// v0.1 by gm (created)

#include "stateoutro.h"
#include "globals.h"
#include "render.h"
#include "keyconfig.h"
#include "sound.h"
#include "soundlist.h"
#include "imagelist.h"
#include "valuelist.h"
#include "soundtotext.h"

namespace state
{
    Outro:: Outro()
    {
    }

    Outro::~Outro ()
    {
    }

    void
    Outro::on_enter()
    {
        Globals g;

        string snd = g.soundlist().get_random_sound(SND_GAME_EXIT);
        m_snd_game_exit = g.sound().load(snd);
        m_img_mainmenu = g.render().LoadTexture(g.images().mainmenu());
        timer_reset();
        timer_start();

        g.sound().play(m_snd_game_exit);
        g.snd2txt().lookup(snd);

        g.render().SetTextSizes(32, 32);
    }

    void
    Outro::on_key_down(UINT keysym)
    {
        if (SDLK_ESCAPE == keysym)
        {
            next_state();
        }
    }

    void
    Outro::on_draw()
    {
        if (m_snd_game_exit != NULL)
        {
            if (timer_elapsed() > static_cast<unsigned int>(m_snd_game_exit->length_in_ms) + 100)
            {
                next_state();
            }
        }

        Globals g;

        g.render().DrawTile(0,0, g.values().res_w(), g.values().res_h(), m_img_mainmenu);

        string text1 = g.snd2txt().text();
        string text2 = "";

        if (text1.length() >= 25)
        {
            text2 = text1;
            text1.erase(25, string::npos);
            text2.erase(0, 25);
        }
        g.render().DrawText(500, 400, 1.0, 1.0, 1.0, text1);
        g.render().DrawText(500, 450, 1.0, 1.0, 1.0, text2);
    }

    void
    Outro::on_exit()
    {
        Globals::sound().unload(m_snd_game_exit);
    }

}
