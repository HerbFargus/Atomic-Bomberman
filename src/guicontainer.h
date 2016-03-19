/**
 *
 * Classname / filename: Container / container.h
 *
 * Author: Dominik Haumann
 *
 * Version: 0.1
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

#ifndef CONTAINER_H
#define CONTAINER_H

#include "guibase.h"

#include <vector>

namespace gui
{
    using std::vector;

    /**
     * Container: handles all classes derived from Base
     */
    class Container
    {
    public:
        Container();
        virtual ~Container();

        // add a from Base derived control
        void    add(Base* pWnd);

        /**
         * creates the tab-order using the order from the vector;
         * call this only ONE time after all controls are added to the container!
         */
        void    create_tab_order();

        /**
         * experimental: step back a tab in the other direction
         * (this shell work)
         */
        void    tab_backward();

        // gives the key events to all controls
        void    on_key_down (UINT keysym);
        void    on_key_up (UINT keysym);

        // gives the mouse events to all controls
        void    on_mouse_down (int x, int y);
        void    on_mouse_up (int x, int y);
        void    on_mouse_move (int x, int y);

        /**
         * calls for every ctrl the draw() routine
         */
        void    draw_all();

        /**
         * removes all windows the container contains (but does NOT delete them)
         */
        void    clear();

        /**
         * if true the added controls will be deleted with 'delete';
         * the user does not have to delete them manually;
         * default is false
         */
        void    set_autodelete(bool autodel);

        /** 
         * returns the ctrl that has the focus.
         * importent: the add - sequence
         */
        int     current_focused();

    protected:
        /**
         * when the user clicks not in a control no control has the focus.
         * this function gives the focus to the window that _had_ the focus.
         */
        void restore_focus();

        /**
         * important is that p_last_focused_wnd points all time to the right wnd.
         * So we have to be up to date.
         */
        void update_last_focused_wnd();

    private:
        // contains all controls
        vector <Base*> m_wnds;

        /**
         * the wnd that had the focus...
         */
        Base*          p_last_focused_wnd;

        // if true the ctrls will be deleted; (default false)
        bool m_autodelete;
    };
}

#endif // CONTAINER_H
