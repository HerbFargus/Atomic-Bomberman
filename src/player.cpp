// v0.1  by gm (created)
// v0.11 by gm (development phase)
// v0.2  by gm (added new functions)
// v0.21 by gm (fixed memory handling errors)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

// information about the AB player:
// --------------------------------
// times:
// 2 x back and forth (= 60 cells)
//    0 additional speed:            12.54 s       145 pixel / s
//    1 additional speed:            10.79 s
//    2 additional speed:             9.39 s
//
// additional speed = 25 pixel / s
//
// animspeed factor = 1.3: (With 0,1,2... additional speed) our bomberman does 17 steps to run from left to right.


#include "player.h"
#include "globals.h"
#include "render.h"
#include "valuelist.h"
#include "timer.h"
#include "cellbomb.h"
#include "field.h"
#include "gameinfo.h"
#include "soundlist.h"
#include "soundtotext.h"
#include "sound.h"

#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "inputmouse.h"
using namespace input;

#include <iostream>
using namespace std;

#include "inputmouse.h"

// TODO: corner anim!!!
// TODO: anim speed depends on pixel speed (speed())!!!  --> ok so weit, aber noch mal pruefen


Player::Player(int index)
    : m_nArrayIndex (index)
{
    init();
}

Player::~Player()
{

}


void
Player::init()
{
    m_bActive   = false;
    m_pInput  = 0;
    m_nWins     = 0;
    m_nKills    = 0;

    m_fieldpos_x  = 0;
    m_fieldpos_y  = 0;

    m_pixelpos_x  = 0;
    m_pixelpos_y  = 0;

    m_nBombsOnField = 0;

    m_speed       = Globals::values().get(VAL_PLAYER_SPEED);
    m_dir1        = DIR_SOUTH;
    m_dir2        = -1;
    m_direction   = m_dir1;
    m_bWalking    = false;
    m_curAnim     = ANI_STAND;

    m_anim.SetAnimation(ANI_STAND, m_direction);

    m_fith_starttime = 0;
    m_fith_bombs = 0;

    m_bDead = false;

    m_nGiveBackPu = -1;
}

void
Player::reset_match()
{
    m_nWins = 0;
    m_nKills = 0;

    reset_round();
}

void
Player::reset_round()
{
    Globals g;
    
    // reset powerups:
    m_powerups.reset();
    const Scheme& scheme = Globals::game().scheme();
    scheme.powerup_info_player(&m_powerups);
    
    m_pudata.reset();
    
    m_diseases.reset();
    apply_powerup_values();

    m_dir1        = DIR_SOUTH;
    m_dir2        = -1;
    m_direction   = m_dir1;
    m_bWalking    = false;
    m_curAnim     = ANI_STAND;

    m_anim.SetAnimation(ANI_STAND, m_direction);

    m_nBombsOnField = 0;

    m_fith_starttime = 0;
    m_fith_bombs = 0;

    m_bDead = false;
}

void
Player::set_active(bool active)
{
    m_bActive = active;
}

bool
Player::active() const
{
    return m_bActive;
}

Input*
Player::input()
{
    if (!m_pInput)
        cerr << "Player::input(): Serious Error: m_pInput == 0" << endl;

    return m_pInput;
}

void
Player::set_input(Input* pInput)
{
    if (!pInput)
        cerr << "Error! Player::set_input(): pInput == 0" << endl;
    else
    {
        m_pInput = pInput;
        if (input::Mouse* pm = dynamic_cast < Mouse * > (m_pInput))
            pm->set_player(this);
    }
}

int
Player::index() const
{
    if (m_nArrayIndex < 0 || m_nArrayIndex >= Globals::values().max_players())
        cerr << "Error! Player::index(): index out of bounds!!! " << m_nArrayIndex << endl;

    return m_nArrayIndex;
}

void
Player::update()
{
    if (m_bDead) return;

    Globals g;
    int nPressedKeys = 0;
    int dir1 = -1;
    int dir2 = -1;
    bool bDirChanged = false;

    EnumPlayerKeys key_up = KEY_UP;
    EnumPlayerKeys key_down = KEY_DOWN;
    EnumPlayerKeys key_right = KEY_RIGHT;
    EnumPlayerKeys key_left = KEY_LEFT;

    if (diseases().active(DSE_REVERSED))
    {
        key_up = KEY_DOWN;
        key_down = KEY_UP;
        key_right = KEY_LEFT;
        key_left = KEY_RIGHT;
    }

    if (input()->pressed(key_up) && nPressedKeys <= 2)
    {
        ++nPressedKeys;

        if (nPressedKeys == 1)
            dir1 = DIR_NORTH;
        else
            dir2 = DIR_NORTH;

    }

    if (input()->pressed(key_left) && nPressedKeys <= 2)
    {
        ++nPressedKeys;

        if (nPressedKeys == 1)
            dir1 = DIR_WEST;
        else
            dir2 = DIR_WEST;

    }

    if (input()->pressed(key_down) && nPressedKeys <= 2)
    {
        ++nPressedKeys;

        if (nPressedKeys == 1)
            dir1 = DIR_SOUTH;
        else
            dir2 = DIR_SOUTH;
    }

    if (input()->pressed(key_right) && nPressedKeys <= 2)
    {
        ++nPressedKeys;

        if (nPressedKeys == 1)
            dir1 = DIR_EAST;
        else
            dir2 = DIR_EAST;
    }

    // if more than one key is pressed, behave as if 2 keyes were pressed
    if (nPressedKeys > 2)
        nPressedKeys = 2;

    if (nPressedKeys == 0)
        m_bWalking = false;
    else
        m_bWalking = true;


    if (nPressedKeys == 1)
    {
        if (m_dir1 != dir1 || m_curAnim == ANI_STAND)
        {
            bDirChanged = true;
            m_dir1 = static_cast < EnumDir > (dir1);
        }

        if (m_dir2 != -1)
        {
            m_dir2 = -1;
            bDirChanged = true;
        }
    }
    else if (nPressedKeys == 2)
    {
        if (dir1 != m_dir1)    // it is not certain that dir1 is equal m_direction!
            dir2 = dir1;

        if (m_dir2 != dir2 || m_curAnim == ANI_STAND)
        {
            bDirChanged = true;
            m_dir2 = dir2;
        }
    }

    // Update m_direction:

    if (nPressedKeys == 1)
        m_direction = static_cast < EnumDir > (m_dir1);
    else if (nPressedKeys == 2)
        m_direction = static_cast < EnumDir > (m_dir2);

    m_oldx = m_pixelpos_x;
    m_oldy = m_pixelpos_y;

    if (m_bWalking || bDirChanged)
    {
//         // TODO: walking direction in Abh. von der tatsächlich gelaufenen Bahn!!!
//         if (bDirChanged)
//         {
//             m_anim.SetAnimation(ANI_WALK, m_direction, 1.3f + 0.17f * powerups().get(PU_EXTRA_SPEED));    // TODO: richtig
//             m_anim.Start();
//             m_curAnim = ANI_WALK;
//         }

        // Let the player move...

        int cx, cy;
        coming_fieldpos (&cx, &cy);

        switch (m_direction)
        {
        case DIR_NORTH:
//            if (!g.game().field()->data()[cx][cy].m_brick->solid())
            m_pixelpos_y -= speed() * g.timer().frame_time();
            break;

        case DIR_WEST:
//            if (!g.game().field()->data()[cx][cy].m_brick->solid())
            m_pixelpos_x -= speed() * g.timer().frame_time();
            break;

        case DIR_SOUTH:
//            if (!g.game().field()->data()[cx][cy].m_brick->solid())
            m_pixelpos_y += speed() * g.timer().frame_time();
            break;

        case DIR_EAST:
//            if (!g.game().field()->data()[cx][cy].m_brick->solid())
            m_pixelpos_x += speed() * g.timer().frame_time();
            break;

        }
    }
    else
    {
        if (m_curAnim != ANI_STAND)
        {
//          if(m_direction == DIR_SOUTH)
//
//          else if(m_direction == DIR_EAST)
//              m_anim.SetAnimation(ANI_CORNER); // TODO
//          else

            m_anim.SetAnimation(ANI_STAND, m_direction);
            m_curAnim = ANI_STAND;
        }
    }


    // pixel to field position...
    pixel2field(m_pixelpos_x, m_pixelpos_y, &m_fieldpos_x, &m_fieldpos_y);

    m_bDirChanged = bDirChanged;

    if (bDirChanged)
    {
        // TODO: m_speed verwenden!!!
        //m_anim.SetAnimation(ANI_WALK, m_direction, 1.3f + 0.17f * powerups().get(PU_EXTRA_SPEED));    // TODO: richtig
        m_anim.SetAnimation(ANI_WALK, m_direction, 1.3f * speed() / g.values().get(VAL_PLAYER_SPEED));    // TODO: richtig
        m_anim.Start();
        m_curAnim = ANI_WALK;
    }
}

void
Player::update_animation()
{
    // TODO:

//     EnumDir dir;

//     double diff_east  = m_pixelpos_x > m_oldx;
//     double diff_west  = m_pixelpos_x < m_oldx;
//     double diff_north = m_pixelpos_y < m_oldy;
//     double diff_south = m_pixelpos_y > m_oldy;

//     m_bDirChanged = false;

//     bool bDiff = true;
//     double offset = 1.0;

//     if (diff_east > diff_west + offset && diff_east > diff_north + offset && diff_east > diff_south + offset)
//         dir = DIR_EAST;
//     else if (diff_west > diff_east + offset && diff_west > diff_north + offset && diff_west > diff_south + offset)
//         dir = DIR_WEST;
//     else if (diff_north > diff_west + offset && diff_north > diff_east + offset && diff_north > diff_south + offset)
//         dir = DIR_NORTH;
//     else if (diff_south > diff_west + offset && diff_south > diff_north + offset && diff_south > diff_east + offset)
//         dir = DIR_SOUTH;
//     else
//         bDiff = false;

//     if (bDiff && dir != m_direction)
//     {
//         m_bDirChanged = true;
//         m_oldDir = dir;
//     }

//     if (m_bDirChanged)
//     {
//         m_anim.SetAnimation(ANI_WALK, dir, 1.3f + 0.17f * powerups().get(PU_EXTRA_SPEED));    // TODO: richtig
//         m_anim.Start();
//         m_curAnim = ANI_WALK;
//     }

}

void
Player::draw()
{
    Globals g;


    m_anim.Update();

    EnumAnims animtype = m_anim.GetCurAnimType();
    if (animtype == ANI_DYING)
        m_anim.Draw(m_pixelpos_x, m_pixelpos_y);
    else
        m_anim.Draw(m_pixelpos_x, m_pixelpos_y, 176, 176);

//    m_anim.Draw(m_pixelpos_x, m_pixelpos_y);

    if (m_bDead)
    {
        if (m_anim.IsFinished())
        {
            m_bDead = false;
            set_active(false);
        }
    }

    // TODO: That's only a test drawing!

    SDL_Rect rect = {(int)m_pixelpos_x, (int)m_pixelpos_y, 2, 2};
    g.render().FillRect(rect, 1.0, 1.0, 1.0);

    double fr = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0R + index() * 3)) / 255.0;
    double fg = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0G + index() * 3)) / 255.0;
    double fb = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0B + index() * 3)) / 255.0;

    g.render().SetTextSizes(16, 16);
    g.render().DrawText((int)m_pixelpos_x - 6, (int)m_pixelpos_y - 22, fr, fg, fb,
                        "index()FIXME"); //                        "%d", index());//FIXME

    if (diseases().infected() > 0)
    {
        g.render().DrawText((int)m_pixelpos_x - 20, (int)m_pixelpos_y - 5, fr, fg, fb,
                            "infected");

    }

//     int tw = g.values().cell_w();
//     int th = g.values().cell_h();


//    g.render().DrawText(fieldpos_x() * tw + tw / 2, fieldpos_y() * th + th / 2, 255, index() / 10.0, index() / 10.0,
//                        "Player %d: %d, %d,     %f", index(), fieldpos_x(), fieldpos_y(), m_pixelpos_x);
}

const Powerups&
Player::powerups() const
{
    return m_powerups;
}

PowerupData&
Player::pudata()
{
    return m_pudata;
}

Diseases&
Player::diseases()
{
    return m_diseases;
}

bool
Player::add_powerup(EnumPowerups pu)
{
    Globals g;

    bool bGotIt = true;

    // some powerups exclude some others
    // if so the new powerup will replace the old (which will be given back on field)
    switch (pu)
    {
    case PU_ABLITY_PUNCH:
        if (powerups().get(PU_TRIGGER) > 0)
            m_nGiveBackPu = PU_TRIGGER;
        break;

    case PU_ABILITY_GRAB:
        if (powerups().get(PU_SPOOGER) > 0)
            m_nGiveBackPu = PU_SPOOGER;
        break;

    case PU_SPOOGER:
        if (powerups().get(PU_ABILITY_GRAB) > 0)
            m_nGiveBackPu = PU_ABILITY_GRAB;
        break;

    case PU_TRIGGER:
        if (powerups().get(PU_JELLY) > 0)
            m_nGiveBackPu = PU_JELLY;
        
        if (powerups().get(PU_ABLITY_PUNCH))
            m_nGiveBackPu = PU_ABLITY_PUNCH;
        
        // set number of trigger bombs
        m_pudata.inc_trigger_bombs(powerups().get(PU_BOMB));
        break;

    case PU_JELLY:
        if (powerups().get(PU_TRIGGER) > 0)
            m_nGiveBackPu = PU_TRIGGER;
        break;

    case PU_BOMB:
        if (powerups().get(PU_TRIGGER) > 0)
            m_pudata.inc_trigger_bombs(powerups().get(PU_BOMB) + 1);
        break;

    case PU_FLAME:
    case PU_DISEASE:
    case PU_ABILITY_KICK:
    case PU_EXTRA_SPEED:
    case PU_GOLDFLAME:
    case PU_EBOLA:
    case PU_RANDOM:
    case PU_NUMBER_OF:
        break;
    }


    // add powerup and play sound:
    switch (pu)
    {
    case PU_BOMB:
    case PU_FLAME:
    case PU_ABILITY_KICK:
    case PU_EXTRA_SPEED:
    case PU_ABLITY_PUNCH:
    case PU_ABILITY_GRAB:
    case PU_SPOOGER:
    case PU_GOLDFLAME:
    case PU_TRIGGER:
    case PU_JELLY:
        if (powerups().get(pu) < g.values().get(static_cast < EnumValues > (VAL_PU_MAX_BOMB + pu)))    // you can get a maximum number of pu
        {
            m_powerups.inc(pu, 1);
            apply_powerup_values();
        }
        else
        {
            bGotIt = false;
        }

        {
            string snd = g.soundlist().get_random_sound(SND_POWERUP);   // only play sound if really got the powerup

            g.sound().play(snd);
            g.snd2txt().lookup(snd);
        }
        break;

    case PU_DISEASE:
        m_diseases.infect(1);
        cout << "Player " << index() << ": ";
        m_diseases.debug_print_diseases();
        break;

    case PU_EBOLA:
        m_diseases.infect(rand()%2+2);    // add 2..3 diseases: todo: dynmamic
        break;

        // TODO:
    case PU_RANDOM:
    {
        m_powerups.inc(pu, 1);    // only for statistic reasons
        string snd = g.soundlist().get_random_sound(SND_POWERUP);   // only play sound if really got the powerup
        g.sound().play(snd);
        g.snd2txt().lookup(snd);
    }
    break;

    default:
        cerr << "Errror: Player::add_powerup(...): programming error: default statement reached." << endl;
    }

//  debug_print_powerups();

    return bGotIt;
}

bool
Player::remove_powerup (EnumPowerups pu)
{
    if (powerups().get(pu) > 0)
    {
        m_powerups.inc(pu, -1);
        apply_powerup_values();
        debug_print_powerups();
        return true;
    }
    else
    {
        debug_print_powerups();
        return false;
    }
}

bool
Player::maybe_give_back_powerup(EnumPowerups *pu)
{
    if (m_nGiveBackPu > -1)
    {
        *pu = static_cast < EnumPowerups > (m_nGiveBackPu);
        m_nGiveBackPu = -1;

        if (remove_powerup (*pu))
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

UINT
Player::next_trigger_bomb_id()
{
    return m_pudata.remove_next_bomb_id();
}

int
Player::wins() const
{
    return m_nWins;
}

int
Player::kills() const
{
    return m_nKills;
}

void
Player::inc_wins(int amount)
{
    m_nWins += amount;
}

void
Player::inc_kills(int amount)
{
    m_nKills += amount;
}

void Player::set_pixelpos(double x, double y)
{
    m_pixelpos_x = x;
    m_pixelpos_y = y;

    pixel2field(m_pixelpos_x, m_pixelpos_y, &m_fieldpos_x, &m_fieldpos_y);
}

void
Player::set_fieldpos(int x, int y)
{
    m_fieldpos_x = x;
    m_fieldpos_y = y;

    field2pixel(m_fieldpos_x, m_fieldpos_y, &m_pixelpos_x, &m_pixelpos_y);
}

double
Player::pixelpos_x() const
{
    return m_pixelpos_x;
}

double
Player::pixelpos_y() const
{
    return m_pixelpos_y;
}

int
Player::fieldpos_x() const
{
    return m_fieldpos_x;
}

int
Player::fieldpos_y() const
{
    return m_fieldpos_y;
}

double
Player::speed() const
{
    if (m_diseases.active(DSE_MOLASSES))
    {
        return m_diseases.speed_molasses();
    }
    else if (m_diseases.active(DSE_CRACK))
    {
        return m_diseases.speed_crack();
    }
    else
    {
        return m_speed;
    }
}

EnumDir
Player::direction() const
{
    return m_direction;
}

void
Player::coming_fieldpos(int *x, int *y) const
{
    Globals g;
    int tw = g.values().cell_w();
    int th = g.values().cell_h();

    double pixpos_x = m_pixelpos_x;
    double pixpos_y = m_pixelpos_y;

    switch (m_direction)
    {
    case DIR_NORTH:
        pixpos_y -= th / 2;
//        pixpos_y -= th;
        break;

    case DIR_WEST:
        pixpos_x -= tw / 2;
//        pixpos_x -= tw;
        break;

    case DIR_SOUTH:
        pixpos_y += th / 2;
//        pixpos_y += th;
        break;

    case DIR_EAST:
        pixpos_x += tw / 2;
//        pixpos_x += tw;
        break;
    }

    *x = static_cast < int > (pixpos_x / tw);
    *y = static_cast < int > (pixpos_y / th);

    // TODO: besser machen?

    // if outside of field!!!
    if (pixpos_x / tw < 0) *x = -1;
    if (pixpos_y / th < 0) *y = -1;
}

void
Player::coming_fieldpos2(int *x, int *y) const
{
    Globals g;

    int fx = fieldpos_x();
    int fy = fieldpos_y();

    switch (direction())
    {
    case DIR_NORTH:
        *x = fx;
        *y = fy - 1;
        break;

    case DIR_WEST:
        *x = fx - 1;
        *y = fy;
        break;

    case DIR_SOUTH:
        *x = fx;
        *y = fy + 1;
        break;

    case DIR_EAST:
        *x = fx + 1;
        *y = fy;
        break;
    }
}

void
Player::pixel2field(const double& px, const double& py, int *fx, int *fy)
{
    Globals g;
    double tw = g.values().cell_w();
    double th = g.values().cell_h();

    *fx = static_cast < int > (px / tw);
    *fy = static_cast < int > (py / th);

    // TODO: besser machen?

    // outside of field!!!
    if (px / tw < 0) *fx = -1;
    if (py / th < 0) *fy = -1;

//    cout << pixelpos_x << " " << fieldpos_x << " " << pixelpos_x / tw << endl;
}

void
Player::field2pixel(const int& fx, const int& fy, double *px, double *py)
{
    Globals g;
    int tw = g.values().cell_w();
    int th = g.values().cell_h();

    *px = fx * tw + tw / 2;
    *py = fy * th + th / 2;
}

double
Player::cell_center (double *center_x, double *center_y, double pixx, double pixy, int direction)
{
    // TODO: lkaslasdjfksfd

    int fx, fy;
    pixel2field (pixx, pixy, &fx, &fy);

    double cw = Globals::values().cell_w();
    double ch = Globals::values().cell_h();

    *center_x = fx * cw + cw / 2;
    *center_y = fy * ch + ch / 2;


    if (direction == DIR_NORTH || direction == DIR_SOUTH)
    {
        return *center_x;
    }
    else
    {
        return *center_x;
    }
}

void
Player::apply_powerup_values()
{
    Globals g;

    // Update speed:
    m_speed = g.values().get(VAL_PLAYER_SPEED) + powerups().get(PU_EXTRA_SPEED) * g.values().get(VAL_PLAYER_SPEED_ADD);
}


cell::Bomb*
Player::create_bomb(int x /*= -1*/, int y /*= -1*/)
{
    Globals g;

    // check if player has enough bombs:
    if (m_nBombsOnField < powerups().get(PU_BOMB) && !diseases().active(DSE_CONSTIPATION))
    {
        ++m_nBombsOnField;        // --m_nBombsOnField (see cell::Bomb::~cell::Bomb)



//         if (m_nBombsOnField >= g.values().get(VAL_FIREINTHEHOLE_BOMBS))
//         {
//             g.sound().play(g.soundlist().get_random_sound(SND_ON_MANY_BOMBS));
//         }


//         // Fire in the Hole (TODO:

//         double curTime = g.timer().time();

//         if (curTime - m_fith_starttime <= g.values().get(VAL_FIREINTHEHOLE_TIME) / 1000.0)
//         {
//             ++m_fith_bombs;
//             if (m_fith_bombs >= g.values().get(VAL_FIREINTHEHOLE_BOMBS))
//             {
//                 m_fith_bombs = 0;
//                 g.sound().play(g.soundlist().get_random_sound(SND_ON_MANY_BOMBS));
//             }
//         }
//         else
//         {
//             m_fith_starttime = curTime;
//             m_fith_bombs = 0;
//         }
        
        // bombtype:
        cell::EnumBombType bombtype = cell::BOMB_NORMAL;
        
        if (powerups().get(PU_TRIGGER) > 0 && pudata().trigger_bombs() > 0)
        {
            m_pudata.inc_trigger_bombs(-1);
            bombtype = cell::BOMB_TRIGGER;
        }
        else if (powerups().get(PU_JELLY) > 0)
        {
            bombtype = cell::BOMB_JELLY;
        }
        
        
        // flame length:
        int flame_length = powerups().get(PU_FLAME);

        if (diseases().active(DSE_SHORTFLAME))         // short flame dominates goldflame
        {
            flame_length = 1;
        }
        else if (powerups().get(PU_GOLDFLAME) > 0)
        {
            int w = g.values().get(VAL_FIELD_WIDTH);
            int h = g.values().get(VAL_FIELD_HEIGHT);
            
            flame_length = w>h?w:h;
        }
        
        
        // fuze length:
        int fuze = g.values().get(VAL_FUZE_TIME_NORMAL);

        if (diseases().active(DSE_SHORTFUZE))
            fuze = g.values().get(VAL_FUZE_TIME_SHORT);


        // bomb position:
        if (x == -1) x = fieldpos_x();
        if (y == -1) y = fieldpos_y();

        
        // create bomb:
        cell::Bomb* pBomb = new cell::Bomb (x, y, index(), bombtype, flame_length, fuze);

        
        // play poop sound, if poop man...
        if (0 != pBomb && diseases().active(DSE_POOPS))
        {
            // TODO: larger "poop intervals" !!!
            g.sound().play(g.soundlist().get_random_sound(SND_POOP));
        }
        
        
        // if trigger bomb, add bomb id to list:
        if (powerups().get(PU_TRIGGER) > 0)
            m_pudata.add_bomb_id(pBomb->bomb_id());

        return pBomb;
    }
    else
    {
        // change nothing on the field...
        return 0;
    }
}

void
Player::inc_available_bombs()
{
    --m_nBombsOnField;
}

bool
Player::walking()
{
    return m_bWalking;
}

void
Player::kill()
{
    if (!m_bDead)
    {
        Globals g;

        m_bDead = true;
        m_anim.SetAnimation(ANI_DYING);
        m_anim.Start();
        m_curAnim = ANI_DYING;

        // TODO: Wenn Player ohne sich zu bewegen stirbt, dann ist die Animation falsch!!! ???

        string snd = g.soundlist().get_random_sound(SND_DIE);
        g.sound().play(snd);
        g.snd2txt().lookup(snd);
    }
}

bool
Player::dead() const
{
    return m_bDead;
}

void
Player::swap_positions (Player & swap_partner)
{
    int      tmp_fieldpos_x = m_fieldpos_x;
    int      tmp_fieldpos_y = m_fieldpos_y;
    double   tmp_pixelpos_x = m_pixelpos_x;
    double   tmp_pixelpos_y = m_pixelpos_y;

    m_fieldpos_x = swap_partner.m_fieldpos_x;
    m_fieldpos_y = swap_partner.m_fieldpos_y;
    m_pixelpos_x = swap_partner.m_pixelpos_x;
    m_pixelpos_y = swap_partner.m_pixelpos_y;

    swap_partner.m_fieldpos_x = tmp_fieldpos_x;
    swap_partner.m_fieldpos_y = tmp_fieldpos_y;
    swap_partner.m_pixelpos_x = tmp_pixelpos_x;
    swap_partner.m_pixelpos_y = tmp_pixelpos_y;
}

void
Player::debug_print_powerups()
{
    cout << "Player " << index() << ": "
         << "B=" << powerups().get(PU_BOMB) << ", "
         << "FL=" << powerups().get(PU_FLAME) << ", "
         << "DIS=" << powerups().get(PU_DISEASE) << ", "
         << "KICK=" << powerups().get(PU_ABILITY_KICK) << ", "
         << "SPEED=" << powerups().get(PU_EXTRA_SPEED) << ", "
         << "PUNCH=" << powerups().get(PU_ABLITY_PUNCH) << ", "
         << "GRAB=" << powerups().get(PU_ABILITY_GRAB) << ", "
         << "SPG=" << powerups().get(PU_SPOOGER) << ", "
         << "GOLD=" << powerups().get(PU_GOLDFLAME) << ", "
         << "TRIG=" << powerups().get(PU_TRIGGER) << ", "
         << "JLLY=" << powerups().get(PU_JELLY) << ", "
         << "EBOLA=" << powerups().get(PU_EBOLA) << ", "
         << "RNDM=" << powerups().get(PU_RANDOM) << ", " << endl;
}
