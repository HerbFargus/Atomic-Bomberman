// v0.1  by gm (created)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "inputmouse.h"
#include "player.h"
#include "globals.h"
#include "valuelist.h"
#include "timer.h"
#include <iostream>

namespace input
{
    using namespace std;

    Mouse::Mouse()
        : m_pPlayer (0)
    {
//     Globals g;
//     int cx = g.values().get(VAL_FIELD_OFFSET_X);
//     int cy = g.values().get(VAL_FIELD_OFFSET_Y);

//     SDL_WarpMouse(m_rPlayer.pixelpos_x() + cx, m_rPlayer.pixelpos_y() + cy);

        m_startTime = 0;
        m_oldDir = KEY_DOWN;
    }

    Mouse::~Mouse()
    {
    }

    void
    Mouse::set_player(const Player* player)
    {
        m_pPlayer = player;
        SDL_WarpMouse(static_cast <int> (m_pPlayer->pixelpos_x()), static_cast <int> (m_pPlayer->pixelpos_y()));
    }

    // TODO: F machen
    void
    Mouse::update_mouse_motion(int x, int y)
    {
        if (!m_pPlayer)
        {
            cerr << "input::Mouse::update_mouse_motion(...): m_pPlayer == 0 (must be set up with set_player())" << endl;
            return;
        }

        static bool no = true;
        if (no)
        {
            no = false;
//         key_up (KEY_RIGHT);
//         key_up (KEY_LEFT);
//         key_up (KEY_DOWN);
//         key_up (KEY_UP);
            return;
        }

        Globals g;

        m_startTime = g.timer().time();

        double cx = g.values().get(VAL_FIELD_OFFSET_X);
        double cy = g.values().get(VAL_FIELD_OFFSET_Y);

//    int threshold_x = g.values().get(VAL_CELL_W) / 2;
//    int threshold_y = g.values().get(VAL_CELL_H) / 2;

//     double diff_east  =  x - (m_rPlayer.pixelpos_x() + cx);
//     double diff_west  =  -(x - (m_rPlayer.pixelpos_x() + cx));
//     double diff_south =  y - (m_rPlayer.pixelpos_y() + cy);
//     double diff_north =  -(y - (m_rPlayer.pixelpos_y() + cy));

        double px = m_pPlayer->pixelpos_x() + cx;
        double py = m_pPlayer->pixelpos_y() + cy;

        double diff_east  =  x - m_oldX;
        double diff_west  =  -(x - m_oldX);
        double diff_south =  y - m_oldY;
        double diff_north =  -(y - m_oldY);


        bool bDiff = true;

        EnumPlayerKeys dir = KEY_RIGHT;  // some unimportant initialization
        double offset = 0.0;

        if (diff_east > diff_west + offset && diff_east > diff_north + offset && diff_east > diff_south + offset)
            dir = KEY_RIGHT;
        else if (diff_west > diff_east + offset && diff_west > diff_north + offset && diff_west > diff_south + offset)
            dir = KEY_LEFT;
        else if (diff_north > diff_west + offset && diff_north > diff_east + offset && diff_north > diff_south + offset)
            dir = KEY_UP;
        else if (diff_south > diff_west + offset && diff_south > diff_north + offset && diff_south > diff_east + offset)
            dir = KEY_DOWN;
        else
            bDiff = false;

        if (bDiff)
        {
            key_up(m_oldDir);
            key_down(dir);
            m_oldDir = dir;
        }
        else
        {

        }

        SDL_WarpMouse(static_cast <int> (px), static_cast <int> (py));
        m_oldX = static_cast <int> (px);
        m_oldY = static_cast <int> (py);
        no = true;

//    cout << "TEST   " << diff_east << " " << diff_west << " " << diff_south << " " << diff_north << " " << endl;



//     if (x > m_rPlayer.pixelpos_x() + cx + threshold_x)
//         key_is_pressed (KEY_RIGHT);
//     else if (x < m_rPlayer.pixelpos_x() + cx - threshold_x)
//         key_is_pressed (KEY_LEFT);
//     else if (y > m_rPlayer.pixelpos_y() + cy + threshold_y)
//         key_is_pressed (KEY_DOWN);
//     else if (y < m_rPlayer.pixelpos_y() + cy - threshold_y)
//         key_is_pressed (KEY_UP);


    }

    void
    Mouse::maybe_stop_mousemotion()
    {
        Globals g;
        double curTime = g.timer().time();
        if (curTime - m_startTime > 0.01)
        {
            key_up (KEY_RIGHT);
            key_up (KEY_LEFT);
            key_up (KEY_DOWN);
            key_up (KEY_UP);
        }
    }

    void
    Mouse::update_mouse_button(int button, bool bDown)
    {
        if (0 == button)
            if (bDown)
                key_down (KEY_BOMB);
            else
                key_up (KEY_BOMB);

        else if (1 == button)
            if (bDown)
                key_down (KEY_SPECIAL);
            else
                key_up (KEY_SPECIAL);

    }
}
