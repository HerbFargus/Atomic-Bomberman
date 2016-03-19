/**
 * file: listview.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "guilistview.h"

#include "globals.h"
#include "render.h"

#include <iostream>

namespace gui
{

    ListView::ListView(string cap)
        : Button(),
        m_num_entries(-1), // no entries yet
        m_selection(-1), // no selection
        m_sb_align_left(false), // scrollbar on the left
        m_begin_with(0)
    {
    }

    ListView::~ListView()
    {
    }

    void
    ListView::draw()
    {
        draw_border();
        draw_listview();
        draw_selection();
        draw_entries();

        Globals g;

        g.render().SetTextSizes(m_font_size_w, m_font_size_h);

        switch (text_alignment())
        {
            case TAL_LEFT:
            {
                g.render().DrawText(m_x +15 , m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, caption());
                break;
            }

            case TAL_CENTER:
            {
                g.render().DrawText(wnd_size(), 1, 1, 1, caption());
                break;
            }

            case TAL_RIGHT:
            {
                g.render().DrawText(m_x + m_w - g.render().TextWidth(caption()) - 15, m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, caption());
                break;
            }
        }
    }

    void
    ListView::draw_selection()
    {
        if (m_selection >= 0)
        {
            SDL_Rect rsel = {m_x+12,
                            m_y+12+30+m_selection*20,
                            m_w-2*12-30, // -30: because of scrollbar
                            20};
            if ( m_sb_align_left ) rsel.x += 30;


            Globals::render().FillRect(rsel,1.0, 1.0, 1.0, 0.5f);
        }
    }

    void
    ListView::draw_entries()
    {
        Globals g;
        SDL_Rect rect = {m_x+12, // scrollbar right
                         m_y+12+30,
                         m_w-2*12-30,
                         20};
        if ( m_sb_align_left ) rect.x += 30; // scrollbar left

        int num = 0;
        vector<string>::iterator it = m_entries.begin();
        it += m_begin_with;

        switch (text_alignment()) {
            case TAL_LEFT: {
                for ( ; it != m_entries.end() && num < num_entries(); ++it) {
                    g.render().DrawText(rect.x, rect.y+2, 255, 255, 255, *it);
                    rect.y += 20;
                    ++num;
                }
                break;
            }

            case TAL_CENTER: {
                for ( ; it != m_entries.end() && num < num_entries(); ++it) {
                    g.render().DrawText(rect, 255, 255, 255, *it);
                    rect.y += 20;
                    ++num;
                }
                break;
            }

            case TAL_RIGHT: {
                for ( ; it != m_entries.end() && num < num_entries(); ++it) {
                    g.render().DrawText(rect.x + rect.w - g.render().TextWidth(*it),
                                        rect.y+2, 255, 255, 255, *it);
                    rect.y += 20;
                    ++num;
                }
                break;
            }
        }
    }

    void
    ListView::draw_listview()
    {
        ButtonState bs = draw_border();
        Globals g;
        int i;
        TexInfo *top, *middle, *bottom, *hline, *vline;
        // scrollbar
        switch (bs)
        {
        case BS_MOUSE_OVER:
            {
                top    = g.render().LoadTexture(img_path() + "sb_mo_t.tga");
                middle = g.render().LoadTexture(img_path() + "sb_mo_m.tga");
                bottom = g.render().LoadTexture(img_path() + "sb_mo_b.tga");
                hline  = g.render().LoadTexture(img_path() + "sb_mo_h.tga");
                vline  = g.render().LoadTexture(img_path() + "sb_mo_v.tga");

                break;
            }

        case BS_MOUSE_DOWN:
            {
                top    = g.render().LoadTexture(img_path() + "sb_md_t.tga");
                middle = g.render().LoadTexture(img_path() + "sb_md_m.tga");
                bottom = g.render().LoadTexture(img_path() + "sb_md_b.tga");
                hline  = g.render().LoadTexture(img_path() + "sb_md_h.tga");
                vline  = g.render().LoadTexture(img_path() + "sb_md_v.tga");

                break;
            }

        case BS_HAS_FOCUS:
            {
                top    = g.render().LoadTexture(img_path() + "sb_hf_t.tga");
                middle = g.render().LoadTexture(img_path() + "sb_hf_m.tga");
                bottom = g.render().LoadTexture(img_path() + "sb_hf_b.tga");
                hline  = g.render().LoadTexture(img_path() + "sb_hf_h.tga");
                vline  = g.render().LoadTexture(img_path() + "sb_hf_v.tga");

                break;
            }

        case BS_NOT_FOCUSED:
            {
                top    = g.render().LoadTexture(img_path() + "sb_nf_t.tga");
                middle = g.render().LoadTexture(img_path() + "sb_nf_m.tga");
                bottom = g.render().LoadTexture(img_path() + "sb_nf_b.tga");
                hline  = g.render().LoadTexture(img_path() + "sb_nf_h.tga");
                vline  = g.render().LoadTexture(img_path() + "sb_nf_v.tga");

                break;
            }
        case BS_NONE: // will not happen; just to avoid compiler warning;
            {
                cerr << "ListView::draw_listview: BS_NONE called. This may not happen!" << endl;
                break;
            }
        }

        int x;
        int y = m_y + 12 + 30;
        if ( m_sb_align_left ) // left aligned
            x = m_x + 12; // 12 because of border
        else
            x = m_x + m_w - 12 - 20; // 12 because of border

        int size = m_entries.size();
        if (size == 0) size = 1;

        int dsb = (static_cast<double>(m_h)-12.0-12.0-30.0)
            *(static_cast<double>(num_entries())/static_cast<double>(size));
        int anf = (static_cast<double>(m_h)-12.0-12.0-30.0)
            *(static_cast<double>(m_begin_with)/static_cast<double>(size));

        // draw "scroller"
        if (top) g.render().DrawTile(x, y+anf, 20, 12, top);
        if (middle)
        {
            for (i=0; i < dsb-24; ++i)
            {
                g.render().DrawTile(x, y+i+12+anf, 20, 1, middle);
            }
        }
        if (bottom) g.render().DrawTile(x, y+anf-12+dsb, 20, 12, bottom);

        // draw "hline"
        if (hline)
        {
            x = m_x + 12;
            y = m_y + 12 + 21;
            for (i=0; i < m_w-12-12; ++i)
                g.render().DrawTile(x+i, y, 1, 4, hline);
        }

        // draw "vline"
        if (vline)
        {
            if ( m_sb_align_left ) // left aligned
                x = m_x + 12 + 25;
            else
                x = m_x + m_w - 12 - 25 - 4; // 4px*1px==vline
            y = m_y + 12 + 30;
            for (i=0; i < m_h-12-12-30; ++i)
                g.render().DrawTile(x, y+i, 4, 1, vline);
        }

        // draw Caption
        SDL_Rect r = {m_x, m_y+12, m_w, 20};
        g.render().DrawText(r, 255, 255, 255, caption());
    }

    void
    ListView::add_string_list(const vector<string>& list, const vector<string>* data/* = 0*/)
    {
        bool addsel = (m_selection>-1)?true:false;
        int i = 0;
        for( ; i < list.size(); ++i)
            m_entries.push_back(list[i]);
        if (data != 0) {
            for( i = 0; i < data->size(); ++i)
                m_dat_str.push_back((*data)[i]);
        }
        if (!addsel && m_entries.size()>0) m_selection = 0;
    }

    void
    ListView::add_string_list(const vector<string>& list, const vector<int>* data /*= 0*/)
    {
        bool addsel = (m_selection>-1)?true:false;
        int i = 0;
        for( ; i < list.size(); ++i)
            m_entries.push_back(list[i]);
        if (data != 0) {
            for( i = 0; i < data->size(); ++i)
                m_dat_int.push_back((*data)[i]);
        }
        if (!addsel && m_entries.size()>0) m_selection = 0;
    }

    void
    ListView::add_string(const string& str, const string* data /*= 0*/)
    {
        bool addsel = (m_selection>-1)?true:false;
        m_entries.push_back(str);
        if (data != 0) {
            m_dat_str.push_back(*data);
        }
        if (!addsel && m_entries.size()>0) m_selection = 0;
    }

    void
    ListView::add_string(const string& str, const int* data /*= 0*/)
    {
        bool addsel = (m_selection>-1)?true:false;
        m_entries.push_back(str);
        if (data != 0) {
            m_dat_int.push_back(*data);
        }
        if (!addsel && m_entries.size()>0) m_selection = 0;
    }

    const string*
    ListView::selected()
    {
        if (m_selection!=-1)
            return &(m_entries[m_begin_with + m_selection]);
        else
            return 0;
    }

    const string*
    ListView::selected_str_data()
    {
        if (m_selection!=-1)
            return &(m_dat_str[m_begin_with + m_selection]);
        else
            return 0;
    }

    const int*
    ListView::selected_int_data()
    {
        if (m_selection!=-1)
            return &(m_dat_int[m_begin_with + m_selection]);
        else
            return 0;
    }

    int
    ListView::num_entries() const
    {
        return (m_h - 2*12-30)/20; // Listview item height: 20
    }

    void
    ListView::on_key_down(UINT keysym)
    {
        Button::on_key_down(keysym);

        if (keysym == SDLK_LEFT)
            m_sb_align_left=true;
        if (keysym == SDLK_RIGHT)
            m_sb_align_left=false;
        if (keysym == SDLK_a)
            set_text_alignment(TAL_LEFT);
        if (keysym == SDLK_b)
            set_text_alignment(TAL_CENTER);
        if (keysym == SDLK_c)
            set_text_alignment(TAL_RIGHT);

        if (keysym == SDLK_DOWN)
        {
            if (m_begin_with+m_selection+1 >= m_entries.size())
                return;
            if (m_selection+1 >= num_entries())
            {
                m_begin_with++;
                selection_changed();
            }
            else
            {
                m_selection++;
                selection_changed();
            }
            return;
        }

        if (keysym == SDLK_UP)
        {
            if (m_begin_with+m_selection-1 < 0)
                return;
            if (m_selection-1 < 0)
            {
                m_begin_with--;
                selection_changed();
            }
            else
            {
                m_selection--;
                selection_changed();
            }
            return;
        }

        if (keysym == SDLK_HOME)
        {
            m_begin_with = 0;
            if (m_entries.size()>0 && m_selection!=0)
            {
                m_selection = 0;
                selection_changed();
            }
            return;
        }

        if (keysym == SDLK_END)
        {
            m_begin_with = m_entries.size() - num_entries();
            if (m_begin_with < 0) m_begin_with = 0;
            if (m_entries.size()>0 && m_selection != num_entries()-1)
            {
                m_selection = num_entries() -1;
                selection_changed();
            }
            return;
        }
    }

    void
    ListView::on_mouse_down(int x, int y)
    {
        Button::on_mouse_down(x, y);
        // Add code here
    }

    void
    ListView::on_mouse_up(int x, int y)
    {
        Button::on_mouse_up(x, y);
        // Add code here
    }

    void
    ListView::on_mouse_move(int x, int y)
    {
        Button::on_mouse_move(x, y);
        // Add code here
    }

    void
    ListView::selection_changed()
    {
        on_changed.emit();
    }

    void
    ListView::set_sb_align_left(bool left)
    {
        m_sb_align_left = left;
    }

    bool
    ListView::sb_align() const
    {
        return m_sb_align_left;
    }
}
