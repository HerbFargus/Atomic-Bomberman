// v0.11 by gm (created)
// v0.12 by mm
// v0.13 by gm (for testing only)
// v0.14 by gm (for testing only)
// v0.15 by gm (for testing only)

#ifndef STATEGAME_H
#define STATEGAME_H

#ifdef WIN32
#pragma warning(disable: 4786)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#endif

#include "state.h"
#include "animmng.h"

namespace state
{

    class Game : public State
    {
    public:
        Game ();
        virtual ~Game ();

        virtual   void on_enter();
        virtual   void on_exit();
        virtual   void on_draw();
        virtual   void on_key_event(bool bKeydown, UINT keysym);

    private:
        Animation  m_Animation;
        int        m_nDir;

        TexInfo         *m_back;


    };
}

#endif // STATEGAME_H
