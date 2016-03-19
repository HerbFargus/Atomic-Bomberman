/**
 * file: guitextedit.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "guitextedit.h"

#include "globals.h"
#include "render.h"

namespace gui
{

    TextEdit::TextEdit()
        : Base(), m_cur_pos(0), m_lshift(false), m_rshift(false), m_cursor_timestep(SDL_GetTicks()), m_cursor_opacity(0.0), m_cursor_inc(true)
    {
    }

    TextEdit::TextEdit(string text)
        : Base(), m_text(text), m_cur_pos(0), m_lshift(false), m_rshift(false), m_cursor_timestep(SDL_GetTicks()), m_cursor_opacity(0.0), m_cursor_inc(true)
    {
    }
 
    TextEdit::~TextEdit()
    {
    }

    /**
     * set the text
     */
    void TextEdit::set_text(string text)
    {
        m_text = text;
    }

    /**
     * get the text
     */
    string TextEdit::text() const
    {
        return m_text;
    }

    /**
     * cursor position: navigate left / right
     */
    void TextEdit::navigate_left(bool bleft)
    {
        if (bleft)
        {
            if (m_cur_pos > 0)
                 --m_cur_pos;
        }
        else
        {
            if (m_text.length() > m_cur_pos)
            {
                ++m_cur_pos;
            }
        }
    }

    void TextEdit::on_key_down(UINT keysym)
    {
        Base::on_key_down(keysym);
        if (!has_focus()) return;

        if (keysym == SDLK_RSHIFT)
        {
            m_rshift = true;
        }

        if (keysym == SDLK_LSHIFT)
        {
            m_lshift = true;
        }
    
        if (keysym == SDLK_LEFT)
        {
            navigate_left(true);
        }

        if (keysym == SDLK_RIGHT)
        {
            navigate_left(false);
        }

        if (m_lshift || m_rshift)
        {
            if (keysym >= 79 && keysym <= 122)
            {
                keysym-= 32;
            }
            else
            {
//                if (keysym
            }
        }

        if (keysym >= 32 && keysym < 127)
        {
            char c = keysym;
            string s;
            s += c;
            m_text.insert(m_cur_pos, s);
            navigate_left(false);
            text_changed();
        }

        if (keysym == SDLK_BACKSPACE)
        {
            if (m_cur_pos > 0)
            {
                m_text.erase(m_cur_pos - 1, 1);
                --m_cur_pos;
                text_changed();
            }
        }

        if (keysym == SDLK_DELETE)
        {
            if (m_cur_pos < m_text.length())
            {
                m_text.erase(m_cur_pos, 1);
                text_changed();
            }
        }

    }

    /**
     * key up
     */
    void TextEdit::on_key_up(UINT keysym)
    {
        Base::on_key_up(keysym);

        if (keysym == SDLK_LSHIFT)
        {
            m_lshift = false;
        }

        if (keysym == SDLK_RSHIFT)
        {
            m_rshift = false;
        }
    }

    /**
     * draw; overwrite
     */
    void TextEdit::draw()
    {
        draw_border();

        Globals g;

        switch (text_alignment())
        {
            case TAL_LEFT:
            {
                g.render().DrawText(m_x + 15, m_y + m_h/2 - m_font_size_w/2, 1,1,1, m_text);
                break;
            }
            case TAL_CENTER:
            {
                g.render().DrawText(wnd_size(), 1,1,1, m_text);
                break;
            }
            case TAL_RIGHT:
            {
                g.render().DrawText(m_x + m_w - g.render().TextWidth(m_text) - 15, m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, m_text);
                break;
            }
        }
        
        if (has_focus()) draw_cursor(wnd_size());
    }

    /**
     * draw cursor position
     */
    void TextEdit::draw_cursor(SDL_Rect rect)
    {
        if (SDL_GetTicks() - m_cursor_timestep > 10)
        {
            m_cursor_timestep = SDL_GetTicks();
            
            if (m_cursor_inc)
            {
                m_cursor_opacity += 0.05;
                if (m_cursor_opacity > 1.0)
                {
                    m_cursor_opacity = 1.0;
                    m_cursor_inc = false;
                }
            }
            else
            {
                m_cursor_opacity -= 0.05;
                if (m_cursor_opacity < 0.0)
                {
                    m_cursor_opacity = 0.0;
                    m_cursor_inc = true;
                }
            }
        }
        
        Globals g;

        int first_text = 0;

        switch (text_alignment())
        {
            case TAL_LEFT:
            {
                first_text = 15;
                break;
            }
            case TAL_CENTER:
            {
                first_text = rect.w/2 - g.render().TextWidth(m_text)/2;
                break;
            }
            case TAL_RIGHT:
            {
                first_text = rect.w - 15 - g.render().TextWidth(m_text);
                break;
            }
        }

        int dx = g.render().TextWidth(m_text.substr(0, m_cur_pos));

        SDL_Rect r = { rect.x + first_text + dx, rect.y + m_h/2 - m_font_size_h/2, 3, m_font_size_h};

        g.render().FillRect(r, 1, 1, 0, m_cursor_opacity);
    }

    /**
     * draw the border
     */
    Base::ButtonState TextEdit::draw_border()
    {
        if (has_focus())
        {
            if (mouse_down())
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

    /**
     * called when the text changed; emits signal.
     */
    void TextEdit::text_changed()
    {
        // emit signal
        on_changed.emit();
    }
}
