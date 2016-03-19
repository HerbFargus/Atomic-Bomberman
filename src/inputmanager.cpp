// v0.1  by mm (created)

#include "inputmanager.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "inputmouse.h"
//#include "input.h"
//#include "input.h"
#include <SDL/SDL.h>
#include <algorithm>
#include <iostream>
#include <exception>

namespace input
{
    using namespace std;

    Manager::Manager()
    {
    }

    Manager::~Manager()
    {
    }

    void
    Manager::init()
    {
        m_allinputs[TYPE_KEYBOARD].push_back(new Keyboard(0));

        m_allinputs[TYPE_KEYBOARD].push_back(new Keyboard(1));

        for (int i = 0; i < SDL_NumJoysticks(); ++i)                     // (TODO: algorithm) ???
        {
            m_allinputs[TYPE_JOYSTICK].push_back(new Joystick(i));
        }

        m_allinputs[TYPE_MOUSE].push_back(new Mouse());
    }

    void
    Manager::delete_all()
    {
        for (UINT i = 0; i < TYPE_NUMBER_OF; ++i)
        {
            for (UINT j = 0; j < m_allinputs[i].size(); ++j)
            {
                delete m_allinputs[i][j];
            }
        }
    }

    int
    Manager::number_available(EnumType type)
    {
        return m_allinputs[type].size();
    }


    Input*
    Manager::get(EnumType type, UINT index)
    {
        if (index < m_allinputs[type].size())
            return m_allinputs[type][index];
        else
        {
            cerr << "input::Manager::get(EnumType, int index): index out_of_range: " << index << endl;
            return 0;
        }

//         try
//         {
//             return &m_allinputs[type].at(index);
//         }
//         catch (out_of_range e)
//         {
//             cerr << "input::Manager::get(EnumType, int index): Exception out_of_range: " << e.what() << endl;
//         }
    }

    bool
    Manager::is_used(EnumType type, int index)
    {
        return find (m_used_list.begin(), m_used_list.end(), m_allinputs[type][index]) != m_used_list.end();
    }

    void
    Manager::reset_used_list()
    {
        m_used_list.clear();
    }

    void
    Manager::set_used(EnumType type, int index, bool bUsed)
    {
        if (bUsed && !is_used(type, index))
        {
            m_used_list.push_back (m_allinputs[type][index]);
        }
        else if (!bUsed)
        {
            PInputList::iterator it = find (m_used_list.begin(), m_used_list.end(), m_allinputs[type][index]);
            if (it != m_used_list.end())
                m_used_list.erase (it);
        }
    }

    PInputList&
    Manager::used_list()
    {
        return m_used_list;
    }
}
