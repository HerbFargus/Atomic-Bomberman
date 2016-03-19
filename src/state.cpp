// v0.9  by gm (created)
// v0.91 by gm (cosmetic changes)
// v0.95 by gm (new state concept; new event handlers)

#ifdef WIN32
  #define DISABLE_LIBSIGC 1
#endif

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include "state.h"
#include <SDL/SDL.h>

#include "stateabout.h"
#include "stateconfigurekeys.h"
#include "statedisplaygameresults.h"
#include "statedisplaywinner.h"
#include "stategame.h"
#include "stateintro.h"
#include "stateoutro.h"
#include "statemainmenu.h"
#include "stateoptions.h"
#include "stateselectgame.h"
#include "stateselectplayers.h"
#include "stateexit.h"
#include "statetest.h"

#include "enummainmenuchoice.h"
#include <iostream>

namespace state
{
    using namespace std;

    State* State::       m_current_state = 0;

    State* State::              m_pAbout = 0;
    State* State::      m_pConfigureKeys = 0;
    State* State:: m_pDisplayGameResults = 0;
    State* State::      m_pDisplayWinner = 0;
    State* State::               m_pExit = 0;
    State* State::               m_pGame = 0;
    State* State::              m_pIntro = 0;
    State* State::           m_pMainMenu = 0;
    State* State::            m_pOptions = 0;
    State* State::              m_pOutro = 0;
    State* State::         m_pSelectGame = 0;
    State* State::      m_pSelectPlayers = 0;
    State* State::               m_pTest = 0;



    State::State () :
        m_timer_elapsed(0),
        m_timer_last_update(0),
        m_bTimerActive(false)
    {

    }

    State::~State ()
    {

    }

    void
    State::on_enter()
    {

    }

    void
    State::on_key_down (UINT)
    {
    }

    void
    State::on_key_up (UINT)
    {
    }

    void
    State::on_mouse_down (const SDL_MouseButtonEvent&)
    {
    }

    void
    State::on_mouse_up (const SDL_MouseButtonEvent&)
    {
    }

    void
    State::on_mouse_move (const SDL_MouseMotionEvent&)
    {
    }


    void
    State::on_draw()
    {

    }

    void
    State::on_exit()
    {

    }

    void
    State::timer_start()
    {
        if (!m_bTimerActive)
        {
            m_bTimerActive = true;
            m_timer_last_update = SDL_GetTicks();
        }
    }

    void
    State::timer_pause()
    {
        if (m_bTimerActive)
        {
            m_bTimerActive = false;
            m_timer_elapsed += SDL_GetTicks() - m_timer_last_update;
        }

    }

    void
    State::timer_reset()
    {
        m_timer_elapsed = 0;
    }

    UINT
    State::timer_elapsed()
    {
        if (m_bTimerActive)
        {
            UINT time = SDL_GetTicks();
            m_timer_elapsed += time - m_timer_last_update;
            m_timer_last_update = time;
        }

        return m_timer_elapsed;
    }

    State::AutomatonInput& 
    State::input()
    {
        static State::AutomatonInput input;
        return input;
    }

    State*
    State::current()
    {
        return m_current_state;
    }

    bool
    State::exit()
    {
        return current() == m_pExit;
    }

    void
    State::create_states()
    {
        m_pAbout = new About();
        m_pConfigureKeys = new ConfigureKeys();
        m_pDisplayGameResults = new DisplayGameResults();
        m_pDisplayWinner = new DisplayWinner();
        m_pExit = new Exit();
        m_pGame = new Game();
        m_pIntro = new Intro();
        m_pMainMenu = new MainMenu();
        m_pOptions = new Options();
        m_pOutro = new Outro();
        m_pSelectGame = new SelectGame();
        m_pSelectPlayers = new SelectPlayers();
        m_pTest = new Test();

        // set start state:
        m_current_state = m_pIntro;
        m_current_state->on_enter();
    }

    void
    State::delete_states()
    {
        current()->on_exit();

        delete m_pAbout;
        delete m_pConfigureKeys;
        delete m_pDisplayGameResults;
        delete m_pDisplayWinner;
        delete m_pExit;
        delete m_pGame;
        delete m_pIntro;
        delete m_pMainMenu;
        delete m_pOptions;
        delete m_pOutro;
        delete m_pSelectGame;
        delete m_pSelectPlayers;
        delete m_pTest;
    }

    void
    State::switch_to_state(State* new_state)
    {
        m_current_state->on_exit();
        m_current_state->input().reset();
        m_current_state = new_state;
        m_current_state->on_enter();
    }

    State::AutomatonInput::AutomatonInput ()
    {
        reset();
    }

    State::AutomatonInput::~AutomatonInput ()
    {

    }

    void
    State::AutomatonInput::reset()
    {
        m_bCancel = false;
        m_bOK = false;
        m_value = 0;
    }

    bool
    State::AutomatonInput::ok()
    {
        return m_bOK;
    }

    bool
    State::AutomatonInput::cancel()
    {
        return m_bCancel;
    }

    int
    State::AutomatonInput::value()
    {
        return m_value;
    }

    void
    State::AutomatonInput::set_ok(bool bSet /*= true*/)
    {
        m_bOK = bSet;
    }

    void
    State::AutomatonInput::set_cancel(bool bSet /*= true*/)
    {
        m_bCancel = bSet;
    }

    void
    State::AutomatonInput::set_value(int val)
    {
        m_value = val;
    }

    void
    State::next_state()
    {
        if (current() == m_pIntro)
        {
            switch_to_state(m_pMainMenu);
        }
        else if (current() == m_pMainMenu)
        {
            if (input().cancel())
                switch_to_state(m_pOutro);
//              switch_to_state(EXIT]);
            else if (input().ok())
            {
                switch (input().value())
                {
                case CHOICE_STARTGAME:
#ifdef DISABLE_LIBSIGC
                    switch_to_state(m_pTest);
#else
                switch_to_state(m_pSelectGame);
#endif // DISABLE_LIGS
                    break;

                case CHOICE_NETWORK_HOST:
                    switch_to_state(m_pOutro);
                    break;

                case CHOICE_NETWORK_JOIN:
                    switch_to_state(m_pOutro);
                    break;

                case CHOICE_OPTIONS:
                    switch_to_state(m_pOptions);
                    break;

                case CHOICE_KEYCFG:
                    switch_to_state(m_pConfigureKeys);
                    break;

                case CHOICE_ABOUT:
                    switch_to_state(m_pAbout);
                    break;

                case CHOICE_EXIT:
                    switch_to_state(m_pOutro);
                    break;
                }
            }
        }
        else if (current() == m_pGame)
        {
            if (input().cancel())
            {
                switch_to_state(m_pMainMenu);
            }
            else
            {
            }
        }
        else if (current() == m_pOutro)
        {
            switch_to_state(m_pExit);
        }
        else if (current() == m_pAbout)
        {
        }
        else if (current() == m_pConfigureKeys)
        {
            switch_to_state(m_pMainMenu);
        }
        else if (current() == m_pDisplayGameResults)
        {
        }
        else if (current() == m_pDisplayWinner)
        {
        }
        else if (current() == m_pOptions)
        {
        }
        else if (current() == m_pSelectPlayers)
        {
        }
        else if (current() == m_pExit)
        {
        }
        else if (current() == m_pTest)
        {
            if (input().cancel())
            {
//              switch_to_state(MAIN_MENU]);
                switch_to_state(m_pTest);
            }
            else
            {
            }
        }
        else
        {
            cerr << "Error by programer: State::next_state(): unknown state." << endl;
        }
    }
}
