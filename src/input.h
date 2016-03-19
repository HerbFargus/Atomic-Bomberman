// v0.1  by gm (created)
// v0.11 by gm (development phase)

/**
 *
 * Classname / filename: Input / input.h
 *
 * Author: Gregor Mitsch
 *
 * Version: 0.1
 *
 */

/******************************************************************************
 *                                                                            *
 * LICENSE: GPL v2 (General Public License v2)                                *
 *                                                                            *
 ******************************************************************************/

#ifndef INPUT_H
#define INPUT_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <vector>
using std::vector;

#include "typedefs.h"
#include "enumkeys.h"

namespace input
{
/**
 * Input:
 * Interface to control player movement and actions
 */
    class Input
    {
    public:
        Input();
        virtual ~Input();

        /**
         * returns true, if player action 'which' is pressed (or enable by mouse action, gamepad, ai, ...)
         */
        bool pressed (EnumPlayerKeys which);

        /**
         * returns true, if player action 'which' was just pressed
         */
        bool just_pressed (EnumPlayerKeys which);

    protected:
        /**
         * these functions are called by classes derived from Input
         * to determine the behaviour of the control state
         */
        void key_is_pressed (EnumPlayerKeys which);
        void key_is_released(EnumPlayerKeys which);

        /**
         * entweder ^ oder v    (TODO: doc)
         */
        void key_down (EnumPlayerKeys which);
        void key_up(EnumPlayerKeys which);


    private:
        typedef vector < bool > EventMap;

        /**
         * true, if player action is enabled, pressed, ...
         */
        EventMap m_EventPressed;

        /**
         * true, if player action was just pressed
         */
        EventMap m_EventJustPressed;
    };
}

#endif // INPUT_H
