// v0.1  by gm (created)
// v0.2  by gm (adjusted to class dependencies)
// v0.3  by dh (draw Text, handling input, play sounds, draw bomb)
// v0.31 by gm, mm (Windows C++ compiler compatibility)
// v0.32 by gm, mm
// v0.33 by dh (remove id completely, turn dynamic keys into SDL/SDL_keysym)
// v0.4  by dh (derived from SigC::Object; turned menu into gui::Buttons with signal/slot concept)
// v0.41 by dh (set the img_gui path for gui)

#ifndef STATEMAINMENU_H
#define STATEMAINMENU_H

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#include "state.h"
#include "animmng.h"
#include "enummainmenuchoice.h"

#ifndef DISABLE_LIBSIGC
 #include "guipushbutton.h"
 #include "guicheckbox.h"
 #include "guitextedit.h"
 #include "guispinedit.h"
 #include "guicontainer.h"
 #include "guienums.h"

 #include <sigc++/sigc++.h>
 //#include "sigc++/slot.h"
#endif // DISABLE_LIBSIGC

#include <SDL/SDL.h>

struct TexInfo;
class SndInfo;

namespace state
{
#ifndef DISABLE_LIBSIGC
    using namespace SigC;
    using namespace gui;
#endif
    class MainMenu : public State
#ifndef DISABLE_LIBSIGC
, public SigC::Object
#endif // DISABLE_LIGSIGC
    {

        public:
            MainMenu ();
            virtual ~MainMenu ();

            virtual   void on_enter();
            virtual   void on_exit();
            virtual   void on_draw();

            virtual	  void on_key_down(UINT keysym);
            virtual	  void on_key_up  (UINT keysym);

            virtual   void on_mouse_down (const SDL_MouseButtonEvent& ev);
            virtual   void on_mouse_up (const SDL_MouseButtonEvent& ev);
            virtual   void on_mouse_move (const SDL_MouseMotionEvent& ev);


            void     start_game_clicked();
            void       net_host_clicked();
            void       net_join_clicked();
            void        options_clicked();
            void configure_keys_clicked();
            void          about_clicked();
            void      exit_game_clicked();

            // switches to the next state using m_choice
            void switch_to_next_state();


        protected:
            TexInfo         *m_back;
            Animation       m_anim_bomb;
            const SndInfo   *m_snd_back;

            EnumChoice      m_choice;

#ifndef DISABLE_LIBSIGC
            /**
             * handles all classes derived from WndBase
             */
            Container       m_container;

            // all buttons;
            PushButton          *m_btn_start_game;
            PushButton          *m_btn_net_host;
            PushButton          *m_btn_net_join;
            PushButton          *m_btn_options;
            PushButton          *m_btn_configure_keys;
            PushButton          *m_btn_about;
            PushButton          *m_btn_exit_game;

            CheckBox            *m_chk;
            TextEdit            *m_edt;
            SpinEdit            *m_sed;
#endif // DISABLE_LIGSIGC

        protected:
            void draw_bomb_anim();


        private:

    };

}

#endif // STATEMAINMENU_H
