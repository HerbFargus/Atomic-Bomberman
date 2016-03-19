// v0.1  by gm (created)
// v0.11 by gm (development phase)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "input.h"

namespace input
{
    Input::Input()
        : m_EventPressed (KEY_PLAYER_NUMBER_OF),
          m_EventJustPressed (KEY_PLAYER_NUMBER_OF)    // important! (it's a vector)
    {
    }

    Input::~Input()
    {
    }

    bool Input::pressed (EnumPlayerKeys which)
    {
        return m_EventPressed[which];
    }

    bool Input::just_pressed (EnumPlayerKeys which)
    {
        bool bPressd = m_EventJustPressed[which];

        if (m_EventJustPressed[which])
            m_EventJustPressed[which] = false;

        return bPressd;
    }

    void Input::key_is_pressed (EnumPlayerKeys which)
    {
        if (!m_EventPressed[which])
            m_EventJustPressed[which] = true;

        m_EventPressed[which] = true;
    }

    void Input::key_is_released (EnumPlayerKeys which)
    {
        m_EventPressed[which] = false;
    }
    
    void Input::key_down (EnumPlayerKeys which)
    {
        m_EventJustPressed[which] = true;        
        m_EventPressed[which] = true;
    }
    
    void Input::key_up(EnumPlayerKeys which)
    {
        m_EventJustPressed[which] = false;        
        m_EventPressed[which] = false;    
    }

}
