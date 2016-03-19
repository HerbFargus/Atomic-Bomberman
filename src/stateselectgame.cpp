/**
 * file: stateselectgame.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#ifdef WIN32
  #define DISABLE_LIBSIGC 1
#endif

#include "stateselectgame.h"

#include "enumblocks.h"
#include "gameinfo.h"
#include "globals.h"
#include "imagelist.h"
#include "scheme.h"
#include "schememanager.h"
#include "valuelist.h"

#include <iostream>

namespace state
{

SelectGame::SelectGame () {}
SelectGame::~SelectGame (){}

void
SelectGame::on_enter()
{
#ifndef DISABLE_LIBSIGC
    create_scheme_list();

    if (m_scheme_list.size() > 0)
        m_scheme_preview.set_scheme(m_scheme_list[0]);

    m_selected_scheme = 0;

    create_gui();
#endif // DISABLE_LIBSIGC
}

void
SelectGame::create_gui()
{
#ifndef DISABLE_LIBSIGC
    Globals g;

    int width  = g.values().res_w();
    int height = g.values().res_h();
    int half   = width / 2;
    int quarter= half / 2;

    // create buttons
//    m_btn_p1_head    = new PushButton("Player 1");
    m_lv_schemes     = new ListView("Schemes");

    int d = 75;

    // positions
//    m_btn_p1_head    ->wnd_set_rect(quarter - 200, 100, 400, 40);
    m_lv_schemes     ->wnd_set_rect(50, 100, 300, 500);
    // font size
//    m_btn_p1_head    ->set_font_size(24, 24);
    
    // text alignment
/*    m_btn_p1_head    ->set_text_alignment(TAL_CENTER);
*/

//    m_btn_p1_up      ->set_border_type(BT_MOUSE_OVER);

    m_gui_active.add(m_lv_schemes);

    // signals & slots
//    m_btn_p1_up     ->on_clicked.connect(slot(*this, &ConfigureKeys::p1_up_clicked));

    m_gui_active.create_tab_order();
    // delete objects when calling m_con_active.clear()!
    m_gui_active.set_autodelete(true);
    m_lv_schemes->set_focus(true);
#endif // DISABLE_LIBSIGC
}

void
SelectGame::on_exit()
{
#ifndef DISABLE_LIBSIGC
    m_gui_active.clear();
#endif // DISABLE_LIBSIGC
}

void
SelectGame::on_draw()
{
#ifndef DISABLE_LIBSIGC
    /**
     * TODO:
     *      -> draw the level list on the left
     *      -> draw map list on the right top
     *      -> draw scheme preview on right bottom
     */
    m_scheme_preview.draw(400, 300);
    m_gui_active.draw_all();
#endif // DISABLE_LIBSIGC
}

void
SelectGame::on_key_down(UINT keysym)
{
#ifndef DISABLE_LIBSIGC
    m_scheme_preview.set_scheme(m_scheme_list[++m_selected_scheme]);
#endif // DISABLE_LIBSIGC
}

void
SelectGame::on_key_up  (UINT keysym)
{
}

int
SelectGame::create_scheme_list()
{
#ifndef DISABLE_LIBSIGC
    SchemeManager mng;
    mng.find_schemes();

    for (int i = 0; i < mng.number(); ++i)
    {
        m_scheme_list.push_back( mng.scheme(i).filename );
    }
    
    return m_scheme_list.size();
#else
	return 0;
#endif // DISABLE_LIBSIGC

}



/*////////////////////////////////////////////
// Nested class: SelectGame::SchemePreview  //
////////////////////////////////////////////*/
SelectGame::SchemePreview::SchemePreview()
    : mp_scheme(0), m_divisor(2.0)
{
    m_brick_solid.SetAnimation(ANI_TILE_SOLID);
    m_brick_breakable.SetAnimation(ANI_TILE_NONSOLID);
}

SelectGame::SchemePreview::~SchemePreview()
{
    if (mp_scheme != 0)
        delete mp_scheme;
}

void
SelectGame::SchemePreview::draw(int offset_x, int offset_y)
{
#ifndef DISABLE_LIBSIGC
    Globals g;
    
    int w;
    int h;

    TexInfo* bg = g.render().LoadTexture(g.images().map_field(g.game().map()));
    
	g.render().DrawTile(offset_x, offset_y, g.values().res_w() / m_divisor, g.values().res_h() / m_divisor, bg);

    // cell offset for preview
    double f_os_x = g.values().get(VAL_FIELD_OFFSET_X) / m_divisor;
    double f_os_y = g.values().get(VAL_FIELD_OFFSET_Y) / m_divisor;

    // cell size for preview
    double f_sz_x = g.values().get(VAL_CELL_W) / m_divisor;
    double f_sz_y = g.values().get(VAL_CELL_H) / m_divisor;

    if (mp_scheme != 0)
    {
        // draw bricks
        for ( w=0 ; w < g.values().get(VAL_FIELD_WIDTH); ++w )
        {
            for ( h=0; h < g.values().get(VAL_FIELD_HEIGHT); ++h )
            {
                switch (mp_scheme->field_data(w, h))
                {
                    case BLOCK_SOLID:
                        m_brick_solid       .Draw(offset_x + f_os_x + w * f_sz_x, offset_y + f_os_y + h * f_sz_y, f_sz_x, f_sz_y);
                        break;
                        
                    case BLOCK_BREAKABLE:
                        m_brick_breakable   .Draw(offset_x + f_os_x + w * f_sz_x, offset_y + f_os_y + h * f_sz_y, f_sz_x, f_sz_y);
                        break;
                }
            }
        }
    }
    else
    {
        cerr << "Error: SchemePreview: scheme to preview is not set! Call SchemePreview::set_scheme!" << endl;
    }
#endif // DISABLE_LIBSIGC
}

void
SelectGame::SchemePreview::set_scheme(const string& filename)
{
    if (mp_scheme != 0)
    {
        delete mp_scheme;
    }

    mp_scheme = new Scheme;
    mp_scheme->load_from_file(filename);
}
/** ********** Here ends N E S T E D   C L A S S: SchemePreview ********** **/

}
