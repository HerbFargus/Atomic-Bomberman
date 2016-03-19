// v0.1  by mm (created)
// v0.11 by gm (minor changes)

#include "field.h"

#include "globals.h"
#include "render.h"
#include "gameinfo.h"
#include "imagelist.h"
#include "valuelist.h"
#include "player.h"
#include "timer.h"

#include "cellblank.h"
#include "cellbomb.h"
#include "cellbreakable.h"
#include "cellextra.h"
#include "cellflame.h"
#include "cellpowerup.h"
#include "cellsolid.h"

#include "soundlist.h"
#include "sound.h"
#include "soundtotext.h"

#include <cmath>

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

using namespace cell;


// TODO: Kick: stoppen der Bombe durch Mensch
//             (Bug beseitigen: Mensch bewegt sich; Mensch lauft manchmal durch bombe!!!)

// TODO: Spooger: Mensch wird zentriert bei Spooger-Einsatz

// TODO: Kick: Sound, Animation

// TODO: corner_anim

// TODO: if player dies by his own poops bombs --> death animation error

// TODO: poop sound


Field::Field ()
{
    init();
}

Field::~Field()
{
    unload();
}

void
Field::init()
{
    Globals g;
    int i;

    // Allocate field:

    m_field.resize(g.values().field_w());
    for (i = 0; i < g.values().field_w(); ++i)       // (TODO: algorithm) ???
    {
        m_field[i].resize(g.values().field_h());
    }

    // Distribute blocks on the field:

    for (int x = 0; x < g.values().field_w(); x++)
    {
        for (int y = 0; y < g.values().field_h(); y++)
        {
            switch(g.game().scheme().field_data(x, y))
            {
            case BLOCK_BLANK:
                m_field[x][y].set(new Blank(x, y));
                break;

            case BLOCK_BREAKABLE:
                if (rand() % 100 < g.game().scheme().brick_density())       // TODO: erst PlayerSpace und dann brick_density!!!
                {
                    m_field[x][y].set(new Breakable(x, y));
                }
                else
                    m_field[x][y].set(new Blank(x, y));

                break;

            case BLOCK_SOLID:
                m_field[x][y].set(new Solid(x, y));
                break;

            default:
                cerr << "Error Field::init(): m_field[" << x << "][" << y << " ] not initialized." << endl;
            }
        }
    }


    // Set up players and eventually remove bricks:

    for (i = 0; i < g.values().max_players(); ++i)
    {
        Player& p = g.game().player(i);

        if (p.active() && !p.dead())
        {
            if (g.game().round() == 1)
                p.reset_match();
            else
                p.reset_round();

            int x, y, team;     // TODO: team?  Not here!
            g.game().scheme().player_locations(i, &x, &y, &team);

            if (p.active())
            {
                make_player_space(x, y);

                p.set_fieldpos(x, y);
            }

            p.debug_print_powerups();
        }
    }


    // Distribute Powerups:
    
    // old:
//    int born_with;
//    int override_value;
//    bool bForbidden;
//    for (i = 0; i < PU_NUMBER_OF; ++i)
//    {
//        g.game().scheme().powerup_info(i, &born_with, &override_value, &bForbidden);
//        int nNumber = override_value;
//        if (bForbidden)
//            nNumber = 0;
//        else
//            if (-10 == nNumber)     // if NO override...
//                nNumber = g.values().get(static_cast < EnumValues > (VAL_PU_FIELD_BOMB + i));     // use default
//        put_powerup (static_cast < EnumPowerups > (i), nNumber, PLACE_HIDDEN);
//    }
    
    Powerups pus;
    g.game().scheme().powerup_info_field(&pus);
    
    for (i = 0; i < PU_NUMBER_OF; ++i)
    {
        put_powerup (static_cast < EnumPowerups > (i), pus.get(static_cast < EnumPowerups > (i)),
                     PLACE_HIDDEN);
    }
    

    debug_count_powerups_on_field();


    // Loading textures:

    m_mapbg = g.render().LoadTexture(g.images().map_field(g.game().map()));

//    cout << g.images().map_field(g.game().map()) << endl;
}

void
Field::unload()
{
    Globals g;

    g.render().DeleteTexture(m_mapbg);
}

bool
Field::solid(int x, int y) const
{
    return m_field[x][y].cell().solid();
}

//const cell::Cell& Field::cell(int x, int y) const
//{
//    return m_field[x][y].cell();
//}

void
Field::make_player_space(int x, int y)
{
    // TODO: verbessern. (= in verschiedenen Situationen testen...)

    Globals g;

    m_field[x][y].set(new Blank(x, y));

    if (x + 1 < g.values().field_w())
    {
        m_field[x+1][y].set(new Blank(x+1, y));

        if (y + 1 < g.values().field_h())
        {
            m_field[x+1][y+1].set(new Blank(x+1, y+1));
        }
        else
        {
            m_field[x+1][y-1].set(new Blank(x+1, y+1));
        }
    }
    else
    {
        m_field[x-1][y].set(new Blank(x-1, y));

        if (y + 1 < g.values().field_h())
        {
            m_field[x-1][y+1].set(new Blank(x-1, y+1));
        }
        else
        {
            m_field[x-1][y-1].set(new Blank(x-1, y+1));
        }
    }
}

void
Field::find_powerup_places()
{
    Globals g;

    m_powerupPositions[PLACE_HIDDEN].clear();
    m_powerupPositions[PLACE_REVEALED].clear();

    for (int x = 0; x < g.values().field_w(); x++)
    {
        for (int y = 0; y < g.values().field_h(); y++)
        {
            bool bPlayer = false;
            for (int i = 0; i < g.values().max_players(); ++i)
            {
                const Player& p = g.game().player(i);
                if (p.active() && !p.dead())
                {
                    if (p.fieldpos_x() == x && p.fieldpos_y() == y)
                    {
                        bPlayer = true;
                        break;
                    }
                }
            }

            if (!bPlayer)  // powerups should not be placed under a player...
            {
                if (const Breakable* pb = dynamic_cast < const Breakable* > (&m_field[x][y].cell()))
                {
                    if (!pb->has_powerup())   // only if there is no hidden pu already there
                        m_powerupPositions[PLACE_HIDDEN].push_back(Field::CellCoo(x, y));
                }
                else if (const Blank* pb = dynamic_cast < const Blank* > (&m_field[x][y].cell()))
                {
                    m_powerupPositions[PLACE_REVEALED].push_back(Field::CellCoo(x, y));
                }
            }
        }
    }
}

void
Field::put_powerup (EnumPowerups which, int count, EnumPowerupPlace where)
{
    find_powerup_places();  // update m_powerupPositions

    Globals g;

    if (count < 0)
    {
        if (rand() % 10 < -count)   // the 1-in-10 chance for negative how_many-values
            return;

        count = 1;
    }

    bool bFirstPlace = true;
    int place = where;

    while (count > 0)
    {
        if (bFirstPlace && m_powerupPositions[place].empty())   // if no breakable / blank bricks available
        {
            if (PLACE_HIDDEN == place)
                place = PLACE_REVEALED;
            else
                place = PLACE_HIDDEN;

            bFirstPlace = false;

        }

        if (!bFirstPlace && m_powerupPositions[place].empty()) // if no blank / breakable bricks available
        {
            return; // no putting possible
        }

        int i = rand() % m_powerupPositions[place].size();

        int x = m_powerupPositions[place][i].x;
        int y = m_powerupPositions[place][i].y;

        if (Breakable* pBB = dynamic_cast < Breakable* > (m_field[x][y].cell_pointer()))
        {
            if (!pBB->has_powerup())
            {
                pBB->set_powerup(which);
            }
            else
            {
                cerr << "Error: Field::put_powerup (...): programming error (1)." << endl;
            }
        }
        else if (dynamic_cast < const Blank* > (&m_field[x][y].cell()))
        {
            m_field[x][y].set(new Powerup(x, y, which));
        }
        else
        {
            cerr << "Error: Field::put_powerups (...): programming error (2)." << endl;
        }

        m_powerupPositions[place].erase(m_powerupPositions[place].begin() + i);
        --count;
    }
}

void
Field::draw()
{
    Globals g;

    // Draw the background:

    g.render().DrawTile(0, 0, g.values().res_w(), g.values().res_h(), m_mapbg);


    // Draw the field:

    g.render().SetOffset(g.values().get(VAL_FIELD_OFFSET_X), g.values().get(VAL_FIELD_OFFSET_Y));

    for (int x = 0; x < g.values().field_w(); x++)
    {
        for (int y = 0; y < g.values().field_h(); y++)
        {
            m_field[x][y].draw();
        }
    }

    // Draw the players: (make sure that more lower (y) players will be drawn last)

    for (int y = 0; y < g.values().field_h(); y++)
    {
        DrawPlayerHelper playerarry[MAX_PLAYERS];
        int pl = 0;
        int i;

        for (i = 0; i < g.values().max_players(); ++i)
        {
            Player& p = g.game().player(i);
            if (p.active() && g.game().player(i).fieldpos_y() == y)
            {
                playerarry[pl].m_player = &p;
                playerarry[pl].y = p.pixelpos_y();
                ++pl;
            }
        }

        sort (playerarry, playerarry + g.values().max_players());

        for (i = 0; i < pl; ++i)
            if (playerarry[i].m_player)
                playerarry[i].m_player->draw();
    }

    g.render().SetOffset(0, 0);

    // Draws the title bar:

    g.render().SetTextSizes(16, 16);     // TODO: verbessern!!!
    g.render().DrawText(g.values().get(VAL_FIELD_OFFSET_X), 30, 1.0, 1.0, 1.0, g.snd2txt().text());

}


void
Field::pf_delete_cells ()
{
    Globals g;

    int w = g.values().field_w();
    int h = g.values().field_h();

    // delete bricks that want to be deleted:

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (m_field[x][y].cell().to_be_deleted())
            {
                if (const Breakable* pB = dynamic_cast < const Breakable* > (&m_field[x][y].cell()))
                {
                    // check if there is a powerup under a brick:

                    if (pB->has_powerup())
                    {
                        m_field[x][y].set(new Powerup(x, y, pB->powerup()));
                    }
                    else
                    {
                        m_field[x][y].set(new Blank(x, y));
                    }
                }
                else if (Bomb* pB = dynamic_cast < Bomb* > (m_field[x][y].cell_pointer()))
                {
                    // let bombs explode:

                    // create flames:

                    if (pB->triggered())
                    {
                        string snd = g.soundlist().get_random_sound(SND_BOMB_EXPLOSION);
                        g.sound().play(snd);
                        g.snd2txt().lookup(snd);

                        g.game().player(pB->player()).inc_available_bombs();
                        create_flames(pB);
                    }
                }
                else
                {
                    m_field[x][y].set(new Blank(x, y));
                }
            }
        }
    }
}


void
Field::pf_movement (Player& p)
{
    Globals g;

    // begin: collision detection (old but OK):

//             int cposx, cposy;
//             p.coming_fieldpos(&cposx, &cposy);

//            int old_posx = p.fieldpos_x();
//            int old_posy = p.fieldpos_y();

//             p.update();          // update the player!

//             if (cposx >= 0 && cposy >= 0 && cposx < g.values().field_w() && cposy < g.values().field_h())
//             {
//                 if (m_field[cposx][cposy].cell().solid())// && !m_field[old_posx][old_posy].cell().solid())
//                     p.set_fieldpos(old_posx, old_posy);
//             }
//             else
//             {
//                 p.set_fieldpos(old_posx, old_posy);
//             }

    // end.



    // TODO: jetzt anpassen, damit es nicht ruckelt !!!!!!!

    // (2) new collision detection (begin):

    int ox = p.fieldpos_x();   // old pos
    int oy = p.fieldpos_y();

    double pox = p.pixelpos_x();   // old pixel pos
    double poy = p.pixelpos_y();

    p.update();          // update the player! Must be called to determine shove distances and so on.

    double px = p.pixelpos_x();  // current pixel pos
    double py = p.pixelpos_y();

    EnumDir dir = p.direction();   // direction (after update()!!!)

    double pcx, pcy;     // pixel center pos
    p.cell_center(&pcx, &pcy, px, py, dir);

    int nx, ny;      // next pos
    p.coming_fieldpos2(&nx, &ny);


    double sw = abs(poy - py);    // shove distances (important: x and y are exchanged)
    double sh = abs(pox - px);    // "     "         depend on the actually walked distance between two frames

    double saw = g.values().get(VAL_SHOVE_W);   // shove area (distance from cell border in pixels): when to shove across cells
    double sah = g.values().get(VAL_SHOVE_H);

    double cellw = g.values().get(VAL_CELL_W);
    double cellh = g.values().get(VAL_CELL_H);

    // now do some corrections referring the player's placement...

    switch (dir)
    {
    case DIR_NORTH:
        if (inside(VERT,  false, oy - 1) && m_field[ox][oy-1].cell().solid() &&
            inside(HORIZ, false, ox - 1) && !m_field[ox-1][oy-1].cell().solid() &&
            pcx - cellw / 2 + saw > px)                                    // shove condition + inside left shove area
        {
            p.set_pixelpos(px - sw, py + sw);     // shove left and slow down y movement
        }
        else if (inside(VERT,  false, oy - 1) && m_field[ox][oy-1].cell().solid() &&
                 inside(HORIZ, true , ox + 1) && !m_field[ox+1][oy-1].cell().solid() &&
                 pcx + cellw / 2 - saw < px)                                    // shove condition + inside right shove area
        {
            p.set_pixelpos(px + sw, py + sw);     // shove right and slow down y movement
        }
        else
        {
            if (abs(px - pcx) <= abs(sw))                  // distance from center <= shove dist.
            {
                p.set_pixelpos(pcx, py);                   // center player
            }
            else
            {
                if (px - pcx < 0)                          // left from center
                    p.set_pixelpos(px + sw, py + sw / 2);  // shove right and slow down y movement
                else                                       // right from center
                    p.set_pixelpos(px - sw, py + sw / 2);  // shove left and slow down y movement
            }

            if (ny < 0 || m_field[nx][ny].cell().solid())          // border or next cell is solid
            {
                if (py < pcy) // && p.walking())        // pixel out of valid range and player is walking
                {
                    p.set_pixelpos(px, pcy);               // make pos valid
                    if (p.walking()) // ??? (TODO)
                        on_pf_collide(p, dir, ny < 0 ? 0 : m_field[nx][ny].cell_pointer());
                }
            }
        }
        break;

    case DIR_SOUTH:
        if (inside(VERT,  true , oy + 1) && m_field[ox][oy+1].cell().solid() &&
            inside(HORIZ, false, ox - 1) && !m_field[ox-1][oy+1].cell().solid() &&
            pcx - cellw / 2 + saw > px)
        {
            p.set_pixelpos(px - sw, py - sw);
        }
        else if (inside(VERT,  true , oy + 1) && m_field[ox][oy+1].cell().solid() &&
                 inside(HORIZ, true , ox + 1) && !m_field[ox+1][oy+1].cell().solid() &&
                 pcx + cellw / 2 - saw < px)
        {
            p.set_pixelpos(px + sw, py - sw);
        }
        else
        {
            if (abs(px - pcx) <= abs(sw))
            {
                p.set_pixelpos(pcx, py);
            }
            else
            {
                if (px - pcx < 0)
                    p.set_pixelpos(px + sw, py - sw / 2);
                else
                    p.set_pixelpos(px - sw, py - sw / 2);
            }

            if (ny >= g.values().field_h() || m_field[nx][ny].cell().solid())
            {
                if (py > pcy) // && p.walking())
                {
                    p.set_pixelpos(px, pcy);
                    if (p.walking())
                        on_pf_collide(p, dir, ny >= g.values().field_h() ? 0 : m_field[nx][ny].cell_pointer());
                }
            }
        }
        break;

    case DIR_EAST:
        if (inside(HORIZ, true , ox + 1) && m_field[ox+1][oy].cell().solid() &&
            inside(VERT , false, oy - 1) && !m_field[ox+1][oy-1].cell().solid() &&
            pcy - cellh / 2 + sah > py)
        {
            p.set_pixelpos(px - sh, py - sh);
        }
        else if (inside(HORIZ, true , ox + 1) && m_field[ox+1][oy].cell().solid() &&
                 inside(VERT , true , oy + 1) && !m_field[ox+1][oy+1].cell().solid() &&
                 pcy + cellh / 2 - sah < py)
        {
            p.set_pixelpos(px - sh, py + sh);
        }
        else
        {
            if (abs(py - pcy) <= abs(sh))
            {
                p.set_pixelpos(px, pcy);
            }
            else
            {
                if (py - pcy < 0)
                    p.set_pixelpos(px - sh / 2, py + sh);
                else
                    p.set_pixelpos(px - sh / 2, py - sh);
            }

            if (nx >= g.values().field_w() || m_field[nx][ny].cell().solid())
            {
                if (px > pcx) // && p.walking())
                {
                    p.set_pixelpos(pcx, py);
                    if (p.walking())
                        on_pf_collide(p, dir, nx >= g.values().field_w() ? 0 : m_field[nx][ny].cell_pointer());
                }
            }
        }
        break;

    case DIR_WEST:
        if (inside(HORIZ, false, ox - 1) && m_field[ox-1][oy].cell().solid() &&
            inside(VERT , false, oy - 1) && !m_field[ox-1][oy-1].cell().solid() &&
            pcy - cellh / 2 + sah > py)
        {
            p.set_pixelpos(px + sh, py - sh);
        }
        else if (inside(HORIZ, false, ox - 1) && m_field[ox-1][oy].cell().solid() &&
                 inside(VERT , true , oy + 1) && !m_field[ox-1][oy+1].cell().solid() &&
                 pcy + cellh / 2 - sah < py)
        {
            p.set_pixelpos(px + sh, py + sh);
        }
        else
        {
            if (abs(py - pcy) <= abs(sh))
            {
                p.set_pixelpos(px, pcy);
            }
            else
            {
                if (py - pcy < 0)
                    p.set_pixelpos(px + sh / 2, py + sh);
                else
                    p.set_pixelpos(px + sh / 2, py - sh);
            }

            if (nx < 0 || m_field[nx][ny].cell().solid())
            {
                if (px < pcx) //&& p.walking())
                {
                    p.set_pixelpos(pcx, py);
                    if (p.walking())
                        on_pf_collide(p, dir, nx < 0 ? 0 : m_field[nx][ny].cell_pointer());
                }
            }
        }
        break;
    }

    p.update_animation();


// old:
    //           if (nx >= 0 && ny >= 0 && nx < g.values().field_w() && ny < g.values().field_h())
//             {

//                 if (m_field[cposx][cposy].cell().solid())// && !m_field[old_posx][old_posy].cell().solid())
//                     p.set_fieldpos(old_posx, old_posy);
//             }
//             else
//             {
//                 p.set_fieldpos(old_posx, old_posy);
//             }

    // (2) new collision detection (end)



    // (1) new collision detection (begin):

    // p.update();          // update the player and do collision detection (there is the problem)!

    // (1) new collision detection (end)
}

void
Field::pf_player_actions (Player& p)
{
    Globals g;

    int posx = p.fieldpos_x();
    int posy = p.fieldpos_y();

    // player dies in flames:
    if (const Flame* pF = dynamic_cast < const Flame* > (&m_field[posx][posy].cell()))
    {
        if (pF->player() != p.index() || !g.values().get(VAL_SUICIDE_IMPOSSIBLE))
        {
            p.kill();

            // put dead player's powerups into recycler:

            PlayerPowerupList::iterator it = m_playerPowerups.begin();
            while (it != m_playerPowerups.end())
            {
                if (p.index() == it->nPlayer)
                {
                    m_recycledPowerups.push_back(PowerupInfo(it->type,
                                                             g.timer().time(), g.values().get(VAL_TIME_POWERUP_RECYCLE),
                                                             g.values().get(VAL_TRY_HIDING_DEAD_PLAYER_PUS)==1?PLACE_HIDDEN:PLACE_REVEALED));
                    it = m_playerPowerups.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }
    else
    {
        // trigger next trigger bomb:
        if (p.powerups().get(PU_TRIGGER) > 0 && p.input()->just_pressed(KEY_SPECIAL))
        {
            bool ok = false;

            UINT id;
            while (!ok && (id = p.next_trigger_bomb_id()) > 0)
            {
                int w = g.values().field_w();
                int h = g.values().field_h();

                for (int y = 0; y < h; y++)
                {
                    for (int x = 0; x < w; x++)
                    {
                        if (Bomb* pB = dynamic_cast < Bomb* > (m_field[x][y].cell_pointer()))
                        {
                            if (BOMB_TRIGGER == pB->type() && pB->player() == p.index() && pB->bomb_id() == id)
                            {
                                pB->trigger();
                                ok = true;
                                break;
                            }
                        }
                    }

                    if (ok) break;
                }
            }
        }
    
    
        // stop rolling bombs:
        if (p.powerups().get(PU_ABILITY_KICK) > 0 && p.input()->just_pressed(KEY_SPECIAL))
        {
            int w = g.values().field_w();
            int h = g.values().field_h();

            for (int y = 0; y < h; y++)
            {
                for (int x = 0; x < w; x++)
                {
                    if (Bomb* pB = dynamic_cast < Bomb* > (m_field[x][y].cell_pointer()))
                    {
                        if (pB->player() == p.index() && pB->rolling())
                            pB->stop_rolling();
                    }
                }
            }
        }


        // put bombs:
        // important: keep that order in "if" statement: first: key / disease query, second: solid test:
        bool bBombKey = p.input()->just_pressed(KEY_BOMB);
        const Cell& cell = m_field[posx][posy].cell();
        if ((bBombKey || p.diseases().active(DSE_POOPS)) && !cell.solid())
        {
            // only stupid test:
    //        Bomb* pB = p.create_bomb();
    //        m_field[posx][posy].set(pB);
    //
    //        // if bomb was put on a flame! (TODO: warum passiert das? --> Poops)
    //        if (const Flame* pF = dynamic_cast < const Flame* > (&m_field[posx][posy].cell()))
    //        {
    //            pB->trigger();
    //        }

            m_field[posx][posy].set(p.create_bomb());

            
        }         // Spooger:
        else if (p.powerups().get(PU_SPOOGER) > 0 && bBombKey && dynamic_cast < const Bomb* > (&cell))
        {
            int x = posx;
            int y = posy;

            switch (p.direction())
            {
            case DIR_NORTH:
                while (create_bomb(p, x, --y));
                break;

            case DIR_EAST:
                while (create_bomb(p, ++x, y));
                break;

            case DIR_SOUTH:
                while (create_bomb(p, x, ++y));
                break;

            case DIR_WEST:
                while (create_bomb(p, --x, y));
                break;
            }
        }


        // player got powerup:
        if (Powerup* pPu = dynamic_cast < Powerup* > (m_field[posx][posy].cell_pointer()))
        {
            if (p.add_powerup(pPu->type()))  // give the powerup to the player
            {
                m_playerPowerups.push_back(PowerupInfo(pPu->type(), p.index()));  // and store it if player keeps the powerup
            }
            else
            {
                if (g.values().get(VAL_PLAYER_KEEPS_ADDITIONAL_PUS) == 1) // if player keeps the powerup...
                {
                    m_playerPowerups.push_back(PowerupInfo(pPu->type(), p.index()));  // ...store it to give it back on death
                }
                else
                {
                    m_recycledPowerups.push_back(PowerupInfo(pPu->type(),  // ...else put it into recycler
                                                             g.timer().time(), g.values().get(VAL_TIME_POWERUP_RECYCLE),
                                                             g.values().get(VAL_TRY_HIDING_OTHER_RECYCLED_PUS)==1?PLACE_HIDDEN:PLACE_REVEALED));
                }
            }

            // if a player gives back a powerup:
            EnumPowerups pu;
            if (p.maybe_give_back_powerup (&pu))
            {
                // TODO: TEST!!!
                PlayerPowerupList::iterator it = find (m_playerPowerups.begin(), m_playerPowerups.end(), PowerupInfo(pu, p.index()));
                if (it != m_playerPowerups.end())
                    m_playerPowerups.erase(it);

                m_recycledPowerups.push_back(PowerupInfo(pu,
                                                         g.timer().time(), g.values().get(VAL_TIME_POWERUP_RECYCLE),
                                                         g.values().get(VAL_TRY_HIDING_EXCLUSION_PUS)==1?PLACE_HIDDEN:PLACE_REVEALED));

            }

            // remove powerup cell from field:
            m_field[posx][posy].set(new Blank(posx, posy));
        }


        // p has disease swap?
        if (p.diseases().active(DSE_SWAP))
        {
            if (g.game().active_nondead_players() >= 2)
            {
                bool ok = false;
                
                while (!ok)     // search for a suitible random swap_partner
                {
                    Player& pl = g.game().player(rand() % g.values().max_players());
                    
                    if (pl.active() && !pl.dead() && pl.index() != p.index())
                    {
                        p.swap_positions (pl);
                        p.diseases().swap_ok();
                        ok = true;
                    }
                }
                
            }
        }
        else if (p.diseases().active(DSE_HYPERSWAP))
        {
            if (g.game().active_nondead_players() >= 2)
            {
                int* indexarr = new int[g.values().max_players()]; // array with all valid indizes
                int arr_size = 0;
                
                for (int i = 0; i < g.values().max_players(); ++i)
                {
                    Player& pl = g.game().player(i);
                    if (pl.active() && !pl.dead())
                        indexarr[arr_size++] = i;        // fill array
                }
                
                // todo: vielleicht noch andere swap-Arten einbauen
                for (int a = 0; a < arr_size; a += 2)      // swap all players
                {
//                    cout << a << endl;
                    if (a + 1 < arr_size)
                    {
                        g.game().player(indexarr[a]).swap_positions(g.game().player(indexarr[a+1]));
//                        cout << indexarr[a] << " - " << indexarr[a+1] << endl;
                    }
                    else
                    {
                        g.game().player(indexarr[a]).swap_positions(g.game().player(indexarr[0]));
//                        cout << indexarr[a] << " - " << indexarr[0] << endl;
                    }
                }
            }

            p.diseases().swap_ok();
        }
    }
}

void
Field::pf_recycle_powerups ()
{
    Globals g;

    find_powerup_places();  // update m_powerupPositions

    double cur_time = g.timer().time();
    RecyclePowerupList::iterator it = m_recycledPowerups.begin();
    while (it != m_recycledPowerups.end())
    {
        if (cur_time - it->dStartTime > it->dDuration)
        {
            put_powerup(it->type, 1, it->place);
            it = m_recycledPowerups.erase(it);

//            debug_count_powerups_on_field();
        }
        else
        {
            ++it;
        }
    }
}

void
Field::pf_rolling_bombs ()
{
    Globals g;

    int w = g.values().field_w();
    int h = g.values().field_h();

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
             if (Bomb* pB = dynamic_cast < Bomb* > (m_field[x][y].cell_pointer()))
             {
                 if (pB->rolling()) // if rolling
                 {
                     if (pB->out_of_cell(true))  // if bomb is on cell's center or passed it
                     {
                         bool bChangeBombPos = false;
                         int newx = x;
                         int newy = y;

                         if (pB->roll_dir() == DIR_NORTH)
                         {
                             if (y - 1 < 0 || m_field[x][y - 1].cell().solid() || player_on_cell(x, y - 1))
                             {
                                 pB->stop_rolling();
                             }
                             else if (pB->out_of_cell(false))  // if bomb position has to be changed
                             {
                                 bChangeBombPos = true;
                                 --newy;
                             }
                         }
                         else if (pB->roll_dir() == DIR_SOUTH)
                         {
                             if (y + 1 >= h || m_field[x][y + 1].cell().solid() || player_on_cell(x, y + 1))
                             {
                                 pB->stop_rolling();
                             }
                             else if (pB->out_of_cell(false))
                             {
                                 bChangeBombPos = true;
                                 ++newy;
                             }
                         }
                         else if (pB->roll_dir() == DIR_WEST)
                         {
                             if (x - 1 < 0 || m_field[x - 1][y].cell().solid() || player_on_cell(x - 1, y))
                             {
                                 pB->stop_rolling();
                             }
                             else if (pB->out_of_cell(false))
                             {
                                 bChangeBombPos = true;
                                 --newx;
                             }
                         }
                         else if (pB->roll_dir() == DIR_EAST)
                         {
                             if (x + 1 >= w || m_field[x + 1][y].cell().solid() || player_on_cell(x + 1, y))
                             {
                                 pB->stop_rolling();
                             }
                             else if (pB->out_of_cell(false))
                             {
                                 bChangeBombPos = true;
                                 ++newx;
                             }
                         }

                         if (bChangeBombPos)
                         {
                            if (const Flame* pF = dynamic_cast < const Flame* > (&m_field[newx][newy].cell()))
                            {
                                pB->trigger();
                            }
                            else
                            {
                                if (const Powerup* pPu = dynamic_cast < const Powerup* > (&m_field[newx][newy].cell()))
                                {
                                     m_recycledPowerups.push_back(PowerupInfo(pPu->type(),
                                                     g.timer().time(), g.values().get(VAL_TIME_POWERUP_RECYCLE),
                                                     g.values().get(VAL_TRY_HIDING_OTHER_RECYCLED_PUS)==1?PLACE_HIDDEN:PLACE_REVEALED));
                                }

                                pB->prepare_for_copy();
                                m_field[newx][newy].set(new Bomb(*pB));
                                m_field[x][y].set(new Blank(x, y));
                            }
                         }
                     }
                 }
             }
        }
    }
}

void
Field::on_pf_collide(Player& p, EnumDir dir, Cell* pCell)
{
    if (p.powerups().get(PU_ABILITY_KICK) > 0)
    {
        if (Bomb* pB = dynamic_cast < Bomb* > (pCell))
        {
            if (p.walking())
            {
                if (!pB->rolling())
                    pB->kick(dir);
            }
        }
    }
}

void
Field::process_field()
{
    pf_delete_cells();

    Globals g;

    // go through all players:
    for (int i = 0; i < g.values().max_players(); ++i)
    {
        Player &p = g.game().player(i);

        if (p.active() && !p.dead())
        {
            pf_movement(p);
            pf_player_actions(p);
        }
    }

    pf_rolling_bombs();

    pf_recycle_powerups();
}


bool
Field::inside(EnumAxis axis, bool bRight, int fieldpos)
{
    if (axis == HORIZ)
        if (bRight) // right
            return fieldpos < Globals::values().field_w();
        else  // left
            return fieldpos >= 0;

    else // axis == VERT
        if (bRight) // below
            return fieldpos < Globals::values().field_h();
        else // above
            return fieldpos >= 0;
}

void
Field::create_flames(Bomb* pBomb)
{
    Globals g;
    int pl = pBomb->player();
    int bx = pBomb->x();
    int by = pBomb->y();

    int length = pBomb->flame_length();

    m_field[bx][by].set(new Flame(bx, by, pl, FLAME_CROSS));

    EnumFlameType type;
    int x, y;

    x = 0;
    type = FLAME_HORIZ;
    while (x < length)
    {
        x++;
        if(x == length)
            type = FLAME_EAST;

        if(!create_flame(bx+x, by, pl, type))
            break;
    }

    x = 0;
    type = FLAME_HORIZ;
    while (x < length)
    {
        x++;
        if(x == length)
            type = FLAME_WEST;

        if(!create_flame(bx-x, by, pl, type))
            break;
    }

    y = 0;
    type = FLAME_VERT;
    while (y < length)
    {
        y++;
        if(y == length)
            type = FLAME_SOUTH;

        if(!create_flame(bx, by+y, pl, type))
            break;
    }

    y = 0;
    type = FLAME_VERT;
    while (y < length)
    {
        y++;
        if(y == length)
            type = FLAME_NORTH;

        if(!create_flame(bx, by-y, pl, type))
            break;
    }
}

bool
Field::create_flame(int x, int y, int player, EnumFlameType type)
{
    Globals g;

    if (!(x > g.values().field_w() - 1 || x < 0
          || y > g.values().field_h() - 1 || y < 0))
    {
        const Cell* pCell = &m_field[x][y].cell();

        // create flames on Blank Cells:
        if (dynamic_cast < const Blank* > (pCell))
        {
            m_field[x][y].set(new Flame(x, y, player, type));
            return true;
        }
        else if (const Flame* pF = dynamic_cast < const Flame* > (pCell))
        {
            return true;
        }
        else if (Breakable* pB = dynamic_cast < Breakable* > (m_field[x][y].cell_pointer()))
        {
            pB->break_it();
            return false;
        }
        else if (const Powerup* pp = dynamic_cast < const Powerup* > (pCell))
        {
            if (g.values().get(VAL_POWERUPS_DESTROYABLE) == 0) // if powerups are NOT destroyable
            {
                if (pp->type() == PU_DISEASE)
                {
                    if (g.values().get(VAL_DISEASES_DESTROYABLE) == 0) // if powerup is disease && not destroyable
                        m_recycledPowerups.push_back(PowerupInfo(pp->type(),  // ...put it into recycler
                                                                 g.timer().time(), g.values().get(VAL_TIME_POWERUP_RECYCLE),
                                                                 g.values().get(VAL_TRY_HIDING_OTHER_RECYCLED_PUS)==1?PLACE_HIDDEN:PLACE_REVEALED));
                }
                else  // if powerup is a real powerUP
                {
                    if (g.values().get(VAL_POWERUPS_DESTROYABLE) == 0) // not destroyable
                        m_recycledPowerups.push_back(PowerupInfo(pp->type(),  // ...put it into recycler
                                                                 g.timer().time(), g.values().get(VAL_TIME_POWERUP_RECYCLE),
                                                                 g.values().get(VAL_TRY_HIDING_OTHER_RECYCLED_PUS)==1?PLACE_HIDDEN:PLACE_REVEALED));
                }
            }

            m_field[x][y].set(new Blank(x, y));
            return false;
        }
        else if (dynamic_cast < const Solid* > (pCell))
        {
            return false;
        }
        else if (Bomb* pB = dynamic_cast < Bomb* > (m_field[x][y].cell_pointer()))
        {
            pB->trigger(true);
            return false; // return true, if the flame should penetrate the bomb and affect further bombs
        }
        else if (dynamic_cast < const Extra* > (pCell))
        {
            return true;
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
}

bool
Field::create_bomb (Player& p, int x, int y)
{
    Globals g;

    if (x >= 0 && x < g.values().field_w()
        && y >= 0 && y < g.values().field_h()
        && !m_field[x][y].cell().solid())
    {
        m_field[x][y].set(p.create_bomb(x, y));
        return true;
    }
    else
        return false;
}

bool
Field::player_on_cell (int xx, int yy)
{
    Globals g;
    bool bPlayer = false;

     for (int i = 0; i < g.values().max_players(); ++i)
     {
         const Player& p = g.game().player(i);
         if (p.active() && !p.dead() && p.fieldpos_x() == xx && p.fieldpos_y() == yy)
         {
             bPlayer = true;
             break;
         }
     }

    return bPlayer;
}

void
Field::debug_count_powerups_on_field()
{
    Globals g;

    int hidden[PU_NUMBER_OF];
    int revealed[PU_NUMBER_OF];

    fill (hidden, hidden + PU_NUMBER_OF, 0);
    fill (revealed, revealed + PU_NUMBER_OF, 0);

    for (int x = 0; x < g.values().field_w(); x++)
    {
        for (int y = 0; y < g.values().field_h(); y++)
        {

            if (const Breakable* pb = dynamic_cast < const Breakable* > (&m_field[x][y].cell()))
                if (pb->has_powerup())
                    ++hidden[pb->powerup()];
            if (const Powerup* pp = dynamic_cast < const Powerup* > (&m_field[x][y].cell()))
                ++revealed[pp->type()];
        }
    }

    cout << "Field: "
         << "B=" <<     hidden[PU_BOMB]         + revealed[PU_BOMB]          << "(" << hidden[PU_BOMB]         << "+" << revealed[PU_BOMB]          << ")" << ", "
         << "FL=" <<    hidden[PU_FLAME]        + revealed[PU_FLAME]         << "(" << hidden[PU_FLAME]        << "+" << revealed[PU_FLAME]         << ")" << ", "
         << "DIS=" <<   hidden[PU_DISEASE]      + revealed[PU_DISEASE]       << "(" << hidden[PU_DISEASE]      << "+" << revealed[PU_DISEASE]       << ")" << ", "
         << "KICK=" <<  hidden[PU_ABILITY_KICK] + revealed[PU_ABILITY_KICK]  << "(" << hidden[PU_ABILITY_KICK] << "+" << revealed[PU_ABILITY_KICK]  << ")" << ", "
         << "SPEED=" << hidden[PU_EXTRA_SPEED]  + revealed[PU_EXTRA_SPEED]   << "(" << hidden[PU_EXTRA_SPEED]  << "+" << revealed[PU_EXTRA_SPEED]   << ")" << ", "
         << "PUNCH=" << hidden[PU_ABLITY_PUNCH] + revealed[PU_ABLITY_PUNCH]  << "(" << hidden[PU_ABLITY_PUNCH] << "+" << revealed[PU_ABLITY_PUNCH]  << ")" << ", "
         << "GRAB=" <<  hidden[PU_ABILITY_GRAB] + revealed[PU_ABILITY_GRAB]  << "(" << hidden[PU_ABILITY_GRAB] << "+" << revealed[PU_ABILITY_GRAB]  << ")" << ", "
         << "SPG=" <<   hidden[PU_SPOOGER]      + revealed[PU_SPOOGER]       << "(" << hidden[PU_SPOOGER]      << "+" << revealed[PU_SPOOGER]       << ")" << ", "
         << "GOLD=" <<  hidden[PU_GOLDFLAME]    + revealed[PU_GOLDFLAME]     << "(" << hidden[PU_GOLDFLAME]    << "+" << revealed[PU_GOLDFLAME]     << ")" << ", "
         << "TRIG=" <<  hidden[PU_TRIGGER]      + revealed[PU_TRIGGER]       << "(" << hidden[PU_TRIGGER]      << "+" << revealed[PU_TRIGGER]       << ")" << ", "
         << "JLLY=" <<  hidden[PU_JELLY]        + revealed[PU_JELLY]         << "(" << hidden[PU_JELLY]        << "+" << revealed[PU_JELLY]         << ")" << ", "
         << "EBOLA=" << hidden[PU_EBOLA]        + revealed[PU_EBOLA]         << "(" << hidden[PU_EBOLA]        << "+" << revealed[PU_EBOLA]         << ")" << ", "
         << "RNDM=" <<  hidden[PU_RANDOM]       + revealed[PU_RANDOM]        << "(" << hidden[PU_RANDOM]       << "+" << revealed[PU_RANDOM]        << ")" << ", " << endl;
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



Field::FieldCell::FieldCell()
    : m_cell (0),
      m_extra (0)
{
}

Field::FieldCell::~FieldCell()
{
//    cout << "~FieldCell" << endl;
    delete m_cell;
    delete m_extra;
}

void
Field::FieldCell::set(Cell* cell)
{
    if (cell)
    {
        delete m_cell;
        m_cell = cell;
    }
}

const Cell&
Field::FieldCell::cell() const
{
    return *m_cell;
}

Cell*
Field::FieldCell::cell_pointer()
{
    return m_cell;
}

void
Field::FieldCell::draw()
{
    m_cell->draw();
}
