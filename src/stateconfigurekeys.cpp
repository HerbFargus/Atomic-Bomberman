/* by Dominik Haumann  */

#ifdef WIN32
  #define DISABLE_LIBSIGC 1
#endif

#include "stateconfigurekeys.h"
#include "render.h"
#include "globals.h"
#include "imagelist.h"
#include "valuelist.h"
#include "keyconfig.h"
#include "animmng.h"
#include "soundlist.h"
#include "sound.h"

#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>

namespace state
{

ConfigureKeys::ConfigureKeys () { }
ConfigureKeys::~ConfigureKeys () { }

void
ConfigureKeys::on_enter()
{
#ifndef DISABLE_LIBSIGC
    Globals g;

    SDL_EnableKeyRepeat(g.values().get(VAL_MENU_KEYREPEAT_DELAY), g.values().get(VAL_MENU_KEYREPEAT_INTERVAL));

    create_key_map();
    create_gui();

    mb_grab_key = false;
    m_which_player = 0;

    m_bg = g.render().LoadTexture(g.images().background_random());

    m_anim_bomb.SetAnimation(ANI_BOMB);
    m_anim_bomb.Start();

    mp_keyconfig    = &g.keycfg();

    g.render().SetTextSizes(16, 16);
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::create_gui()
{
#ifndef DISABLE_LIBSIGC
    Globals g;

    int width  = g.values().res_w();
    int height = g.values().res_h();
    int half   = width / 2;
    int quarter= half / 2;

    // create buttons
    m_btn_p1_head    = new PushButton("Player 1");
    m_btn_p1_up      = new PushButton("Up");
    m_btn_p1_down    = new PushButton("Down");
    m_btn_p1_left    = new PushButton("Left");
    m_btn_p1_right   = new PushButton("Right");
    m_btn_p1_drop    = new PushButton("Drop bomb");
    m_btn_p1_special = new PushButton("Special key");

    m_btn_p2_head    = new PushButton("Player 2");
    m_btn_p2_up      = new PushButton("Up");
    m_btn_p2_down    = new PushButton("Down");
    m_btn_p2_left    = new PushButton("Left");
    m_btn_p2_right   = new PushButton("Right");
    m_btn_p2_drop    = new PushButton("Drop bomb");
    m_btn_p2_special = new PushButton("Special key");

    int d = 75;

    // positions
    m_btn_p1_head    ->wnd_set_rect(quarter - 200, 100, 400, 40);
    m_btn_p1_up      ->wnd_set_rect(quarter - 100, 100 + 1*d, 200, 40);
    m_btn_p1_down    ->wnd_set_rect(quarter - 100, 100 + 2*d, 200, 40);
    m_btn_p1_left    ->wnd_set_rect(quarter - 100, 100 + 3*d, 200, 40);
    m_btn_p1_right   ->wnd_set_rect(quarter - 100, 100 + 4*d, 200, 40);
    m_btn_p1_drop    ->wnd_set_rect(quarter - 100, 100 + 5*d, 200, 40);
    m_btn_p1_special ->wnd_set_rect(quarter - 100, 100 + 6*d, 200, 40);

    m_btn_p2_head    ->wnd_set_rect(3*quarter - 200, 100, 400, 40);
    m_btn_p2_up      ->wnd_set_rect(3*quarter - 100, 100 + 1*d, 200, 40);
    m_btn_p2_down    ->wnd_set_rect(3*quarter - 100, 100 + 2*d, 200, 40);
    m_btn_p2_left    ->wnd_set_rect(3*quarter - 100, 100 + 3*d, 200, 40);
    m_btn_p2_right   ->wnd_set_rect(3*quarter - 100, 100 + 4*d, 200, 40);
    m_btn_p2_drop    ->wnd_set_rect(3*quarter - 100, 100 + 5*d, 200, 40);
    m_btn_p2_special ->wnd_set_rect(3*quarter - 100, 100 + 6*d, 200, 40);

    // font size
    m_btn_p1_head    ->set_font_size(24, 24);
    m_btn_p1_up      ->set_font_size(16, 16);
    m_btn_p1_down    ->set_font_size(16, 16);
    m_btn_p1_left    ->set_font_size(16, 16);
    m_btn_p1_right   ->set_font_size(16, 16);
    m_btn_p1_drop    ->set_font_size(16, 16);
    m_btn_p1_special ->set_font_size(16, 16);

    m_btn_p2_head    ->set_font_size(24, 24);
    m_btn_p2_up      ->set_font_size(16, 16);
    m_btn_p2_down    ->set_font_size(16, 16);
    m_btn_p2_left    ->set_font_size(16, 16);
    m_btn_p2_right   ->set_font_size(16, 16);
    m_btn_p2_drop    ->set_font_size(16, 16);
    m_btn_p2_special ->set_font_size(16, 16);

    // text alignment
/*    m_btn_p1_head    ->set_text_alignment(TAL_CENTER);
    m_btn_p1_up      ->set_text_alignment(TAL_LEFT);
    m_btn_p1_down    ->set_text_alignment(TAL_LEFT);
    m_btn_p1_left    ->set_text_alignment(TAL_LEFT);
    m_btn_p1_right   ->set_text_alignment(TAL_LEFT);
    m_btn_p1_drop    ->set_text_alignment(TAL_LEFT);
    m_btn_p1_special ->set_text_alignment(TAL_LEFT);

    m_btn_p2_head    ->set_text_alignment(TAL_CENTER);
    m_btn_p2_up      ->set_text_alignment(TAL_LEFT);
    m_btn_p2_down    ->set_text_alignment(TAL_LEFT);
    m_btn_p2_left    ->set_text_alignment(TAL_LEFT);
    m_btn_p2_right   ->set_text_alignment(TAL_LEFT);
    m_btn_p2_drop    ->set_text_alignment(TAL_LEFT);
    m_btn_p2_special ->set_text_alignment(TAL_LEFT);
*/

    m_btn_p1_up      ->set_border_type(BT_MOUSE_OVER);
    m_btn_p1_down    ->set_border_type(BT_MOUSE_OVER);
    m_btn_p1_left    ->set_border_type(BT_MOUSE_OVER);
    m_btn_p1_right   ->set_border_type(BT_MOUSE_OVER);
    m_btn_p1_drop    ->set_border_type(BT_MOUSE_OVER);
    m_btn_p1_special ->set_border_type(BT_MOUSE_OVER);

    m_btn_p2_up      ->set_border_type(BT_MOUSE_OVER);
    m_btn_p2_down    ->set_border_type(BT_MOUSE_OVER);
    m_btn_p2_left    ->set_border_type(BT_MOUSE_OVER);
    m_btn_p2_right   ->set_border_type(BT_MOUSE_OVER);
    m_btn_p2_drop    ->set_border_type(BT_MOUSE_OVER);
    m_btn_p2_special ->set_border_type(BT_MOUSE_OVER);

    m_con_active.add(m_btn_p1_up     );
    m_con_active.add(m_btn_p1_down   );
    m_con_active.add(m_btn_p1_left   );
    m_con_active.add(m_btn_p1_right  );
    m_con_active.add(m_btn_p1_drop   );
    m_con_active.add(m_btn_p1_special);

    m_con_active.add(m_btn_p2_up     );
    m_con_active.add(m_btn_p2_down   );
    m_con_active.add(m_btn_p2_left   );
    m_con_active.add(m_btn_p2_right  );
    m_con_active.add(m_btn_p2_drop   );
    m_con_active.add(m_btn_p2_special);

    // signals & slots
    m_btn_p1_up     ->on_clicked.connect(slot(*this, &ConfigureKeys::p1_up_clicked));
    m_btn_p1_down   ->on_clicked.connect(slot(*this, &ConfigureKeys::p1_down_clicked));
    m_btn_p1_left   ->on_clicked.connect(slot(*this, &ConfigureKeys::p1_left_clicked));
    m_btn_p1_right  ->on_clicked.connect(slot(*this, &ConfigureKeys::p1_right_clicked));
    m_btn_p1_drop   ->on_clicked.connect(slot(*this, &ConfigureKeys::p1_drop_clicked));
    m_btn_p1_special->on_clicked.connect(slot(*this, &ConfigureKeys::p1_special_clicked));

    m_btn_p2_up     ->on_clicked.connect(slot(*this, &ConfigureKeys::p2_up_clicked));
    m_btn_p2_down   ->on_clicked.connect(slot(*this, &ConfigureKeys::p2_down_clicked));
    m_btn_p2_left   ->on_clicked.connect(slot(*this, &ConfigureKeys::p2_left_clicked));
    m_btn_p2_right  ->on_clicked.connect(slot(*this, &ConfigureKeys::p2_right_clicked));
    m_btn_p2_drop   ->on_clicked.connect(slot(*this, &ConfigureKeys::p2_drop_clicked));
    m_btn_p2_special->on_clicked.connect(slot(*this, &ConfigureKeys::p2_special_clicked));

    m_con_active.create_tab_order();
    // delete objects when calling m_con_active.clear()!
    m_con_active.set_autodelete(true);
    m_btn_p1_up->set_focus(true);

    m_con_passive.add(m_btn_p1_head   );
    m_con_passive.add(m_btn_p2_head   );
    m_con_passive.create_tab_order();
    m_con_passive.set_autodelete(true);
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::on_exit()
{
#ifndef DISABLE_LIBSIGC
    Globals g;

    g.render().DeleteTexture(m_bg);
    SDL_EnableKeyRepeat(0, 0); // 0,0 disables key-repeat

    m_con_active.clear();
    m_con_passive.clear();
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::on_draw()
{
#ifndef DISABLE_LIBSIGC
    Globals g;

    // background image
    g.render().DrawTile(0, 0, g.values().res_w(), g.values().res_h(), m_bg);

    int width  = g.values().res_w();
    int half   = width / 2;
    int quarter= width / 4;

    SDL_Rect top = {quarter - 220, 80, width - 2*(quarter-220), 80};
    SDL_Rect rl  = {quarter - 220, 170, half - 50, 500};
    SDL_Rect rr  = {half + (half -(quarter - 220 + (half - 50))), 170, half - 50, 500};

    g.render().FillRect(top,.0, .0, .0, 0.5f);
    g.render().FillRect(rl ,.0, .0, .0, 0.5f);
    g.render().FillRect(rr ,.0, .0, .0, 0.5f);

    m_con_active.draw_all();
    m_con_passive.draw_all();

    draw_player_keys();

    m_anim_bomb.Update();

    if (mb_grab_key)
    {
        draw_grab_key();
        m_anim_bomb.Draw(quarter - 185, 740, 50, 50);
        m_anim_bomb.Draw(quarter - 220 + (width - 2*(quarter-220)) - 45, 740, 50, 50);
    }
    else
    {
        int index = m_con_active.current_focused();
        m_anim_bomb.Draw(quarter-145 + 512*(index>5?1:0), 142 + 75*((index>5?(index-6):index)+1), 50, 50);
    }
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::draw_player_keys()
{
    int d = 75;
    Globals g;
    g.render().SetTextSizes(16, 16);

    g.render().DrawText(380, 112 + 1*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(0).key(KEY_UP)]);
    g.render().DrawText(380, 112 + 2*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(0).key(KEY_DOWN)]);
    g.render().DrawText(380, 112 + 3*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(0).key(KEY_LEFT)]);
    g.render().DrawText(380, 112 + 4*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(0).key(KEY_RIGHT)]);
    g.render().DrawText(380, 112 + 5*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(0).key(KEY_BOMB)]);
    g.render().DrawText(380, 112 + 6*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(0).key(KEY_SPECIAL)]);

    g.render().DrawText(890, 112 + 1*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(1).key(KEY_UP)]);
    g.render().DrawText(890, 112 + 2*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(1).key(KEY_DOWN)]);
    g.render().DrawText(890, 112 + 3*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(1).key(KEY_LEFT)]);
    g.render().DrawText(890, 112 + 4*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(1).key(KEY_RIGHT)]);
    g.render().DrawText(890, 112 + 5*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(1).key(KEY_BOMB)]);
    g.render().DrawText(890, 112 + 6*d, 255, 255, 255, m_map_keys[mp_keyconfig->player_keys(1).key(KEY_SPECIAL)]);
}

void
ConfigureKeys::draw_grab_key()
{
    Globals g;
    int width  = g.values().res_w();
    int height = g.values().res_h();
    int quarter= width / 4;

    SDL_Rect r = {quarter - 220, 680, width - 2*(quarter-220), 70};

    g.render().FillRect(r, .0, .0, .0, .5f);

    string str = "Press a key for ";

    switch (m_which_player)
    {
        case 0: str += "Player 1!"; break;
        case 1: str += "Player 2!"; break;
    }

    g.render().SetTextSizes(24, 24);
    g.render().DrawText(r, 255, 255, 255, str);
}

void
ConfigureKeys::on_key_down(UINT keysym)
{
#ifndef DISABLE_LIBSIGC
    Globals g;

    if (keysym == SDLK_ESCAPE)
    {
        if(mb_grab_key)
        {
            mb_grab_key = false;
            g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));
        }
        else
        {
            g.sound().play(g.soundlist().get_random_sound(SND_MENU_EXIT));
            input().set_ok();
            next_state();
        }
        return;
    }

    if (!mb_grab_key)
    {
        if (keysym == SDLK_DOWN)
        {
            g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));
            m_con_active.on_key_down(SDLK_TAB);
            return;
        }
        else
        {
            if (keysym == SDLK_UP)
            {
                g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));
                m_con_active.tab_backward();
                return;
            }
            else
            {
                if (keysym == SDLK_LEFT || keysym == SDLK_RIGHT)
                {
                    for (int i = 0; i < 6; ++i)
                    {
                        m_con_active.on_key_down(SDLK_TAB);
                    }
                    g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));
                    return;
                }
            }
        }

        g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));
        m_con_active.on_key_down(keysym);
    }
    else
    {
        g.sound().play(g.soundlist().get_random_sound(SND_MENU_EXIT));
        mb_grab_key = false;
        mp_keyconfig->player_keys_change(m_which_player).set_key(m_player_keys, keysym);
    }
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::on_key_up(UINT keysym)
{
#ifndef DISABLE_LIBSIGC
    m_con_active.on_key_up(keysym);
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::on_mouse_down (const SDL_MouseButtonEvent& ev)
{
#ifndef DISABLE_LIBSIGC
    if (!mb_grab_key) m_con_active.on_mouse_down(ev.x, ev.y);
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::on_mouse_up (const SDL_MouseButtonEvent& ev)
{
#ifndef DISABLE_LIBSIGC
    if (!mb_grab_key) m_con_active.on_mouse_up(ev.x, ev.y);
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::on_mouse_move (const SDL_MouseMotionEvent& ev)
{
#ifndef DISABLE_LIBSIGC
    if (!mb_grab_key) m_con_active.on_mouse_move(ev.x, ev.y);
#endif // DISABLE_LIBSIGC
}

void
ConfigureKeys::create_key_map()
{
    m_map_keys.resize(SDLK_LAST + 1);

    m_map_keys[SDLK_BACKSPACE   ] = "Backspace";
    m_map_keys[SDLK_TAB		    ] = "Tab";
    //    m_map_keys[SDLK_CLEAR	 ]  = "",
    m_map_keys[SDLK_RETURN	    ] = "Return";
    m_map_keys[SDLK_PAUSE	    ] = "Pause";
//    m_map_keys[SDLK_ESCAPE	    ] = "Escape"; // esc switches to mainmenu!
    m_map_keys[SDLK_SPACE	    ] = "Space";
    m_map_keys[SDLK_EXCLAIM	    ] = "!";
    m_map_keys[SDLK_QUOTEDBL    ] = "\"";
    m_map_keys[SDLK_HASH	    ] = "#";
    m_map_keys[SDLK_DOLLAR	    ] = "$";
    m_map_keys[SDLK_AMPERSAND   ] = "&";
    m_map_keys[SDLK_QUOTE	    ] = "'";
    m_map_keys[SDLK_LEFTPAREN   ] = "[";
    m_map_keys[SDLK_RIGHTPAREN  ] = "]";
    m_map_keys[SDLK_ASTERISK    ] = "*";
    m_map_keys[SDLK_PLUS	    ] = "+";
    m_map_keys[SDLK_COMMA	    ] = ",";
    m_map_keys[SDLK_MINUS	    ] = "-";
    m_map_keys[SDLK_PERIOD	    ] = "~";
    m_map_keys[SDLK_SLASH	    ] = "/";
    m_map_keys[SDLK_0		    ] = "0";
    m_map_keys[SDLK_1		    ] = "1";
    m_map_keys[SDLK_2	        ] = "2";
    m_map_keys[SDLK_3		    ] = "3";
    m_map_keys[SDLK_4	        ] = "4";
    m_map_keys[SDLK_5		    ] = "5";
    m_map_keys[SDLK_6	        ] = "6";
    m_map_keys[SDLK_7	    	] = "7";
    m_map_keys[SDLK_8           ] = "8";
    m_map_keys[SDLK_9	        ] = "9";
    m_map_keys[SDLK_COLON       ] = ":";
    m_map_keys[SDLK_SEMICOLON   ] = ";";
    m_map_keys[SDLK_LESS        ] = "<";
    m_map_keys[SDLK_EQUALS      ] = "=";
    m_map_keys[SDLK_GREATER     ] = ">";
    m_map_keys[SDLK_QUESTION    ] = "?";
    m_map_keys[SDLK_AT          ] = "@";
    /*
       Skip uppercase letters
     */
    m_map_keys[SDLK_LEFTBRACKET ] = "(";
    m_map_keys[SDLK_BACKSLASH   ] = "\\";
    m_map_keys[SDLK_RIGHTBRACKET] = ")";
    m_map_keys[SDLK_CARET       ] = "";
    m_map_keys[SDLK_UNDERSCORE  ] = "_";
    m_map_keys[SDLK_BACKQUOTE   ] = "'";
    m_map_keys[SDLK_a           ] = "a";
    m_map_keys[SDLK_b           ] = "b";
    m_map_keys[SDLK_c           ] = "c";
    m_map_keys[SDLK_d           ] = "d";
    m_map_keys[SDLK_e           ] = "e";
    m_map_keys[SDLK_f           ] = "f";
    m_map_keys[SDLK_g           ] = "g";
    m_map_keys[SDLK_h           ] = "h";
    m_map_keys[SDLK_i           ] = "i";
    m_map_keys[SDLK_j           ] = "j";
    m_map_keys[SDLK_k           ] = "k";
    m_map_keys[SDLK_l           ] = "l";
    m_map_keys[SDLK_m           ] = "m";
    m_map_keys[SDLK_n           ] = "n";
    m_map_keys[SDLK_o           ] = "o";
    m_map_keys[SDLK_p           ] = "p";
    m_map_keys[SDLK_q           ] = "q";
    m_map_keys[SDLK_r           ] = "r";
    m_map_keys[SDLK_s           ] = "s";
    m_map_keys[SDLK_t           ] = "t";
    m_map_keys[SDLK_u           ] = "u";
    m_map_keys[SDLK_v           ] = "v";
    m_map_keys[SDLK_w           ] = "w";
    m_map_keys[SDLK_x           ] = "x";
    m_map_keys[SDLK_y           ] = "y";
    m_map_keys[SDLK_z           ] = "z";
    m_map_keys[SDLK_DELETE      ] = "Delete";
    /* End of ASCII mapped keysyms */

    /* International keyboard syms */
    /*    SDLK_WORLD_0		= 160*/		/* 0xA0 */
    /*    SDLK_WORLD_1		= 161,
          SDLK_WORLD_2		= 162,
          SDLK_WORLD_3		= 163,
          SDLK_WORLD_4		= 164,
          SDLK_WORLD_5		= 165,
          SDLK_WORLD_6		= 166,
          SDLK_WORLD_7		= 167,
          SDLK_WORLD_8		= 168,
          SDLK_WORLD_9		= 169,
          SDLK_WORLD_10		= 170,
          SDLK_WORLD_11		= 171,
          SDLK_WORLD_12		= 172,
          SDLK_WORLD_13		= 173,
          SDLK_WORLD_14		= 174,
          SDLK_WORLD_15		= 175,
          SDLK_WORLD_16		= 176,
          SDLK_WORLD_17		= 177,
          SDLK_WORLD_18		= 178,
          SDLK_WORLD_19		= 179,
          SDLK_WORLD_20		= 180,
          SDLK_WORLD_21		= 181,
          SDLK_WORLD_22		= 182,
          SDLK_WORLD_23		= 183,
          SDLK_WORLD_24		= 184,
          SDLK_WORLD_25		= 185,
          SDLK_WORLD_26		= 186,
          SDLK_WORLD_27		= 187,
          SDLK_WORLD_28		= 188,
          SDLK_WORLD_29		= 189,
          SDLK_WORLD_30		= 190,
          SDLK_WORLD_31		= 191,
          SDLK_WORLD_32		= 192,
          SDLK_WORLD_33		= 193,
          SDLK_WORLD_34		= 194,
          SDLK_WORLD_35		= 195,
          SDLK_WORLD_36		= 196,
          SDLK_WORLD_37		= 197,
          SDLK_WORLD_38		= 198,
          SDLK_WORLD_39		= 199,
          SDLK_WORLD_40		= 200,
          SDLK_WORLD_41		= 201,
          SDLK_WORLD_42		= 202,
          SDLK_WORLD_43		= 203,
          SDLK_WORLD_44		= 204,
          SDLK_WORLD_45		= 205,
          SDLK_WORLD_46		= 206,
          SDLK_WORLD_47		= 207,
          SDLK_WORLD_48		= 208,
          SDLK_WORLD_49		= 209,
          SDLK_WORLD_50		= 210,
          SDLK_WORLD_51		= 211,
          SDLK_WORLD_52		= 212,
          SDLK_WORLD_53		= 213,
          SDLK_WORLD_54		= 214,
          SDLK_WORLD_55		= 215,
          SDLK_WORLD_56		= 216,
          SDLK_WORLD_57		= 217,
          SDLK_WORLD_58		= 218,
          SDLK_WORLD_59		= 219,
          SDLK_WORLD_60		= 220,
          SDLK_WORLD_61		= 221,
          SDLK_WORLD_62		= 222,
          SDLK_WORLD_63		= 223,
          SDLK_WORLD_64		= 224,
          SDLK_WORLD_65		= 225,
          SDLK_WORLD_66		= 226,
          SDLK_WORLD_67		= 227,
          SDLK_WORLD_68		= 228,
          SDLK_WORLD_69		= 229,
          SDLK_WORLD_70		= 230,
          SDLK_WORLD_71		= 231,
          SDLK_WORLD_72		= 232,
    SDLK_WORLD_73		= 233,
    SDLK_WORLD_74		= 234,
    SDLK_WORLD_75		= 235,
    SDLK_WORLD_76		= 236,
    SDLK_WORLD_77		= 237,
    SDLK_WORLD_78		= 238,
    SDLK_WORLD_79		= 239,
    SDLK_WORLD_80		= 240,
    SDLK_WORLD_81		= 241,
    SDLK_WORLD_82		= 242,
    SDLK_WORLD_83		= 243,
    SDLK_WORLD_84		= 244,
    SDLK_WORLD_85		= 245,
    SDLK_WORLD_86		= 246,
    SDLK_WORLD_87		= 247,
    SDLK_WORLD_88		= 248,
    SDLK_WORLD_89		= 249,
    SDLK_WORLD_90		= 250,
    SDLK_WORLD_91		= 251,
    SDLK_WORLD_92		= 252,
    SDLK_WORLD_93		= 253,
    SDLK_WORLD_94		= 254,
    SDLK_WORLD_95		= 255,
    */
        /* 0xFF */

        /* Numeric keypad */
        m_map_keys[SDLK_KP0 	    ] = "Numpad 0";
    m_map_keys[SDLK_KP1	        ] = "Numpad 1";
    m_map_keys[SDLK_KP2     	] = "Numpad 2";
    m_map_keys[SDLK_KP3	        ] = "Numpad 3";
    m_map_keys[SDLK_KP4     	] = "Numpad 4";
    m_map_keys[SDLK_KP5         ] = "Numpad 5";
    m_map_keys[SDLK_KP6     	] = "Numpad 6";
    m_map_keys[SDLK_KP7	        ] = "Numpad 7";
    m_map_keys[SDLK_KP8     	] = "Numpad 8";
    m_map_keys[SDLK_KP9	        ] = "Numpad 9";
    m_map_keys[SDLK_KP_PERIOD	] = "Numpad ~";
    m_map_keys[SDLK_KP_DIVIDE	] = "Numpad :";
    m_map_keys[SDLK_KP_MULTIPLY	] = "Numpad *";
    m_map_keys[SDLK_KP_MINUS	] = "Numpad -";
    m_map_keys[SDLK_KP_PLUS		] = "Numpad +";
    m_map_keys[SDLK_KP_ENTER	] = "Numpad Enter";
    m_map_keys[SDLK_KP_EQUALS	] = "Numpad =";

    /* Arrows + Home/End pad */
    m_map_keys[SDLK_UP			] = "Up";
    m_map_keys[SDLK_DOWN		] = "Down";
    m_map_keys[SDLK_RIGHT		] = "Right";
    m_map_keys[SDLK_LEFT		] = "Left";
    m_map_keys[SDLK_INSERT		] = "Insert";
    m_map_keys[SDLK_HOME		] = "Home";
    m_map_keys[SDLK_END		    ] = "End";
    m_map_keys[SDLK_PAGEUP		] = "Page up";
    m_map_keys[SDLK_PAGEDOWN	] = "Page down";

    /* Function keys */
    m_map_keys[SDLK_F1			] = "F1";
    m_map_keys[SDLK_F2			] = "F2";
    m_map_keys[SDLK_F3			] = "F3";
    m_map_keys[SDLK_F4			] = "F4";
    m_map_keys[SDLK_F5			] = "F5";
    m_map_keys[SDLK_F6			] = "F6";
    m_map_keys[SDLK_F7			] = "F7";
    m_map_keys[SDLK_F8			] = "F8";
    m_map_keys[SDLK_F9			] = "F9";
    m_map_keys[SDLK_F10		    ] = "F10";
    m_map_keys[SDLK_F11		    ] = "F11";
    m_map_keys[SDLK_F12		    ] = "F12";
    m_map_keys[SDLK_F13		    ] = "F13";
    m_map_keys[SDLK_F14		    ] = "F14";
    m_map_keys[SDLK_F15		    ] = "F15";

    /* Key state modifier keys */
    m_map_keys[SDLK_NUMLOCK     ] = "Numlock";
    m_map_keys[SDLK_CAPSLOCK    ] = "Capslock";
    m_map_keys[SDLK_SCROLLOCK   ] = "Scrollock";
    m_map_keys[SDLK_RSHIFT	    ] = "Right shift";
    m_map_keys[SDLK_LSHIFT      ] = "Left shift";
    m_map_keys[SDLK_RCTRL       ] = "Right CTRL";
    m_map_keys[SDLK_LCTRL       ] = "Left CTRL";
    m_map_keys[SDLK_RALT        ] = "Right ALT";
    m_map_keys[SDLK_LALT        ] = "Left ALT";
    //    m_map_keys[SDLK_RMETA       ] = "";
    //    m_map_keys[SDLK_LMETA       ] = "";
    //    m_map_keys[SDLK_LSUPER      ] = "";
    //    m_map_keys[SDLK_RSUPER      ] = "";
    //    m_map_keys[SDLK_MODE        ] = "";
    //    m_map_keys[SDLK_COMPOSE     ] = "";

    /* Miscellaneous function keys */
    //    m_map_keys[SDLK_HELP        ] = "";
    m_map_keys[SDLK_PRINT       ] = "Print";
    //    m_map_keys[SDLK_SYSREQ      ] = "";
    //    m_map_keys[SDLK_BREAK       ] = "";
    //    m_map_keys[SDLK_MENU        ] = "";
    //    m_map_keys[SDLK_POWER       ] = "";
    m_map_keys[SDLK_EURO        ] = "Euro";
    //    m_map_keys[SDLK_UNDO        ] = "";
}

void
ConfigureKeys::p1_up_clicked()
{
    mb_grab_key = true;
    m_which_player = 0;
    m_player_keys = KEY_UP;
}

void
ConfigureKeys::p1_down_clicked()
{
    mb_grab_key = true;
    m_which_player = 0;
    m_player_keys = KEY_DOWN;
}

void
ConfigureKeys::p1_left_clicked()
{
    mb_grab_key = true;
    m_which_player = 0;
    m_player_keys = KEY_LEFT;
}

void
ConfigureKeys::p1_right_clicked()
{
    mb_grab_key = true;
    m_which_player = 0;
    m_player_keys = KEY_RIGHT;
}

void
ConfigureKeys::p1_drop_clicked()
{
    mb_grab_key = true;
    m_which_player = 0;
    m_player_keys = KEY_BOMB;
}

void
ConfigureKeys::p1_special_clicked()
{
    mb_grab_key = true;
    m_which_player = 0;
    m_player_keys = KEY_SPECIAL;
}

void
ConfigureKeys::p2_up_clicked()
{
    mb_grab_key = true;
    m_which_player = 1;
    m_player_keys = KEY_UP;
}

void
ConfigureKeys::p2_down_clicked()
{
    mb_grab_key = true;
    m_which_player = 1;
    m_player_keys = KEY_DOWN;
}

void
ConfigureKeys::p2_left_clicked()
{
    mb_grab_key = true;
    m_which_player = 1;
    m_player_keys = KEY_LEFT;
}

void
ConfigureKeys::p2_right_clicked()
{
    mb_grab_key = true;
    m_which_player = 1;
    m_player_keys = KEY_RIGHT;
}

void
ConfigureKeys::p2_drop_clicked()
{
    mb_grab_key = true;
    m_which_player = 1;
    m_player_keys = KEY_BOMB;
}

void
ConfigureKeys::p2_special_clicked()
{
    mb_grab_key = true;
    m_which_player = 1;
    m_player_keys = KEY_SPECIAL;
}

}
