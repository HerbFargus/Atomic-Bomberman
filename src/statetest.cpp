// v0.1  by gm (created)

#include "SDL/SDL.h"

#include "statetest.h"
#include "globals.h"
#include "keyconfig.h"
#include "player.h"
#include "gameinfo.h"
#include "render.h"
#include "field.h"
#include "schememanager.h"
#include "valuelist.h"

#include "soundlist.h"
#include "sound.h"

#include <iostream>

#include "inputmanager.h"

namespace state
{
    using namespace std;
    using namespace input;

    Test::Test ()
    {

    }

    Test::~Test ()
    {

    }

//     EnumStates Test::id()
//     {
//         return STATE_TEST;
//     }




#define TEST_FIELD
//#define TEST_SOUNDTOTEXT




#ifdef TEST_FIELD
    void
    Test::on_enter()
    {
        Globals g;
        SchemeManager schmng;
        schmng.find_schemes();

        // init Player, GameInfo !!!

        // TODO: damit die Spieler nicht beim Neustarten in die Bricks laufen --> irgendwas tun!!!


        g.game().player(0).set_active();
        g.game().player(0).set_input(g.input().get(TYPE_KEYBOARD, 0));
        g.input().set_used (TYPE_KEYBOARD, 0);

//           g.game().player(1).set_active();
//           g.game().player(1).set_input(g.input().get(TYPE_JOYSTICK, 0));
//           g.input().set_used (TYPE_JOYSTICK, 0);

        g.game().player(2).set_active();
        g.game().player(2).set_input(g.input().get(TYPE_MOUSE, 0));
        g.input().set_used (TYPE_MOUSE, 0);



//         g.game().player(3).set_active();
//         g.game().player(3).set_control(CONTROL_KEYBOARD, 0);
//         g.game().player(4).set_active();
//         g.game().player(4).set_control(CONTROL_KEYBOARD, 0);
//         g.game().player(5).set_active();
//         g.game().player(5).set_control(CONTROL_KEYBOARD, 0);
//         g.game().player(6).set_active();
//         g.game().player(6).set_control(CONTROL_KEYBOARD, 0);
//         g.game().player(7).set_active();
//         g.game().player(7).set_control(CONTROL_KEYBOARD, 0);
//         g.game().player(8).set_active();
//         g.game().player(8).set_control(CONTROL_KEYBOARD, 1);

        g.game().player(9).set_active();
        g.game().player(9).set_input(g.input().get(TYPE_KEYBOARD, 1));
        g.input().set_used (TYPE_KEYBOARD, 1);

        // 0: viele Bricks
        // 1: fast alles frei (Kick test)
        // 2: disease test
        g.game().set_new_match(schmng.scheme(1).filename, "", 0, 3, true);

        m_pField = new Field();

        g.game().set_field(m_pField);


//        SDL_ShowCursor(SDL_DISABLE);
    }
#endif

#ifdef TEST_SOUNDTOTEXT
    void
    Test::on_enter()
    {
        Globals g;
        if (!m_s2t.load_from_file(string("./data/config/sound2text.res")))
            cerr << "Test::on_enter(): m_s2t.load_from_file failed." << endl;
    }
#endif

#ifdef TEST_FIELD
    void
    Test::on_exit()
    {
//  m_Animation.Stop();
        Globals g;

        g.input().set_used (TYPE_KEYBOARD, 0, false);
        g.input().set_used (TYPE_MOUSE, 0, false);
        g.input().set_used (TYPE_KEYBOARD, 1, false);

        delete m_pField;
        g.game().set_field(0);

//        SDL_ShowCursor(true);
    }
#endif

#ifdef TEST_SOUNDTOTEXT
    void
    Test::on_exit()
    {
    }
#endif

#ifdef TEST_FIELD
    void Test::on_draw()
    {
        m_pField->process_field();
        m_pField->draw();
//        cout << m_pField->cell(0, 0).cell().solid();    // TODO: warum geht das nicht???
    }
#endif

#ifdef TEST_SOUNDTOTEXT
    void
    Test::on_draw()
    {
        Globals g;
        g.render().SetTextSizes(16, 16);     // TODO: verbessern!!!
        if (m_s2t.info().bText)
            g.render().DrawText(g.values().get(VAL_FIELD_OFFSET_X), 30, 1.0, 1.0, 1.0, m_s2t.info().text);
    }
#endif

#ifdef TEST_FIELD
    void
    Test::on_key_down(UINT keysym)
    {

        Globals g;

        // DEBUG:
//        g.keycfg().debug_print_keyname(keysym);

        if (SDLK_ESCAPE == keysym)
        {
            input().set_cancel();
            next_state();
        }

    }
#endif

#ifdef TEST_SOUNDTOTEXT
    void
    Test::on_key_down(UINT keysym)
    {
        Globals g;


        if (g.keycfg().key(KEY_MENU_CANCEL) == keysym)
        {
            input().set_cancel();
            next_state();
        }

        if (g.keycfg().key(KEY_MENU_OK) == keysym)
        {
            string snd = g.soundlist().get_random_sound(SND_POWERUP);
            g.sound().play(snd);
            if (!m_s2t.lookup(snd))
                cerr << "Test::on_enter(): m_s2t.lookup failed." << endl;
        }
    }
#endif

}
