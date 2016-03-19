/**
 * file: update.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "inputupdate.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "inputmouse.h"

namespace input
{
    Update::Update(const SDL_Event& event)
        : m_event (event)
    {
    }


    /**
     * todo: profing, was schneller ist (erst casten, dann event prüfen; oder umgekehrt)
     */

    void
    Update::operator()(PInput& pInput)
    {
        if (Keyboard* pkb = dynamic_cast < Keyboard* > (pInput))
        {
            int type = m_event.type;

            if (SDL_KEYDOWN == type)
                pkb->update_keyboard(m_event.key.keysym.sym, true);
            else if (SDL_KEYUP == type)
                pkb->update_keyboard(m_event.key.keysym.sym, false);

        }
        else if (Joystick* pjs = dynamic_cast < Joystick * > (pInput))
        {
            int type = m_event.type;

            if (SDL_JOYAXISMOTION == type)
                pjs->update_joyaxis(m_event.jaxis.axis, m_event.jaxis.value);
            else if (SDL_JOYBUTTONDOWN == type)
                pjs->update_joybutton(m_event.jbutton.button, true);
            else if (SDL_JOYBUTTONUP == type)
                pjs->update_joybutton(m_event.jbutton.button, false);
        }
        else if (Mouse* pm = dynamic_cast < Mouse * > (pInput))
        {
            int type = m_event.type;

            if (SDL_MOUSEMOTION == type)
                pm->update_mouse_motion(m_event.motion.x, m_event.motion.y);
            else
                pm->update_mouse_button(m_event.button.button==SDL_BUTTON_LEFT?0:1,
                                        m_event.button.type==SDL_MOUSEBUTTONDOWN?1:0);

        }
    }
}
