// v0.1  by gm (created)

/* Run:
   (setq my-var-run-cmd "gcalc")
   ./ab_linux &
   pkill ab_linux
*/

/**
 *
 * Classname / filename: Mouse / mouse.h
 *
 * Author: g m
 *
 * Version: 0.1
 *
 */

/******************************************************************************
 *                                                                            *
 * LICENSE: GPL v2 (General Public License v2)                                *
 *                                                                            *
 ******************************************************************************/

#ifndef CONTROLMOUSE_H
#define CONTROLMOUSE_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include "input.h"

class Player;

namespace input
{
/**
 * input::Mouse:
 * SDL-BUG: does not work in Win32 Fullscreen Mode
 */
    class Mouse : public Input
    {
    public:
        Mouse();
        virtual ~Mouse();

        /**
         * must be set to player attached to mouse input (TODO: verbessern (weg machen))
         */
        void set_player (const Player* player);

        /**
         * TODO: doc
         *
         */
        void update_mouse_motion (int x, int y);

        void maybe_stop_mousemotion ();

        void update_mouse_button (int button, bool bDown);

    protected:
//    void key_down (EnumPlayerKeys which);
//    void key_up   (EnumPlayerKeys which);

    private:
        int m_oldX;
        int m_oldY;

        /**
         * who own's the control
         */
        const Player* m_pPlayer;

        EnumPlayerKeys m_oldDir;

        float m_startTime;

    };

}
#endif // CONTROLMOUSE_H
