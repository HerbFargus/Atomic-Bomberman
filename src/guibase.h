/**
 *
 * Classname / filename: Base / guibase.h
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

#ifndef GUIBASE_H
#define GUIBASE_H

#include <string>
#include <SDL/SDL.h>

#include "guienums.h"

#include <sigc++/sigc++.h>

typedef unsigned int UINT;

namespace gui
{
    using namespace std;//::string;
    using namespace SigC;

    /**
     * Base (abstract)
     */
    class Base
    {
    public:
        Base();
        virtual ~Base();

        /**
         * abstract draw; overwrite
         */
        virtual void draw() = 0;

        /*********************
         * (re-)size-functions
         *********************/
        /**
         * resize the width and height
         */
        void    wnd_resize(int width, int height);

        /**
         * set the window's origin and the width and height
         */
        void    wnd_set_rect(int x, int y, int width, int height);

        /**
         * set the window's origin
         */
        void    wnd_set_origin(int x, int y);

        /**
         * get the window
         */
        SDL_Rect wnd_size();

        /**
         * set the font size; default==16x16
         */
        void set_font_size(int width, int height);

        /*********************************
         * focus functions (default false)
         *********************************/
        /**
         * give focus
         */
        void set_focus(bool bfocus);

        /**
         * return whether wnd has focus or not
         */
        bool has_focus() const;

        /**
         * set the next wnd that will be focused pressing TAB
         */
        void set_next_focus(Base* next_focus);


        /*************************
         * key events (overwrite!)
         *************************/
        /**
         * key down
         */
        virtual void on_key_down(UINT keysym);

        /**
         * key up
         */
        virtual void on_key_up(UINT keysym);

        /***************************
         * mouse events (overwrite!)
         ***************************/
        /**
         * mouse down
         */
        virtual void on_mouse_down(int x, int y);

        /**
         * mouse up
         */
        virtual void on_mouse_up(int x, int y);

        /**
         * mouse move
         */
        virtual void on_mouse_move(int x, int y);

        /*****************
         * border settings
         *****************/
        /**
         * set the border type. See Base::BorderType!
         */
        void set_border_type(BorderType bt);

        /**
         * get the border type
         */
        BorderType border_type() const;

        /*******************
         * global image path
         *******************/
        /**
         * in this directory are all images. All gui-ctrls which use images will use this dir
         */
        static void set_img_path(string path);

        /**
         * get the img-path
         */
        string img_path() const;

        /**************************
         * text alignment routines.
         **************************/
        /**
         * set text alignment
         */
        void set_text_alignment(TextAlignment ta);

        /**
         * get text alignment
         */
        TextAlignment text_alignment() const;

    public: // signals
        /**
         * on_enter is emitted when getting the focus
         */
        SigC::Signal0 <void, SigC::Marshal <void> > on_enter;

        /**
         * on_exit is emitted when losing the focus
         */
        SigC::Signal0 <void, SigC::Marshal <void> > on_exit;

    public: // has to be public because of MSVC :(
        // every state will draw another border
        enum ButtonState {
            BS_MOUSE_OVER = 0,
            BS_MOUSE_DOWN,
            BS_HAS_FOCUS,
            BS_NOT_FOCUSED,
            BS_NONE
        };

    protected:
        // draw border routines
        void draw_border(ButtonState bs);

    protected:
        // pressing TAB will activate the next control
        void    next_focus();

        // check, whether the mouse click is in the wnd
        bool    mouse_in_wnd(int x, int y);

        // mouse-state
        void    set_mouse_down(bool b_down);
        bool    mouse_down() const;
        void    set_mouse_in_wnd(bool b_in_wnd);
        bool    mouse_over() const;

    protected:
        // size-members
        int     m_x;
        int     m_y;
        int     m_w;
        int     m_h;

        // font size (default: 16x16)
        int     m_font_size_w;
        int     m_font_size_h;

    private:
        // focus (default: false)
        bool    m_has_focus;
        Base*   mp_next_focus;

        // mouse-state
        bool    mb_mouse_down;
        bool    mb_mouse_over;

        // img-path
        static string m_img_path;

        // border type; default == BT_ALWAYS
        BorderType m_border_type;

        // text alignment; default = TAL_CENTER
        TextAlignment m_text_alignment;
    };
}

#endif // GUIBASE_H
