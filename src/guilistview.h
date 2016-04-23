/**
 *
 * Classname / filename: ListView / guilistview.h
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

#ifndef GUI_LISTVIEW_H
#define GUI_LISTVIEW_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif
          
#include "guibutton.h"

#include <sigc++/sigc++.h>

#include <string>
#include <vector>

namespace gui
{
    using namespace std;
    using namespace SigC;
    /**
     * ListView
     */
    class ListView : public Button
    {
    public:
        ListView(string cap);
        virtual ~ListView();

        // draw routines
        virtual void draw();

        // is called when you clicked or pressed RETURN, ENTER; SPACE
        //virtual void click();

        /** gui actions  */
        virtual void on_key_down(UINT keysym);
//        virtual void on_key_up(UINT keysym);
        virtual void on_mouse_down(int x, int y);
        virtual void on_mouse_up(int x, int y);
        virtual void on_mouse_move(int x, int y);

        /** add entries  */
        void add_string_list(const vector<string>& list, const vector<string>* data = 0);
        void add_string_list(const vector<string>& list, const vector<int>* data = 0);
        void add_string(const string& str, const string* data = 0);
        void add_string(const string& str, const int* data = 0);

        /** get entries  */
        const string* selected();
        const string* selected_str_data();
        const int* selected_int_data();

        /** set scrollbar alignment: right false:default; left:true  */
        void set_sb_align_left(bool left);
        bool sb_align() const;

        /** connection ex.:instance.signal.on_changed(slot(Class, &Class::func));
         *                 instance.on_changed.connect(function);  */
        Signal0 <void, Marshal <void> > on_changed;

    protected:
        /** draw selection  */
        virtual void draw_selection();

        /** draw entries  */
        virtual void draw_entries();

        /** draw everything else  */
        virtual void draw_listview();

        /** view number of entries  */
        int num_entries() const;

        /** called when selection changed  */
        void selection_changed();

    private:
        /** displayed text  */
        vector <string> m_entries;
        /** concat displayed text with string data  */
        vector <string> m_dat_str;
        /** concat displayed text with int data  */
        vector <int>    m_dat_int;

        /** number of entries in view  */
        int m_num_entries;
        /** value: -1 = no selection  */
        int m_selection;
        /** view begins with entry X  */
        int m_begin_with;

        /** scrollbar alignment; left=true, false: right  */
        bool m_sb_align_left;
    };
}
#endif // GUI_LISTVIEW_H

/** visualization ;)
+--+------------------------------------+--+
|  |                 12                 |  |
+--+--+---------------------------------+--+
|  |20| ENTRY 1  (20 height)            |  |
|  +--+ ENTRY 2                         |  |
|  |  | ENTRY 3                         |  |
|  |  | ...                             |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|12|20|                                 |12|
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  |  |                                 |  |
|  +--+                                 |  |
|  |20|                                 |  |
+--+--+---------------------------------+--+
|  |                 12                 |  |
+--+------------------------------------+--+
*/
