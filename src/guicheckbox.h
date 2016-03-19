/**
 *
 * Classname / filename: CheckBox / guicheckbox.h
 *
 * Author: Dominik Haumann
 *
 * Version: 0.3
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

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "guibutton.h"

#include <sigc++/signal_system.h>
#include <sigc++/generator.h>
#include <sigc++/rettype.h>
#include <sigc++/bind.h>
#include <sigc++/convert.h>

//#include <windows.h>

namespace gui
{
    using std::string;
    using namespace SigC;

    /**
     * CheckBox;
     * Signals: on_toggled, on_enter, on_exit
     */
    class CheckBox : public Button
    {
    public:
        CheckBox();
        CheckBox(string cap, bool checked = false);
        virtual ~CheckBox();

        // draw routines
        virtual void draw();

        // is called when you clicked or pressed RETURN, ENTER; SPACE
        virtual void click();

        /******************
         * check box states
         ******************/
        /**
         * return true, when checkbox is checked
         */
        bool checked() const;

        /**
         * un/check the check box
         */
        void set_checked(bool checked);

        /**
         * toggle the checkbox
         */
        bool toggle();

        /**
         * set checkbox alignment
         */
        void set_checkbox_alignment(CheckBoxAlignment cba);
         
        /**
         * get checkbox alignment
         */
        CheckBoxAlignment checkbox_alignment() const;

        /*
         * connection ex.: instance.on_toggled.connect(slot(Class, &Class::func));
         *                 instance.on_toggled.connect(function);
         *
         * signal is being emitted when toggling the checkbox!
         */
        SigC::Signal0<void, SigC::Marshal<void> > on_toggled;

    protected:
        // checkbox
        virtual void draw_checkbox(ButtonState bs);

    private:
        bool m_checked;

        CheckBoxAlignment m_chkbox_alignment;

    };

}
#endif // CHECKBOX_H
