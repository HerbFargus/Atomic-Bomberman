// v0.1  by gm (created)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#ifdef WIN32
#define NOMINMAX
#endif

#include "cellbomb.h"
#include "globals.h"
#include "valuelist.h"
#include "render.h"
#include "timer.h"
#include "field.h"

#include "soundlist.h"

#ifndef DISABLE_SOUND
 #include "sound.h"
#endif

namespace cell
{

#ifdef WIN32    // Win32 uses STL
#include <limits>
    using std::numeric_limits;
#else
#include <climits>
#endif
    
    int Bomb::m_increasing_number = 0;

    Bomb::Bomb(int x, int y, int nPlayer, EnumBombType type, int flame_length, int fuze_time)
        : Cell(x, y), m_player (nPlayer), m_type (type), m_flame_length (flame_length), m_time (fuze_time)
    {
        m_nBombID = ++m_increasing_number;

        Globals g;

        anim().SetAnimation(ANI_BOMB);

        anim().Start();

        // Bombe soll erst klein sein...         (TODO: algorithm)
        for (int i = 0; i < 40; ++i)
        {
            anim().Update();
        }

        m_bTriggered = false;

        m_start_time = g.timer().time();

        g.sound().play(g.soundlist().get_random_sound(SND_BOMB_DROP));

        if (BOMB_TRIGGER == type)
#ifdef WIN32
            m_time = numeric_limits <int>::max();  // Win32 uses STL
#else
        m_time = INT_MAX;
#endif

        m_bRolling = false;
        m_rollDir = DIR_NORTH;
        m_rollSpeed = 250.0; // TODO: dyn.
//        m_rollSpeed = 20.0;
        m_rollPixPos = 0.0;
    }


    Bomb::Bomb(const Bomb & rhs)
        : Cell (rhs)
    {
        m_player = rhs.m_player;
        m_type = rhs.m_type;
        m_nBombID = rhs.m_nBombID;
        m_flame_length = rhs.m_flame_length;
        m_time = rhs.m_time;
        m_start_time = rhs.m_start_time;
        m_bTriggered = rhs.m_bTriggered;
        m_bRolling = rhs.m_bRolling;
        m_rollDir = rhs.m_rollDir;
        m_rollSpeed = rhs.m_rollSpeed;
        m_rollPixPos = rhs.m_rollPixPos;
    }

    Bomb::~Bomb()
    {
    }

    void
    Bomb::draw()
    {
        Globals g;

        if (g.timer().time() - m_start_time >= m_time / 1000.0)
        {
            m_bTriggered = true;
            delete_me();
        }

        // TODO: draw gescheit!

        int w = g.values().cell_w();
        int h = g.values().cell_h();

        anim().Update();

        if (!m_bRolling)
        {
            anim().Draw(x() * w + w / 2, y() * h + h, h - 2, h - 2);
        }
        else
        {
            if (m_rollDir == DIR_NORTH || m_rollDir == DIR_SOUTH)
            {
                if (m_rollDir == DIR_NORTH)
                    m_rollPixPos -= m_rollSpeed * g.timer().frame_time();
                else
                    m_rollPixPos += m_rollSpeed * g.timer().frame_time();

                anim().Draw(x() * w + w / 2, y() * h + h + m_rollPixPos, h - 2, h - 2);
            }
            else
            {
                if (m_rollDir == DIR_WEST)
                    m_rollPixPos -= m_rollSpeed * g.timer().frame_time();
                else
                    m_rollPixPos += m_rollSpeed * g.timer().frame_time();

                anim().Draw(x() * w + w / 2 + m_rollPixPos, y() * h + h, h - 2, h - 2);
            }
        }

        SDL_Rect r = {x() * w + w / 2, y() * h + h / 2, 2, 2};
        g.render().FillRect(r, 1.0, 0.0, 1.0);

        double fr = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0R + player() * 3)) / 255.0;
        double fg = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0G + player() * 3)) / 255.0;
        double fb = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0B + player() * 3)) / 255.0;

        g.render().SetTextSizes(16, 16);
        g.render().DrawText(x() * w + w / 2, y() * h + h / 2, fr, fg, fb,
"player(FIXME)");//                            "%d", player()); // FIXME

        if (m_type == BOMB_TRIGGER)
            g.render().DrawText(x() * w + w / 2 + 10, y() * h + h / 2, fr, fg, fb,
                                "Tr");

        if (m_type == BOMB_JELLY)
            g.render().DrawText(x() * w + w / 2 - 20, y() * h + h / 2, fr, fg, fb,
                                "Je");

    }

    bool
    Bomb::solid() const
    {
        return true;
    }

    int
    Bomb::player()
    {
        return m_player;
    }


    bool
    Bomb::triggered()
    {
        return m_bTriggered;
    }


    void
    Bomb::trigger(bool flame_delay)
    {
        stop_rolling();
        
        if (!flame_delay)
        {
            // trigger immediately...
            m_start_time = -m_time / 1000.0 + Globals::timer().time();
        }
        else
        {
            // bomb will wait VAL_TIME_FLAME_TRIGGER milliseconds maximum...

// orig:
//        double start_time = m_start_time - m_time / 1000.0
//            + Globals::values().get(VAL_TIME_FLAME_TRIGGER) / 1000.0
//            + (Globals::timer().time() - m_start_time);


            double start_time =  -m_time / 1000.0
                + Globals::values().get(VAL_TIME_FLAME_TRIGGER) / 1000.0
                + Globals::timer().time();


            // apply only if new time is shorter than the elder one...
            if (start_time < m_start_time)
                m_start_time = start_time;
        }
    }

    int
    Bomb::flame_length()
    {
        return m_flame_length;
    }

    EnumBombType
    Bomb::type()
    {
        return m_type;
    }

    UINT
    Bomb::bomb_id()
    {
        return m_nBombID;
    }




    void
    Bomb::kick(EnumDir dir)
    {
        m_bRolling = true;
        m_rollDir = dir;

       Globals g;
       g.sound().play(g.soundlist().get_random_sound(SND_BOMB_KICK));
    }

    void
    Bomb::stop_rolling()
    {
        m_bRolling = false;
        m_rollPixPos = 0.0;

        Globals g;
//        g.sound().play(g.soundlist().get_random_sound(SND_BOMB_STOP));
    }

    bool
    Bomb::rolling() const
    {
        return m_bRolling;
    }

    EnumDir
    Bomb::roll_dir() const
    {
        return m_rollDir;
    }

    bool
    Bomb::out_of_cell(bool outofcenter)
    {
        Globals g;
        double w = g.values().cell_w();
        double h = g.values().cell_h();

        if (m_rollDir == DIR_NORTH)
        {
            if (outofcenter && m_rollPixPos <= 0)
                return true;
            else if (m_rollPixPos < -h / 2.0)
                return true;
        }
        else if (m_rollDir == DIR_SOUTH)
        {
            if (outofcenter && m_rollPixPos >= 0)
                return true;
            else if (m_rollPixPos > h / 2.0)
                return true;        
        }
        else if (m_rollDir == DIR_WEST)
        {
            if (outofcenter && m_rollPixPos <= 0)
                return true;
            else if (m_rollPixPos < -w / 2.0)
                return true;        
        }
        else if (m_rollDir == DIR_EAST)
        {
            if (outofcenter && m_rollPixPos >= 0)
                return true;
            else if (m_rollPixPos > w / 2.0)
                return true;        
        }

        return false;
    }

    void
    Bomb::prepare_for_copy()
    {
        Globals g;
        double w = g.values().cell_w();
        double h = g.values().cell_h();

        double newpos = 0.0;

        if (m_rollDir == DIR_NORTH)
        {
            newpos = m_rollPixPos + h;
            set_y (y() - 1);
        }
        else if (m_rollDir == DIR_SOUTH)
        {
            newpos = m_rollPixPos - h;
            set_y (y() + 1);
        }
        else if (m_rollDir == DIR_WEST)
        {
            newpos = m_rollPixPos + w;
            set_x (x() - 1);
        }
        else if (m_rollDir == DIR_EAST)
        {
            newpos = m_rollPixPos - w;
            set_x (x() + 1);
        }

        m_rollPixPos = newpos;
    }
}
