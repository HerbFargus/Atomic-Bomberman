// v0.1  by gm (created)

/**
 *
 * Classname / filename: Joystick / joystick.h
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

#ifndef CONTROLJOYSTICK_H
#define CONTROLJOYSTICK_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include "input.h"
#include "SDL/SDL.h"


// todo: Alles!!!

namespace input
{

/**
 * ControlJoystick
 */
    class Joystick : public Input
    {
    public:
        Joystick(int joystick);
        virtual ~Joystick();
        
        void update_joybutton(int button, int bDown);
        void update_joyaxis(int axis, int value);
        


    protected:
//    void key_down (EnumPlayerKeys which);
//    void key_up   (EnumPlayerKeys which);

    private:
        SDL_Joystick *m_pJoystick;

        int m_nThresholdLow;
        int m_nThresholdHigh;

    };

}
#endif // CONTROLJOYSTICK_H
