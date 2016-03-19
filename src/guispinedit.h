/**
 *
 * Classname / filename: SpinEdit / guispinedit.h
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

#ifndef SPINEDIT_H
#define SPINEDIT_H

#include "guitextedit.h"

namespace gui
{

    /**
     * SpinEdit
     * Signals: on_changed, on_enter, on_exit
     */
    class SpinEdit : public TextEdit
    {
    public:
        SpinEdit(); // default value = 0

        /**
         * here: text _must_ be a number!
         */
        SpinEdit(string val);
        SpinEdit(int    val);
        virtual ~SpinEdit();

        virtual void draw();

        /**
         * key down
         */
        void on_key_down(UINT keysym);

        /**
         * returns the value;
         * Example: Connect the signal to a function. In this function you can get
         *          the value with value()
         */
        int value() const;

        /**
         * set the value
         */
        void set_value(int val);

        /**
         * increase value by n
         */
        void inc(int n);

        /**
         * decrease value by n
         */
        void dec(int n);

        /**
         * set the value; note: val must be a number; else undefined behaviour!
         */
        void set_value(string val);

        /**
         * set rænge (min to max); default: -100 to +100
         */
        void set_range(int min, int max);

        /**
         * set the text (must be a number); better: use set_value instead!
         */
        virtual void set_text(string text);

        /**
         * get the text. much better: use value() instead!
         */
        virtual string text() const;

        /**
         * mouse down
         */
        virtual void on_mouse_down(int x, int y);

    protected:
        /**
         * called when the text changed; emits signal.
         */
        virtual void text_changed();

        /**
         * draw plus and minus for mouse.
         */
        void draw_plus_minus(ButtonState bs);

    private:
        /**
         * range variables
         */
        int m_range_min;
        int m_range_max;

    };


}
#endif // SPINEDIT_H
