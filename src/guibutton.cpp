/**
 * file: button.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "guibutton.h"

#include <SDL/SDL_keysym.h>

namespace gui
{

    Button::Button()
        : Base(), m_caption(""), m_button_pressed(false)
    {
    }

    Button::~Button()
    {
    }

    // key events; overwrite!
    void Button::on_key_down(UINT keysym)
    {
        Base::on_key_down(keysym);

        if (has_focus())
        {
            if (keysym == SDLK_SPACE || keysym == SDLK_RETURN)
                set_button_pressed(true);
        }
    }

    void Button::on_key_up(UINT keysym)
    {
        Base::on_key_up(keysym);

        // send click event
        if (has_focus())
        {
            if (keysym == SDLK_SPACE || keysym == SDLK_RETURN)
            {
                if (button_pressed())
                {
                    set_button_pressed(false);
                    click();
                }
            }
        }
        else
        {
            set_button_pressed(false);
        }
    }

    // mouse events; overwrite!
    void Button::on_mouse_up(int x, int y)
    {
        // send click event
        if (has_focus() && mouse_down() && mouse_over())
        {
            click();
        }
        else
        {
            set_button_pressed(false);
        }

        Base::on_mouse_up(x, y);
    }
    
    // clicking with the mouse or pressing ENTER or RETURN or SPACE will call Button::click
    void Button::click()
    {
    }

    // caption routines
    void Button::set_caption(string cap)
    {
        m_caption = cap;
    }

    string Button::caption() const
    {
        return m_caption;
    }

    /**
     * draw border
     */
    Base::ButtonState Button::draw_border()
    {
        if (has_focus())
        {
            if (mouse_down() || button_pressed())
            {
                Base::draw_border(BS_MOUSE_DOWN);
                return BS_MOUSE_DOWN;
            }
            else
            {
                Base::draw_border(BS_HAS_FOCUS);
                return BS_HAS_FOCUS;
            }
        }
        else
        {
            if (mouse_over())
            {
                Base::draw_border(BS_MOUSE_OVER);
                return BS_MOUSE_OVER;
            }
            else
            {
                Base::draw_border(BS_NOT_FOCUSED);
                return BS_NOT_FOCUSED;
            }
        }
    }

    ///////////////////
    // protected members
    ///////////////////

    void Button::set_button_pressed(bool b_pressed)
    {
        m_button_pressed = b_pressed;
    }

    bool Button::button_pressed() const
    {
        return m_button_pressed;
    }
}
