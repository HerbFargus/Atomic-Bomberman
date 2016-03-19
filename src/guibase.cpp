/**
 * file: guibase.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "guibase.h"

#include "globals.h"

#include <SDL/SDL_keysym.h>
#include <iostream>

#include "render.h"

namespace gui
{
    string Base::m_img_path;

    Base::Base()
        : m_font_size_w(16), m_font_size_h(16), m_has_focus(false), mp_next_focus(0),
          mb_mouse_down(false), mb_mouse_over(false), m_border_type(BT_ALWAYS),
          m_text_alignment(static_cast<TextAlignment>(TAL_CENTER))
    {
    }

    Base::~Base()
    {
    }

    // size-functions
    void Base::wnd_resize(int width, int height)
    {
        m_w = width;
        m_h = height;
    }

    void Base::wnd_set_rect(int x, int y, int width, int height)
    {
        m_x = x;
        m_y = y;
        wnd_resize(width, height);
    }

    void Base::wnd_set_origin(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    SDL_Rect Base::wnd_size()
    {
        SDL_Rect r = {m_x, m_y, m_w, m_h};
        return r;
    }

    // font size
    void Base::set_font_size(int width, int height)
    {
        m_font_size_w = width;
        m_font_size_h = height;
    }

    // focus functions
    void Base::set_focus(bool bfocus)
    {
        if (bfocus && has_focus() == false)
        {
            on_enter.emit();
        }

        if (!bfocus && has_focus() == true)
        {
            on_exit.emit();
        }
        
        m_has_focus = bfocus;
    }

    bool Base::has_focus() const
    {
        return m_has_focus;
    }

    // pressing TAB will activate the next control
    void Base::next_focus()
    {
        // only when next wnd exists
        if (mp_next_focus != 0)
        {
            set_focus(false);
            mp_next_focus->set_focus(true);
        }
        else
        {
//            cerr << "Warning: Base::next_focus(): mp_next_focus == NULL!" << endl;
        }
    }

    void Base::set_next_focus(Base* next_focus)
    {
        mp_next_focus = next_focus;
    }

    // key events
    void Base::on_key_down(UINT keysym)
    {
        if (has_focus())
        {
            if (keysym == SDLK_TAB)
                next_focus();
        }
    }

    void Base::on_key_up(UINT keysym)
    {
    }

    // mouse events
    void Base::on_mouse_down(int x, int y)
    {
        // set focus?
        if (mouse_in_wnd(x, y))
        {
            set_focus(true);

            set_mouse_down(true);
        }
        else
        {
            set_focus(false);
        }
    }

    void Base::on_mouse_up(int x, int y)
    {
        if (mouse_down())
            set_mouse_down(false);
    }

    void Base::on_mouse_move(int x, int y)
    {
        if (mouse_in_wnd(x, y))
        {
            set_mouse_in_wnd(true);
        }
        else
        {
            set_mouse_in_wnd(false);
        }
    }

    bool Base::mouse_in_wnd(int x, int y)
    {
        // check, whether the mouse is in the control
        if ( (y < m_y + m_h) &&
                (y > m_y) &&
                (x < m_x + m_w) &&
                (x > m_x) )
            return true;
        else
            return false;
    }

    void Base::set_mouse_in_wnd(bool b_in_wnd)
    {
        mb_mouse_over = b_in_wnd;
    }

    bool Base::mouse_over() const
    {
        return mb_mouse_over;
    }

    void Base::set_mouse_down(bool b_down)
    {
        mb_mouse_down = b_down;
    }

    bool Base::mouse_down() const
    {
        return mb_mouse_down;
    }

    // in this directory are all images. All gui-ctrls which use images will use this dir
    void Base::set_img_path(string path)
    {
        Base::m_img_path = path;
    }

    string Base::img_path() const
    {
        return Base::m_img_path;
    }

    // draw border routines
    void Base::draw_border(ButtonState bs)
    {
        // consider border_style
        if ((border_type() == BT_NEVER) ||
            (!has_focus() && border_type() == BT_FOCUS) ||
            (!has_focus() && !mouse_over() && border_type() == BT_MOUSE_OVER)) return;
        Globals g;
        TexInfo *t, *tl, *tr, *l, *r, *b, *bl, *br;
        t = tl = tr = l = r = b = bl = br = 0;
        switch (bs)
        {
        case BS_MOUSE_OVER:
            {
                t = g.render().LoadTexture(img_path() + "bor_mo_t.tga");
                l = g.render().LoadTexture(img_path() + "bor_mo_l.tga");
                r = g.render().LoadTexture(img_path() + "bor_mo_r.tga");
                b = g.render().LoadTexture(img_path() + "bor_mo_b.tga");
                tl = g.render().LoadTexture(img_path() + "bor_mo_tl.tga");
                tr = g.render().LoadTexture(img_path() + "bor_mo_tr.tga");
                bl = g.render().LoadTexture(img_path() + "bor_mo_bl.tga");
                br = g.render().LoadTexture(img_path() + "bor_mo_br.tga");
                break;
            }
        case BS_MOUSE_DOWN:
            {
                t = g.render().LoadTexture(img_path() + "bor_md_t.tga");
                l = g.render().LoadTexture(img_path() + "bor_md_l.tga");
                r = g.render().LoadTexture(img_path() + "bor_md_r.tga");
                b = g.render().LoadTexture(img_path() + "bor_md_b.tga");
                tl = g.render().LoadTexture(img_path() + "bor_md_tl.tga");
                tr = g.render().LoadTexture(img_path() + "bor_md_tr.tga");
                bl = g.render().LoadTexture(img_path() + "bor_md_bl.tga");
                br = g.render().LoadTexture(img_path() + "bor_md_br.tga");
                break;
            }
        case BS_HAS_FOCUS:
            {
                t = g.render().LoadTexture(img_path() + "bor_hf_t.tga");
                l = g.render().LoadTexture(img_path() + "bor_hf_l.tga");
                r = g.render().LoadTexture(img_path() + "bor_hf_r.tga");
                b = g.render().LoadTexture(img_path() + "bor_hf_b.tga");
                tl = g.render().LoadTexture(img_path() + "bor_hf_tl.tga");
                tr = g.render().LoadTexture(img_path() + "bor_hf_tr.tga");
                bl = g.render().LoadTexture(img_path() + "bor_hf_bl.tga");
                br = g.render().LoadTexture(img_path() + "bor_hf_br.tga");
                break;
            }
        case BS_NOT_FOCUSED:
            {
                t = g.render().LoadTexture(img_path() + "bor_nf_t.tga");
                l = g.render().LoadTexture(img_path() + "bor_nf_l.tga");
                r = g.render().LoadTexture(img_path() + "bor_nf_r.tga");
                b = g.render().LoadTexture(img_path() + "bor_nf_b.tga");
                tl = g.render().LoadTexture(img_path() + "bor_nf_tl.tga");
                tr = g.render().LoadTexture(img_path() + "bor_nf_tr.tga");
                bl = g.render().LoadTexture(img_path() + "bor_nf_bl.tga");
                br = g.render().LoadTexture(img_path() + "bor_nf_br.tga");
                break;
            }
        case BS_NONE:
            {
                return;
            }
        }
        // edges
        g.render().DrawTile(m_x, m_y, 12, 12, tl);
        g.render().DrawTile(m_x + m_w - 12, m_y, 12, 12, tr);
        g.render().DrawTile(m_x, m_y + m_h - 12, 12, 12, bl);
        g.render().DrawTile(m_x + m_w - 12, m_y + m_h - 12, 12, 12, br);
        int i;
        // top
        for (i = 0; i < m_w - 24; ++i)
        {
            g.render().DrawTile(m_x + 12 + i, m_y, 1, 12, t);
        }
        // bottom
        for (i = 0; i < m_w - 24; ++i)
        {
            g.render().DrawTile(m_x + 12 + i, m_y + m_h - 12, 1, 12, b);
        }
        // left
        for (i = 0; i < m_h - 24; ++i)
        {
            g.render().DrawTile(m_x, m_y + 12 + i, 12, 1, l);
        }
        // right
        for (i = 0; i < m_h - 24; ++i)
        {
            g.render().DrawTile(m_x + m_w - 12, m_y + 12 + i, 12, 1, r);
        }

    }

    // border settings
    void Base::set_border_type(BorderType bt)
    {
        m_border_type = bt;
    }

    BorderType Base::border_type() const
    {
        return m_border_type;
    }

    /**
     * set text alignment
     */
    void Base::set_text_alignment(TextAlignment ta)
    {
        m_text_alignment = ta;
    }

    /**
     * get text alignment
     */
    TextAlignment Base::text_alignment() const
    {
        return m_text_alignment;
    }

}
