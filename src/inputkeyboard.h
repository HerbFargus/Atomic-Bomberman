// v0.1  by gm (created)
// v0.11 by gm (development phase)
// v0.2  by gm (minor changes, release-candidate)

/**
 *
 * Classname / filename: Keyboard / keyboard.h
 *
 * Author: gm
 *
 * Version: 0.1
 *
 */

/******************************************************************************
 *                                                                            *
 * LICENSE: GPL v2 (General Public License v2)                                *
 *                                                                            *
 ******************************************************************************/

#ifndef CONTROLKEYBOARD_H
#define CONTROLKEYBOARD_H

#include "input.h"

namespace input
{

/**
 * ControlKeyboard
 */
    class Keyboard : public Input
    {
    public:
        /**
         * constructs a Keyboard object
         * keyset: 0..1  =  there are two different keysets
         */
        Keyboard(int keyset);
        virtual ~Keyboard();

        void update_keyboard(UINT keysym, bool bDown);

    protected:
        /**
         * updates the keystate for the key 'key'
         */
        void update_key (EnumPlayerKeys key, UINT keysym, bool bDown);


    private:
        /**
         * key0 or key1
         */
        int m_keyset;

    };

}
#endif // CONTROLKEYBOARD_H
