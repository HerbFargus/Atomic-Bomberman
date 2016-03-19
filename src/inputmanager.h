// v0.1  by mm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

/**
 * TODO: Ändere etwas in input.h --> Fast alles wird neu kompiliert!!! (Weil in globals.h keine Forwarddekl. wegen namespaces möglich ist!!!)
 */

#include "input.h"

#include <list>
#include <vector>
using std::list;
using std::vector;

#include "typedefs.h"

namespace input
{
    enum EnumType { TYPE_KEYBOARD = 0,
                    TYPE_JOYSTICK,
                    TYPE_MOUSE,
                    TYPE_AI,
                    TYPE_NET,
                    TYPE_NUMBER_OF
    };

    typedef list < Input* > PInputList;
    typedef vector < Input* > PInputVector;

    class Manager
    {
    public:
        Manager();
        virtual ~Manager();

        void init ();

        // don't forget to call that!!!
        void delete_all();

        int number_available (EnumType type);

        Input* get (EnumType type, UINT index = 0);

        // TODO: testen
        void reset_used_list ();

        // TODO: testen
        bool is_used (EnumType type, int index);
        void set_used (EnumType type, int index, bool bUsed = true);

        PInputList& used_list();

    protected:

    private:
        PInputVector m_allinputs[TYPE_NUMBER_OF];
        PInputList m_used_list;

    };
}

#endif // INPUT_MANAGER_H
