// v0.1 by gm (created)

#include "cellbreakable.h"
#include "globals.h"
#include "gameinfo.h"
#include "valuelist.h"
#include "timer.h"
#include "cellpowerup.h"
#include <iostream>

namespace cell
{

    using namespace std;

    Breakable::Breakable (int x, int y)
        : Cell(x, y),
          m_bHasPowerup (false),
          m_bBreak (false)
    {
        anim().SetAnimation(ANI_TILE_NONSOLID, Globals::game().map());        // todo: Animation langsamer (siehe Player) (done???)
    }

    Breakable::~Breakable ()
    {

    }

    void
    Breakable::draw()
    {
        Globals g;
        int w = g.values().cell_w();
        int h = g.values().cell_h();

        if (m_bBreak)
        {
            anim().Update();
            if (g.timer().time() - m_start_time >= g.values().get(VAL_TIME_BRICK_DISINTEGRATE) / 1000.0)
                delete_me();
        }

        anim().Draw(x() * w, y() * h, w, h);

        if (m_bHasPowerup && g.values().get(VAL_SHOW_POWERUPS_IN_BRICKS))
        {
            cell::Powerup bp(x(), y(), m_powerup, true);
            bp.draw();
        }
    }

    bool
    Breakable::solid() const
    {
        return true;
    }

    void
    Breakable::break_it()
    {
        if (!m_bBreak)
        {
            m_bBreak = true;
            anim().Start();
            m_start_time = Globals::timer().time();
        }
    }

    void
    Breakable::set_powerup(EnumPowerups which)
    {
        m_bHasPowerup = true;
        m_powerup = which;
    }
    
    bool
    Breakable::has_powerup() const
    {
        return m_bHasPowerup;
    }
    
    EnumPowerups
    Breakable::powerup() const
    {
        if (has_powerup())
            return m_powerup;
        else
        {
            cerr << "Error cell::Breakable: powerup() was called, but has_powerup() was false. Return PU_BOMB." << endl;
            return PU_BOMB;
        }
    }
}
