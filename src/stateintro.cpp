// v0.1  by gm (created)
// v0.2  by dh
// v0.3  by dh (added protected enum-type: STATES; removed timer)
// v0.31 by gm (forgotten...)
// v0.32 by gm (adjusted to class dependencies)

#include "stateintro.h"
#include "globals.h"
#include "valuelist.h"
#include "render.h"
#include "keyconfig.h"
#include "sound.h"
#include "soundlist.h"
#include "imagelist.h"

#include <iostream>

namespace state
{
    using namespace std;

    Intro::Intro ()
    {
    }

    Intro::~Intro ()
    {

    }

    void
    Intro::on_enter()
    {
        timer_reset();
        timer_start();

        Globals g;

        // load images, sounds, durations
        m_img_logo  = g.render().LoadTexture(g.images().logo());
        m_img_title = g.render().LoadTexture(g.images().title());

        m_snd_back      = g.sound().load(g.soundlist().get_random_sound(SND_MUSIC_TITLE)); // and play directly
        g.sound().play(m_snd_back);

        m_snd_ab        = g.sound().load(g.soundlist().get_random_sound(SND_TITLE_INTRO));
        m_snd_stateexit = g.sound().load(g.soundlist().get_random_sound(SND_MENU_EXIT));

        m_duration_logo = g.values().get(VAL_INTRO_TIME_LOGO ) * 1000;
        m_duration_title= g.values().get(VAL_INTRO_TIME_TITLE) * 1000;

        m_current_state = STATE_LOGO;
    }

    void
    Intro::on_key_down(UINT keysym)
    {
        Globals g;

        if (SDLK_RETURN == keysym || SDLK_ESCAPE == keysym)
        {
            switch (m_current_state)
            {
                case STATE_LOGO:
                    {
                        m_current_state = STATE_TITLE;
                        break;
                    }

                case STATE_TITLE:
                    {
                        g.sound().play(m_snd_stateexit);
                        next_state();
                        break;
                    }
            }
        }
        else
        {
            g.sound().play(g.soundlist().get_random_sound(SND_MENU_MOVE));
        }
    }

    void
    Intro::on_draw()
    {
        static bool b_playab = true;
        Globals g;

        switch (m_current_state)
        {
            case STATE_LOGO:
                {
                    g.render().DrawTile(0, 0, g.values().res_w(), g.values().res_h(), m_img_logo);
                    break;
                }

            case STATE_TITLE:
                {
                    if (b_playab)
                    {
                        b_playab = false;
                        g.sound().play(m_snd_ab);
                        g.sound().play(m_snd_stateexit);
                        timer_reset();
                    }

                    g.render().DrawTile(0, 0, g.values().res_w(), g.values().res_h(), m_img_title);
                    break;
                }
        }

        if (b_playab)
        {
            if (timer_elapsed() > m_duration_logo)
                m_current_state = STATE_TITLE;
        }
        else
        {
            if (timer_elapsed() > m_duration_title)
            {
                g.sound().play(m_snd_stateexit);
                next_state();
            }
        }
    }

    void
    Intro::on_exit()
    {
        Globals g;
        // first load sound because of latency, then unload&stop current one to have a smooth switch
        const SndInfo* snd_main_menu = g.sound().load(g.soundlist().get_random_sound(SND_MUSIC_MENU_MAIN));
        g.sound().unload(m_snd_back);
        g.sound().play(snd_main_menu, true);
    }

}

