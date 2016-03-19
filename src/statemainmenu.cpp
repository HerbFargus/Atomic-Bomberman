// v0.1  by gm (created)
// v0.2  by gm (adjusted to class dependencies)
// v0.21 by gm (adjusted to class dependencies)
// v0.3  by dh (see header file)
// v0,32 by gm, mm (Windows Compiler compatibility)
// v0.33 by dh (see header file)
// v0.4  by dh ( "    "     "  )
// v0.41 by dh (")

#ifdef WIN32
  #define DISABLE_LIBSIGC 1
#endif

#include "statemainmenu.h"
#include "globals.h"
#include "valuelist.h"
#include "render.h"
#include "keyconfig.h"
#include "nameddatafile.h"
#include "imagelist.h"
#include "sound.h"
#include "soundlist.h"
#include "animmng.h"
#include "mainconfig.h"

#include <SDL/SDL_keysym.h>

namespace state
{
    MainMenu::MainMenu ()
        : m_back(0)
    {
    }

    MainMenu::~MainMenu ()
    {

    }

    void MainMenu::on_enter()
    {
        Globals g;

        g.render().SetTextSizes(24, 24);


        m_back = g.render().LoadTexture(g.images().mainmenu());
        m_anim_bomb.SetAnimation(ANI_BOMB);
        m_anim_bomb.Start();

        m_snd_back = g.sound().load(g.soundlist().get_random_sound(SND_MUSIC_MENU_MAIN));
		if (!g.sound().is_running(m_snd_back))
		{
			g.sound().play(m_snd_back, true);
		}

        timer_reset();
        timer_start();

        SDL_EnableKeyRepeat(g.values().get(VAL_MENU_KEYREPEAT_DELAY), g.values().get(VAL_MENU_KEYREPEAT_INTERVAL));

        int m = g.values().res_w() / 2 + 50;

        m_choice = CHOICE_STARTGAME;

#ifndef DISABLE_LIBSIGC
        // captions
        m_btn_start_game        = new PushButton("Start Game");
        m_btn_net_host          = new PushButton("Host Network Game");
        m_btn_net_join          = new PushButton("Join Game");
        m_btn_options           = new PushButton("Options");
        m_btn_configure_keys    = new PushButton("Configure Keys");
        m_btn_about             = new PushButton("About");
        m_btn_exit_game         = new PushButton("Exit Game");

        m_chk                   = new CheckBox("Toggle me!");
        m_edt                   = new TextEdit("default");
        m_sed                   = new SpinEdit(5);

        m_btn_start_game->set_img_path(g.maincfg().get(MC_GUI_PATH));

        // button places
        m_btn_start_game        ->wnd_set_rect(m, 150, 300, 40);
        m_btn_net_host          ->wnd_set_rect(m, 200, 300, 40);
        m_btn_net_join          ->wnd_set_rect(m, 250, 300, 40);
        m_btn_options           ->wnd_set_rect(m, 300, 300, 40);
        m_btn_configure_keys    ->wnd_set_rect(m, 350, 300, 40);
        m_btn_about             ->wnd_set_rect(m, 400, 300, 40);
        m_btn_exit_game         ->wnd_set_rect(m, 450, 300, 40);

        m_chk         ->wnd_set_rect(m, 500, 300, 40);
        m_edt         ->wnd_set_rect(m, 550, 300, 40);
        m_sed         ->wnd_set_rect(m, 600, 300, 40);

           // connections
        m_btn_start_game        ->on_clicked.connect(slot(*this, &MainMenu::start_game_clicked));
        m_btn_net_host          ->on_clicked.connect(slot(*this, &MainMenu::net_host_clicked));
        m_btn_net_join          ->on_clicked.connect(slot(*this, &MainMenu::net_join_clicked));
        m_btn_options           ->on_clicked.connect(slot(*this, &MainMenu::options_clicked));
        m_btn_configure_keys    ->on_clicked.connect(slot(*this, &MainMenu::configure_keys_clicked));
        m_btn_about             ->on_clicked.connect(slot(*this, &MainMenu::about_clicked));
        m_btn_exit_game         ->on_clicked.connect(slot(*this, &MainMenu::exit_game_clicked));

        // properties
        m_btn_start_game        ->set_font_size(24, 24);
        m_btn_net_host          ->set_font_size(24, 24);
        m_btn_net_join          ->set_font_size(24, 24);
        m_btn_options           ->set_font_size(24, 24);
        m_btn_configure_keys    ->set_font_size(24, 24);
        m_btn_about             ->set_font_size(24, 24);
        m_btn_exit_game         ->set_font_size(24, 24);

        m_btn_start_game->set_text_alignment(TAL_CENTER);
        m_chk           ->set_checkbox_alignment(CBA_LEFT);
        m_chk           ->set_text_alignment(TAL_CENTER);
        m_edt           ->set_text_alignment(TAL_CENTER);

        // container-handler
        m_container.add(m_btn_start_game    );
        m_container.add(m_btn_net_host      );
        m_container.add(m_btn_net_join      );
        m_container.add(m_btn_options       );
        m_container.add(m_btn_configure_keys);
        m_container.add(m_btn_about         );
        m_container.add(m_btn_exit_game     );
        m_container.add(m_chk     );
        m_container.add(m_edt);
        m_container.add(m_sed);

        m_container.create_tab_order();

        // m_container will delete the buttons when calling Container::clear() (or destructor)
        m_container.set_autodelete(true);

        m_btn_start_game->set_focus(true);
#endif // DISABLE_LIGSIGC
    }

    void MainMenu::on_draw()
    {
#ifndef DISABLE_LIBSIGC
        Globals g;

        g.render().DrawTile(0, 0, g.values().res_w(), g.values().res_h(), m_back);

        m_container.draw_all();
        draw_bomb_anim();
#endif // DISABLE_LIGSIGC
    }

    void MainMenu::on_key_down(UINT keysym)
    {
#ifndef DISABLE_LIBSIGC
        Globals g;

        // cancel
        if (keysym == SDLK_ESCAPE)
        {
            g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));

            input().set_cancel();
            next_state();
        }
        else
        {
            if (keysym == SDLK_DOWN)
            {
                g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));

                m_container.on_key_down(SDLK_TAB);
            }
            else
            {
                if (keysym == SDLK_UP)
                {
                    g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));

                    m_container.tab_backward();
                }
                else
                {
                    if (keysym == SDLK_RETURN)
                        g.sound().play(g.soundlist().get_random_sound(SND_MENU_EXIT));

                    m_container.on_key_down(keysym);
                }
            }
        }
#else
        input().set_ok();
        input().set_value(CHOICE_STARTGAME);
        next_state();
#endif // DISABLE_LIBSIGC
    }

    void MainMenu::on_key_up(UINT keysym)
    {
#ifndef DISABLE_LIBSIGC
        m_container.on_key_up(keysym);
#endif // DISABLE_LIGSIGC
    }

    void MainMenu::on_exit()
    {
        Globals g;

        g.render().DeleteTexture(m_back);

        SDL_EnableKeyRepeat(0, 0); // 0,0 disables key-repeat

        if (m_choice != CHOICE_KEYCFG)
            g.sound().stop(m_snd_back);

#ifndef DISABLE_LIBSIGC
        // deletes the Buttons*, too
        m_container.clear();
#endif // DISABLE_LIGSIGC
    }

    void MainMenu::on_mouse_down (const SDL_MouseButtonEvent& ev)
    {
#ifndef DISABLE_LIBSIGC
        m_container.on_mouse_down(ev.x, ev.y);
#endif // DISABLE_LIGSIGC
    }

    void MainMenu::on_mouse_up (const SDL_MouseButtonEvent& ev)
    {
#ifndef DISABLE_LIBSIGC
        m_container.on_mouse_up(ev.x, ev.y);
#endif // DISABLE_LIGSIGC
    }

    void MainMenu::on_mouse_move (const SDL_MouseMotionEvent& ev)
    {
#ifndef DISABLE_LIBSIGC
        m_container.on_mouse_move(ev.x, ev.y);
#endif // DISABLE_LIGSIGC
    }


    void MainMenu::draw_bomb_anim()
    {
#ifndef DISABLE_LIBSIGC
        // update m_choice
        m_choice = static_cast<EnumChoice>(m_container.current_focused());

        Globals g;

        int middle = g.values().res_w() / 2;
        m_anim_bomb.Update();
        m_anim_bomb.Draw(middle, 190 + 50*m_choice, 50, 50);
#endif // DISABLE_LIGSIGC
    }

    void MainMenu::switch_to_next_state()
    {
#ifndef DISABLE_LIBSIGC
        Globals g;
        g.sound().play(g.soundlist().get_random_sound(SND_MENU_EXIT));

        input().set_value(m_choice);
        input().set_ok();

        next_state();
#endif // DISABLE_LIGSIGC
    }

    // SLOT
    void MainMenu::start_game_clicked()
    {
        m_choice = CHOICE_STARTGAME;
        switch_to_next_state();
    }

    // SLOT
    void MainMenu::net_host_clicked()
    {
        m_choice = CHOICE_NETWORK_HOST;
        switch_to_next_state();
    }

    // SLOT
    void MainMenu::net_join_clicked()
    {
        m_choice = CHOICE_NETWORK_JOIN;
        switch_to_next_state();
    }

    // SLOT
    void MainMenu::options_clicked()
    {
        m_choice = CHOICE_OPTIONS;
        switch_to_next_state();
    }

    // SLOT
    void MainMenu::configure_keys_clicked()
    {
        m_choice = CHOICE_KEYCFG;
        switch_to_next_state();
    }

    // SLOT
    void MainMenu::about_clicked()
    {
        m_choice = CHOICE_ABOUT;
        switch_to_next_state();
    }

    // SLOT
    void MainMenu::exit_game_clicked()
    {
        m_choice = CHOICE_EXIT;
        switch_to_next_state();
    }
}
