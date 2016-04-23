/**
 *
 * Classname / filename: PushButton / pushbutton.h
 *
 * Author: Dominik Haumann
 *
 * Version: 0.2
 *
 */

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "guibutton.h"

#include <sigc++/sigc++.h>

namespace gui
{
    using namespace SigC;

    /**
     * PushButton;
     * Signals: on_clicked, on_enter, on_exit
     */
    class PushButton : public Button
    {
    public:
        PushButton();
        PushButton(string cap);
        virtual ~PushButton();

        // draw routines
        virtual void draw();

        // is called when you clicked or pressed RETURN, ENTER; SPACE
        virtual void click();

        /*
         * connection ex.: instance.signal.on_clicked(slot(Class, &Class::func));
         *                 instance.on_clicked.connect(function);
         */
        Signal0 <void, Marshal <void> > on_clicked;

    protected:

    private:

    };

}
#endif // PUSHBUTTON_H
