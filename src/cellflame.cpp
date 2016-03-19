// v0.1  by gm (created)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "cellflame.h"
#include "globals.h"
#include "valuelist.h"
#include "animmng.h"
#include "timer.h"
#include <iostream>

namespace cell
{
    using namespace std;

    Flame::Flame(int x, int y, int nPlayer, EnumFlameType type)
        : Cell(x, y),
          m_type(type),
          m_player(nPlayer)
    {
        m_start_time = Globals::timer().time();
        anim().SetAnimation(ANI_FLAME, m_type);         // todo: Animation besser machen (done ???)
        anim().Start();
    }

    Flame::~Flame()
    {
    }
    
    EnumFlameType
    Flame::type() const
    {
        return m_type;
    }
    
    bool
    Flame::solid() const
    {
        return false;
    }


    void
    Flame::draw()
    {
        Globals g;
        int w = g.values().cell_w();
        int h = g.values().cell_h();

        anim().Update();
        anim().Draw(x() * w, y() * h, w, h);

        g.render().SetTextSizes(16, 16);

        double fr = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0R + player() * 3)) / 255.0;
        double fg = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0G + player() * 3)) / 255.0;
        double fb = g.values().get(static_cast < EnumValues > (VAL_COLOR_PLAYER_0B + player() * 3)) / 255.0;

        g.render().DrawText(x() * w + w / 2, y() * h + h / 2, fr, fg, fb,
"player()FIXME"); //                            "%d", player()); // FIXME

        if (g.timer().time() - m_start_time >= g.values().get(VAL_TIME_FLAME) / 1000.0)
            delete_me();
    }

    int
    Flame::player() const
    {
        return m_player;
    }

}
