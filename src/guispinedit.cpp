/**
 * file: guispinedit.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "guispinedit.h"

#include "globals.h"
#include "render.h"

#include <sstream>
#include <iostream>

namespace gui
{
    SpinEdit::SpinEdit()
        : TextEdit(), m_range_min(-100), m_range_max(100)
    {
        set_value(0);
    }

    SpinEdit::SpinEdit(string val)
        : TextEdit(val), m_range_min(-100), m_range_max(100)
    {
    }
    
    SpinEdit::SpinEdit(int val)
        : TextEdit(), m_range_min(-100), m_range_max(100)
    {
        set_value(val);
    }

    SpinEdit::~SpinEdit()
    {
    }

    void SpinEdit::on_key_down(UINT keysym)
    {
        Base::on_key_down(keysym);
        if (!has_focus()) return;

        if (keysym == SDLK_LEFT)
        {
            dec(1);
            text_changed();
            return;
        }

        if (keysym == SDLK_RIGHT)
        {
            inc(1);
            text_changed();
            return;
        }

        if (keysym == SDLK_BACKSPACE)
        {
            set_value(0);
            text_changed();
            return;
        }

        if (keysym == SDLK_DELETE)
        {
            set_value(0);
            text_changed();
            return;
        }

        if (keysym == SDLK_MINUS || keysym == SDLK_KP_MINUS)
        {
            dec(1);
            text_changed();
            return;
        }

        if (keysym == SDLK_PLUS || keysym == SDLK_KP_PLUS)
        {
            inc(1);
            text_changed();
            return;
        }

        // numbers: (could be implemented better)
        if (keysym == SDLK_0 || keysym == SDLK_KP0)
        {
            m_text.insert(m_cur_pos, "0");
            text_changed();
            return;
        }

        if (keysym == SDLK_1 || keysym == SDLK_KP1)
        {
            m_text.insert(m_cur_pos, "1");
            text_changed();
            return;
        }

        if (keysym == SDLK_2 || keysym == SDLK_KP2)
        {
            m_text.insert(m_cur_pos, "2");
            text_changed();
            return;
        }

        if (keysym == SDLK_3 || keysym == SDLK_KP3)
        {
            m_text.insert(m_cur_pos, "3");
            text_changed();
            return;
        }

        if (keysym == SDLK_4 || keysym == SDLK_KP4)
        {
            m_text.insert(m_cur_pos, "4");
            text_changed();
            return;
        }

        if (keysym == SDLK_5 || keysym == SDLK_KP5)
        {
            m_text.insert(m_cur_pos, "5");
            text_changed();
            return;
        } 

        if (keysym == SDLK_6 || keysym == SDLK_KP6)
        {
            m_text.insert(m_cur_pos, "6");
            text_changed();
            return;
        }

        if (keysym == SDLK_7 || keysym == SDLK_KP7)
        {
            m_text.insert(m_cur_pos, "7");
            text_changed();
            return;
        }

        if (keysym == SDLK_8 || keysym == SDLK_KP8)
        {
            m_text.insert(m_cur_pos, "8");
            text_changed();
            return;
        }

        if (keysym == SDLK_9 || keysym == SDLK_KP9)
        {
            m_text.insert(m_cur_pos, "9");
            text_changed();
            return;
        } 
    }

    /**
     * mouse down
     */
    void SpinEdit::on_mouse_down(int x, int y)
    {
        Base::on_mouse_down(x, y);

        if (has_focus())
        {
            if (x < (m_x + 42))
            {
                dec(1);
                text_changed();
            }
            else
            {
                if (x > (m_x + m_w - 42))
                {
                    inc(1);
                    text_changed();
                }
            }
        }
    }

    /**
     * returns the value
     */
    int SpinEdit::value() const
    {
        // convert string to int
        return (m_text.size() == 0)? 0 : atoi(m_text.c_str());
    }

    /**
     * set the value
     */
    void SpinEdit::set_value(int val)
    {
        if (val == 0)
        {
            m_text = "0";
        }
        else
        {
            // convert an int to string using a stringstream
            std::stringstream ss;
            ss << val;
            ss >> m_text;
        }
    }

    /**
     * increase value by n
     */
    void SpinEdit::inc(int n)
    {
        stringstream ss;
        ss << value() + n;
        ss >> m_text;
    }

    /**
     * decrease value by n
     */
    void SpinEdit::dec(int n)
    {
        stringstream ss;
        ss << value() - n;
        ss >> m_text;
    }

    /**
     * set the value; note: val must be a number; else undefined behaviour!
     */
    void SpinEdit::set_value(string val)
    {
        m_text = val;
    }

    /**
     * called when the text changed; emits signal.
     */
    void SpinEdit::text_changed()
    {
        if (value() > m_range_max)
        {
            set_value(m_range_max);
            m_cur_pos = 0;
        }

        if (value() < m_range_min)
        {
            set_value(m_range_min);
            m_cur_pos = 0;
        }

        TextEdit::text_changed();
    }

    /**
     * set rænge
     */
    void SpinEdit::set_range(int min, int max)
    {
        if (min < max)
        {
            m_range_min = min;
            m_range_max = max;
        }
    }

    /**
     * set the text
     */
    void SpinEdit::set_text(string text)
    {
        set_value(text);
    }

    /**
     * get the text
     */
    string SpinEdit::text() const
    {
        return m_text;
    }

    /**
     * draw; overwrite
     */
    void SpinEdit::draw()
    {
        ButtonState bs = draw_border();

        SDL_Rect r = wnd_size();
        r.x += 30;
        r.w -= 60;

        Globals g;

        switch (text_alignment())
        {
            case TAL_LEFT:
                {
                    g.render().DrawText(r.x + 15, r.y + r.h/2 - m_font_size_w/2, 1,1,1, m_text);
                    break;
                }
            case TAL_CENTER:
                {
                    g.render().DrawText(wnd_size(), 1,1,1, m_text);
                    break;
                }
            case TAL_RIGHT:
                {
                    g.render().DrawText(r.x + r.w - g.render().TextWidth(m_text) - 15, r.y + r.h/2 - m_font_size_h/2, 1, 1, 1, m_text);
                    break;
                }
        }

        draw_plus_minus(bs);
    }

    void SpinEdit::draw_plus_minus(ButtonState bs)
    {
        Globals g;

        TexInfo *plus, *minus;
        plus = minus = 0;

        switch (bs)
        {
            case BS_MOUSE_OVER:
                {
                    plus  = g.render().LoadTexture(img_path() + "spe_mo_pls.tga");
                    minus = g.render().LoadTexture(img_path() + "spe_mo_mns.tga");

                    break;
                }

            case BS_MOUSE_DOWN:
                {
                    plus  = g.render().LoadTexture(img_path() + "spe_md_pls.tga");
                    minus = g.render().LoadTexture(img_path() + "spe_md_mns.tga");

                    break;
                }

            case BS_HAS_FOCUS:
                {
                    plus  = g.render().LoadTexture(img_path() + "spe_hf_pls.tga");
                    minus = g.render().LoadTexture(img_path() + "spe_hf_mns.tga");

                    break;
                }

            case BS_NOT_FOCUSED:
                {
                    plus  = g.render().LoadTexture(img_path() + "spe_nf_pls.tga");
                    minus = g.render().LoadTexture(img_path() + "spe_nf_mns.tga");

                    break;
                }
            case BS_NONE: // will not happen; just to avoid compiler warning;
                {
                    cerr << "SpinEdit::draw_plus_minus: BS_NONE called. This may not happen!" << endl;
                    break;
                }

        }

        int x = m_x + 17;
        int y = m_y + (m_h / 2) - 12;

        // draw plus and minus
        if (plus ) g.render().DrawTile(x, y, 25, 25, minus);
        if (minus) g.render().DrawTile(m_x + m_w - 12 - 30, y, 25, 25, plus);
    }
}
