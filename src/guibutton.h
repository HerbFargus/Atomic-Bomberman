/**
 *
 * Classname / filename: Button / button.h
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

#ifndef BUTTON_H
#define BUTTON_H

#include "guibase.h"

#include <string>

namespace gui
{
   using std::string;

    /**
     * abstract class Button
     */
    class Button : public Base
    {
    public:
        Button();
        virtual ~Button();

        // draw
        virtual void draw() = 0;

        
        // key events; overwrite!
        virtual void on_key_down(UINT keysym);
        virtual void on_key_up(UINT keysym);

        // mouse events; overwrite!
        virtual void on_mouse_up(int x, int y);

        /**
         * clicking with the mouse or pressing ENTER or RETURN will call Button::click
         */
        virtual void click();

        /**
         * set caption
         */
        void    set_caption(string cap);

        /**
         * get caption
         */
        string  caption() const;

    protected:
        // button routines
        void set_button_pressed(bool b_pressed);
        bool button_pressed() const;

        /**
         * draw border
         */
        ButtonState draw_border();

    private:
        // caption
        string  m_caption;

        // if a button is pressed by mouse or key this is true
        bool m_button_pressed;
    };

}
#endif // BUTTON_H
