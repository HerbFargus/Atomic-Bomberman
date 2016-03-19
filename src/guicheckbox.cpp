/**
 * file: guicheckbox.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "guicheckbox.h"

#include "globals.h"
#include "render.h"

#include <iostream>

namespace gui
{

    CheckBox::CheckBox()
        : Button(), m_checked(false), m_chkbox_alignment(CBA_LEFT)
    {
    }

    CheckBox::CheckBox(string cap, bool checked /* = false */)
        : Button(), m_checked(checked), m_chkbox_alignment(CBA_LEFT)
    {
        set_caption(cap);
    }

    CheckBox::~CheckBox()
    {
    }

    bool CheckBox::checked() const
    {
        return m_checked;
    }

    void CheckBox::set_checked(bool checked)
    {
        m_checked = checked;
    }

    bool CheckBox::toggle()
    {
        return m_checked = m_checked?false:true;
    }

    /**
     * set checkbox alignment
     */
    void CheckBox::set_checkbox_alignment(CheckBoxAlignment cba)
    {
        m_chkbox_alignment = cba;
    }

    /**
     * get checkbox alignment
     */
    CheckBoxAlignment CheckBox::checkbox_alignment() const
    {
        return m_chkbox_alignment;
    }

    void CheckBox::click()
    {
        Button::click();

        // clicked -> toggle checkbox
        toggle();

        // emit signal
        on_toggled.emit();
    }

    void CheckBox::draw()
    {
        ButtonState bs = Button::draw_border();
        draw_checkbox(bs);
        
        Globals g;
        
        g.render().SetTextSizes(m_font_size_w, m_font_size_h);

        switch (text_alignment())
        {
            case TAL_LEFT:
            {
                // consider checkbox alignment
                if (checkbox_alignment() == CBA_LEFT)
                {
                    g.render().DrawText(m_x +15 + 35, m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, caption());
                }
                else
                {
                    g.render().DrawText(m_x +15, m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, caption());
                }

                break;
            }

            case TAL_CENTER:
            {
                SDL_Rect r = wnd_size();
                r.w -= 35;

                if (checkbox_alignment() == CBA_LEFT) r.x += 35;
                g.render().DrawText(r, 1, 1, 1, caption());
                
                break;
            }

            case TAL_RIGHT:
            {
                // consider checkbox alignment
                if (checkbox_alignment() == CBA_LEFT)
                {
                    g.render().DrawText(m_x + m_w - g.render().TextWidth(caption()) - 15, m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, caption());
                }
                else
                {
                    g.render().DrawText(m_x + m_w - g.render().TextWidth(caption()) - 15 - 35, m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, caption());
                }
                
                break;
            }
        }
    }

    void CheckBox::draw_checkbox(ButtonState bs)
    {
        Globals g;

        TexInfo *bor, *cross;
        bor = cross = 0;

        switch (bs)
        {
        case BS_MOUSE_OVER:
            {
                bor   = g.render().LoadTexture(img_path() + "chk_mo_bor.tga");
                if (checked())
                    cross = g.render().LoadTexture(img_path() + "chk_mo_cro.tga");

                break;
            }

        case BS_MOUSE_DOWN:
            {
                bor   = g.render().LoadTexture(img_path() + "chk_md_bor.tga");
                if (checked())
                    cross = g.render().LoadTexture(img_path() + "chk_md_cro.tga");

               break;
            }

        case BS_HAS_FOCUS:
            {
                bor   = g.render().LoadTexture(img_path() + "chk_hf_bor.tga");
                if (checked())
                    cross = g.render().LoadTexture(img_path() + "chk_hf_cro.tga");

                break;
            }

        case BS_NOT_FOCUSED:
            {
                bor   = g.render().LoadTexture(img_path() + "chk_nf_bor.tga");
                if (checked())
                    cross = g.render().LoadTexture(img_path() + "chk_nf_cro.tga");

                break;
            }
        case BS_NONE: // will not happen; just to avoid compiler warning;
            {
                cerr << "CheckBox::draw_checkbox: BS_NONE called. This may not happen!" << endl;
                break;
            }

        }

        // check box alignment == CBA_LEFT
        int x = m_x + 17;
        int y = m_y + (m_h / 2) - 12;

        // change cba if CBA == CBA_RIGHT
        if (checkbox_alignment() == CBA_RIGHT)
        {
            x = m_x + m_w - 12 - 30;
        }

        // edges
        g.render().DrawTile(x, y, 25, 25, bor);
        if (cross) g.render().DrawTile(x, y, 25, 25, cross);
    }

}
