/* by Dominik Haumann  */
/***************************************************************************
 *                                                                         *
 *   This program (class) is free software; you can redistribute it and/or *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef STATECONFIGUREKEYS_H
#define STATECONFIGUREKEYS_H

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include "state.h"
#include "animmng.h"
#include "enumkeys.h"
#include "enummainmenuchoice.h"

#ifndef DISABLE_LIBSIGC
 #include "guipushbutton.h"
 #include "guicontainer.h"
 #include "guienums.h"
#endif // DISABLE_LIBSIGC

#include <SDL/SDL_keysym.h>
#include <vector>
#include <string>

struct TexInfo;
class KeyConfig;


namespace state
{
    using namespace std;
#ifndef DISABLE_LIBSIGC
    using namespace SigC;
    using namespace gui;
#endif
    class ConfigureKeys : public State
#ifndef DISABLE_LIBSIGC
  , public SigC::Object
#endif // DISABLE_LIBSIGC
    {
    public:
        ConfigureKeys ();
        virtual ~ConfigureKeys ();

        virtual void on_enter();
        virtual void on_exit();
        virtual void on_draw();

        virtual	void on_key_down(UINT keysym);
        virtual	void on_key_up  (UINT keysym);

        virtual void on_mouse_down (const SDL_MouseButtonEvent& ev);
        virtual void on_mouse_up (const SDL_MouseButtonEvent& ev);
        virtual void on_mouse_move (const SDL_MouseMotionEvent& ev);


    protected:
        vector <string>    m_map_keys;

        /* Textures  */
        TexInfo     *m_bg;

        /* Animations  */
        Animation   m_anim_bomb;

        /* true: the next pressed key will be saved  */
        bool        mb_grab_key;

        /* represents current selection  */
        EnumPlayerKeys m_player_keys;

        /* pointer to static keycfg in globals  */
        KeyConfig   *mp_keyconfig;

    protected:
        /* map ASCII-code to string  */
        void create_key_map();

        /* create gui  */
        void create_gui();

        /* called in on_draw  */
        void draw_player_keys();
        void draw_menu_keys();
        /* when grabbing a key  */
        void draw_grab_key();

        /* button-slots  */
        void p1_up_clicked      ();
        void p1_down_clicked    ();
        void p1_left_clicked    ();
        void p1_right_clicked   ();
        void p1_drop_clicked    ();
        void p1_special_clicked ();

        void p2_up_clicked      ();
        void p2_down_clicked    ();
        void p2_left_clicked    ();
        void p2_right_clicked   ();
        void p2_drop_clicked    ();
        void p2_special_clicked ();

    private:
#ifndef DISABLE_LIBSIGC
        /* containers for gui elements
           active: get events
           passive: does not retrieve any event  */
        Container m_con_active;
        Container m_con_passive;

        PushButton *m_btn_p1_head;
        PushButton *m_btn_p1_up;
        PushButton *m_btn_p1_down;
        PushButton *m_btn_p1_left;
        PushButton *m_btn_p1_right;
        PushButton *m_btn_p1_drop;
        PushButton *m_btn_p1_special;

        PushButton *m_btn_p2_head;
        PushButton *m_btn_p2_up;
        PushButton *m_btn_p2_down;
        PushButton *m_btn_p2_left;
        PushButton *m_btn_p2_right;
        PushButton *m_btn_p2_drop;
        PushButton *m_btn_p2_special;
#endif // DISABLE_LIBSIGC

        /* 0: keys of player 0
           1: keys of player 1  */
        int m_which_player;
    };
}

#endif // STATECONFIGUREKEYS_H
