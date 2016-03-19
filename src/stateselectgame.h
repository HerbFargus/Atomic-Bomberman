/**
 *
 * Classname / filename: SelectGame / stateselectgame.h
 *
 * Author: Gregor Mitsch, Dominik Haumann
 *
 */
 
/***************************************************************************
 *                                                                         *
 *   This program (class) is free software; you can redistribute it and/or *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef STATESELECTGAME_H
#define STATESELECTGAME_H

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef WIN32
  #pragma warning(disable: 4786)
#endif

 
#include "state.h"
#include "animmng.h"

#ifndef DISABLE_LIBSIGC
 #include "guicontainer.h"
 #include "guienums.h"
 #include "guipushbutton.h"
 #include "guilistview.h"
// #include <sigc++/signal_system.h>
#endif // DISABLE_LIBSIGC

#include <string>
#include <vector>

class Scheme;

namespace state
{
using namespace std;
#ifndef DISABLE_LIBSIGC
using namespace SigC;
using namespace gui;
#endif

class SelectGame : public State
{
protected:
    /**
     * SchemePreview - previews a scheme in a small rect using the current map.
     */
    class SchemePreview
    {
    public:
        SchemePreview();
        virtual ~SchemePreview();

        /* draw scheme using offset x and y  */
        void draw(int offset_x, int offset_y);

        /* set the scheme's filename to preview  */
        void set_scheme(const string& name);

    protected:

    private:
        /* pointer to the scheme  */
        Scheme* mp_scheme;

        /* divide. example: if m_divisor == 2, the scheme is going to be drawn in half the size  */
        double     m_divisor;

        /* uses only the first picture of every animation!  */
        Animation   m_brick_solid;
        Animation   m_brick_breakable;
    };

public:
    SelectGame ();
    virtual ~SelectGame ();

    virtual void on_enter();
    virtual void on_exit();
    virtual void on_draw();

    virtual void on_key_down(UINT keysym);
    virtual void on_key_up  (UINT keysym);

    /* creates the schemelist and return the number of schemes.  */
    int     create_scheme_list();
    
protected:
    /* create gui elements; set properties  */
    void create_gui();

    /* previews the scheme  */
    SchemePreview   m_scheme_preview;
    
    /* contains all available levels.  */
    vector <string> m_scheme_list;

    /* the current selected level.  */
    int             m_selected_scheme;
	
private:
#ifndef DISABLE_LIBSIGC
    /* gui elements & control  */
    Container   m_gui_active;

    /* next, prev menu  */
    PushButton* m_btn_next;
    PushButton* m_btn_prev;

    /* scheme list  */
    ListView*   m_lv_schemes;
#endif // DISABLE_LIBSIGC
};

}

#endif // STATESELECTGAME_H

