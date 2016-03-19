// v0.9  by gm (created)
// v0.91 by gm (cosmetic changes)
// v0.95 by gm (new state concept; new event handlers)

#ifndef STATE_H
#define STATE_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include "typedefs.h"

#include <string>
#include <map>

#include <SDL/SDL.h>

namespace state
{
    using namespace std;

    class State;
    class AutomatonInput;

    class State
    {
    public:
        class AutomatonInput
        {
        public:
            AutomatonInput ();
            virtual ~AutomatonInput ();

            /**
             * resets the Input
             */
            void    reset();

            /**
             * sets input values;
             * used in the state classes
             */
            void    set_ok(bool bSet = true);
            void    set_cancel(bool bSet = true);
            void    set_value(int val);

            /**
             * returns input values;
             * used in next_state()
             */
            bool    ok();
            bool    cancel();
            int     value();

        private:
            bool    m_bOK;
            bool    m_bCancel;
            int     m_value;
        };

    public:
        State ();
        virtual ~State ();

        /**
         * event handlers:
         * this set of functions is called in the main loop and should be used for event handling.
         */
        virtual void on_key_down (UINT keysym);
        virtual void on_key_up (UINT keysym);

        virtual void on_mouse_down (const SDL_MouseButtonEvent& ev);
        virtual void on_mouse_up (const SDL_MouseButtonEvent& ev);

        virtual void on_mouse_move (const SDL_MouseMotionEvent& ev);

        /**
         * is called every time a frame is drawn
         */
        virtual void on_draw();

        /**
         * is called when the current state switches to this state
         */
        virtual void on_enter();

        /**
         * is called when the current state switches to another state
         */
        virtual void on_exit();

    protected:
        /**
         * start timer
         */
        void timer_start();

        /**
         * pause timer
         */
        void timer_pause();

        /**
         * right after timer_reset() is called timer_elapsed() returns 0 ms
         * if the timer was active it will still be active
         */
        void timer_reset();

        /**
         * returns the time in milliseconds that is elapsed since timer_start() was called
         * (with respect of timer_pause() calls)
         */
        UINT timer_elapsed();

    private:
        /**
         * elapsed time since timer_start() in milliseconds
         */
        UINT m_timer_elapsed;

        /**
         * in milliseconds
         */
        UINT m_timer_last_update;

        /**
         * true, if time should be "accumulated"
         */
        UINT m_bTimerActive;



        /**************************************
         * statics:
         **************************************/

    public:
        /**
         * allocates memory for all states (with new)
         */
        static void create_states();

        /**
         * deletes the states created with create_states()
         * calls current_state()->on_exit()
         */
        static void delete_states();

        /**
         * returns a pointer (not const!!!) to the current state
         */
        static State* current();

        /**
         * returns true if the current state is the Exit-State (class state::Exit)
         */
        static bool exit();

    protected:
        /**
         * return a reference to the static automaton input
         */
        static AutomatonInput& input();

        /**
         * exits the current state and invokes the next state
         *
         * this transition_function will determine which state is to invoke next
         * using the AutomatonInput (input())
         *
         * call this function in derived states to change to another state
         */
        static void next_state();

    private:
        /**
         * switches to a new state;
         * calls on_exit(), on_enter() and resets the AutomatonInput
         */
        static void switch_to_state(State* new_state);

    private:
        /**
         * that's the pointer to the current state
         */
        static State*        m_current_state;

        /**
         * dyn. allocated: all states
         */
        static State*               m_pAbout;
        static State*       m_pConfigureKeys;
        static State*  m_pDisplayGameResults;
        static State*       m_pDisplayWinner;
        static State*                m_pExit;
        static State*                m_pGame;
        static State*               m_pIntro;
        static State*            m_pMainMenu;
        static State*             m_pOptions;
        static State*               m_pOutro;
        static State*          m_pSelectGame;
        static State*       m_pSelectPlayers;
        static State*                m_pTest;
    };
}

#endif // STATE_H
