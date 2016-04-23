/**
 *
 * Classname / filename: TextEdit / guitextedit.h
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

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include "guibase.h"

#include  <sigc++/sigc++.h>

namespace gui
{
    using namespace SigC;

    /**
     * class TextEdit
     * Signals: on_changed, on_enter, on_exit
     */
    class TextEdit : public Base
    {
    public:
        TextEdit();
        TextEdit(string text);
        virtual ~TextEdit();

        /**
         * draw; overwrite
         */
        virtual void draw();

        /**
         * key down
         */
        virtual void on_key_down(UINT keysym);

        /**
         * key up
         */
        virtual void on_key_up(UINT keysym);

        /**
         * set the text
         */
        virtual void set_text(string text);

        /**
         * get the text
         */
        virtual string text() const;

        /**
         * connection ex.: instance.on_changed.connect(slot(Class, &Class::func));
         *                 instance.on_changed.connect(function); // global function!
         *
         * here: signal means: text changed. You can get the text with instance.text()
         */
        Signal0 <void, Marshal <void> > on_changed;

    protected:
        /**
         * cursor position: navigate left / right
         */
        void navigate_left(bool bleft);

        /**
         * draw cursor
         */
        void draw_cursor(SDL_Rect rect);

        /**
         * draw border
         */
        ButtonState draw_border();

        /**
         * called when the text changed; emits signal.
         */
        virtual void text_changed();

    protected: // this only protected because spinedit have to have access!
        /**
         * contains the text
         */
        string m_text;

        /**
         * contains the cursor position
         */
        UINT m_cur_pos;

    private:

        /**
         * if RSHIFT / LSHIFT down: true; else false
         */
        bool m_lshift;

        /**
         * see m_lshift;
         */
        bool m_rshift;

        /**
         * every 1/10 sec it will be updated
         */
        Uint32 m_cursor_timestep;

        /**
         * opacity: will be inc/dec by .01 when m_cursor_timestep is updated!
         */
        double m_cursor_opacity;
        bool   m_cursor_inc;
    };

}
#endif // TEXTEDIT_H
