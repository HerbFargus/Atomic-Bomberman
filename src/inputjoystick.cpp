// v0.1  by gm (created)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "inputjoystick.h"
#include <SDL/SDL.h>
#include <iostream>

namespace input
{
    using namespace std;

    Joystick::Joystick(int joystick)
    {
        m_pJoystick = SDL_JoystickOpen(joystick);

        // TODO: testen

        if (joystick < SDL_NumJoysticks())
        {
            m_pJoystick = SDL_JoystickOpen(joystick);

            if (m_pJoystick)
            {
                cout << "Joystick::Joystick(" << joystick << ")\n";
                cout << "  name: " << SDL_JoystickName(joystick) << "\n";
                cout << "  number of axes: " << SDL_JoystickNumAxes(m_pJoystick) << "\n";
                cout << "  number of buttons: " << SDL_JoystickNumButtons(m_pJoystick) << "\n";
                cout << "  number of balls: " << SDL_JoystickNumBalls(m_pJoystick) << endl;
            }
            else
            {
//                MessageBox(0, "", "", MB_OK);
                cerr << "Error: Joystick::Joystick(" << joystick << "): couldn't open Joystick." << endl;
            }

            // TODO: verbessern ???:

#ifdef WIN32
            m_nThresholdLow = -3200;
            m_nThresholdHigh = 3200;
#else
            m_nThresholdLow = 500;
            m_nThresholdHigh = 4000;
#endif
        }
    }

    Joystick::~Joystick()
    {
        if (m_pJoystick && SDL_JoystickOpened(SDL_JoystickIndex(m_pJoystick)))
            SDL_JoystickClose(m_pJoystick);

    }

    void
    Joystick::update_joybutton(int button, int bDown)
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

    void
    Joystick::update_joyaxis(int axis, int value)
    {
        axis = 0;

        if (SDL_JoystickGetAxis(m_pJoystick, axis) > m_nThresholdHigh)
            key_down (KEY_RIGHT);
        else
            key_up (KEY_RIGHT);

        if (SDL_JoystickGetAxis(m_pJoystick, axis) < m_nThresholdLow)
            key_down (KEY_LEFT);
        else
            key_up (KEY_LEFT);

        axis = 1;

        if (SDL_JoystickGetAxis(m_pJoystick, axis) > m_nThresholdHigh)
            key_down (KEY_DOWN);
        else
            key_up (KEY_DOWN);

        if (SDL_JoystickGetAxis(m_pJoystick, axis) < m_nThresholdLow)
            key_down (KEY_UP);
        else
            key_up (KEY_UP);

    }

//void Joystick::update_joyaxis(int axis, int value)
//{
//
//            if (0 == axis && value > m_nThreshold)
//                key_down (KEY_RIGHT);
//            else
//                key_up (KEY_RIGHT);
//
//            if (0 == axis && value < -m_nThreshold)
//                key_down (KEY_LEFT);
//            else
//                key_up (KEY_LEFT);
//
//            if (1 == axis && value > m_nThreshold)
//                key_down (KEY_DOWN);
//            else
//                key_up (KEY_DOWN);
//
//            if (1 == axis && value < -m_nThreshold)
//                key_down (KEY_UP);
//            else
//                key_up (KEY_UP);
//}

// void Joystick::key_down (EnumPlayerKeys which)
// {
// }

// void Joystick::key_up (EnumPlayerKeys which)
// {
// }

}
