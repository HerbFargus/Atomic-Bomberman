#ifndef STATETEST_H
#define STATETEST_H

#ifdef WIN32
#pragma warning(disable: 4786)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#endif

#include "state.h"
#include "animmng.h"

#include "soundtotext.h"

class Field;

namespace state
{



// enum
// {
//  DIR_NORTH=0,
//  DIR_WEST,
//  DIR_SOUTH,
//  DIR_EAST
// };


    class Test : public State
    {
    public:
        Test ();
        virtual ~Test ();

        virtual   void on_enter();
        virtual   void on_exit();
        virtual   void on_draw();
        virtual   void on_key_down(UINT keysym);

    private:
        /**
         * dyn. allocated
         */
        Field*     m_pField;

        Animation  m_Animation;

        int        m_nDir;


        SoundToText m_s2t;



    };

}

#endif // STATEGAME_H
