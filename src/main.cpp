// v0.1 by gm (created)
// v0.2 by gm (adjusted to class changes)

#if HAVE_CONFIG_H
#  include <config.h>
#endif

/* (Create Makefile)
   progen -o ab_linux.pro `find -maxdepth 1 -regex "\(.*\.cpp\)\|\(.*\.h\)"` && tmake ab_linux.pro -o Makefile_qt && sed -e '/INCPATH/d' -e '/\/moc/d' -e '/\/uic/d' -e 's/^LIBS.*$/LIBS   =   -lSDL -lSDL_image -lGL -lm/' Makefile_qt > Makefile
*/

/**
 * Debian Pakete:
 * libsdl, libsdlimage, libgl?
 */

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#pragma warning(disable: 4786)
// libs: sdl_image.lib opengl32.lib sdlmain.lib sdl.lib
#endif

// no console at the moment
// #define WIN32_CONSOLE

#include <time.h>
// #include <SDL/SDL.h>
#include "render.h"
#include "animmng.h"
#include "globals.h"
#include "state.h"
#include "options.h"
#include "valuelist.h"
#include "timer.h"
#include "mainconfig.h"
#include "soundtotext.h"
#include "sound.h"
#include "inputkeyboard.h"
#include "inputjoystick.h"
#include "inputmouse.h"
#include "inputupdate.h"

#ifdef WIN32
# ifdef WIN32_CONSOLE
#  include <windows.h>
#  include <iostream>
#  include <fstream>
#  include <conio.h>
#  include <stdio.h>
#  include "guicon.h"
# endif
#endif

#include <iostream>
#include <algorithm>
using std::iostream;

using namespace state;
using namespace input;

/*
  #ifdef WIN32
  #define WIN32_LEAN_AND_MEAN
  #pragma warning(disable: 4786)

  filebuf fbuf;
  fbuf.open("log.txt", ios::out);
  ostream errorfile(&fbuf);
  cerr = errorfile;
  cout = errorfile;
  #endif
*/


#ifdef WIN32
// #ifndef __MINGW32__

// enable config.h definitions for win32 (has its own COPY of config.h)
#define DISABLE_LIBSIGC 1

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
// #else
//    int main ()
// #endif
#else
    int main (int argc, char* argv[])
#endif
{

#ifdef WIN32
 #ifdef WIN32_CONSOLE
    RedirectIOToConsole();
 #endif
#endif

    ValueList::load();

    Globals g;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
        //if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        cerr << "main.cpp: Unable to initialize SDL: " << SDL_GetError() << endl;
        return 1;
    }

    // Set the window caption
    SDL_WM_SetCaption("Atomic Bomberman", 0);

    // Initialize the render class (will set up OpenGL)
    if (!g.render().Init(g.values().res_w(), g.values().res_h(), 1==g.values().get(VAL_FULLSCREEN)?1:0))
    {
        cerr << "main.cpp: Unable to create OpenGL screen: " << SDL_GetError() << endl;
        SDL_Quit();
        return 2;
    }

    // Randomize
    srand(time(0));

#ifndef DISABLE_SOUND
    g.sound().init(22050);
    //  SDL_PauseAudio(true);
    SDL_PauseAudio(false);
#endif

    g.anim().Init();

    // inits the input controls...
    g.input().init();

    // load sound2text...
    g.snd2txt().load_from_file(g.maincfg().get(MC_SOUNDTOTEXT));

    // creates all states and sets the start state...
    State::create_states();

    //  SDL_ShowCursor(false);

    // maybe enable joystick events
    if (g.input().number_available(TYPE_JOYSTICK) > 0)
        SDL_JoystickEventState(SDL_ENABLE);

    bool bDone = false;
    SDL_Event event;

    bool bFreeMouse = false;

    while (!bDone && !State::exit())
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_F12) bDone = true;       // Nottastev

                if (event.key.keysym.sym == SDLK_F11)  // toggle free mouse
                {
                    bFreeMouse = !bFreeMouse;
                }

                State::current()->on_key_down (event.key.keysym.sym);
                break;

            case SDL_KEYUP:
                State::current()->on_key_up (event.key.keysym.sym);
                break;

            case SDL_MOUSEBUTTONDOWN:
                State::current()->on_mouse_down (event.button);
                break;

            case SDL_MOUSEBUTTONUP:
                State::current()->on_mouse_up (event.button);
                break;

            case SDL_MOUSEMOTION:
                State::current()->on_mouse_move (event.motion);
                break;

            case SDL_QUIT:
                bDone = true;
                break;
            }

            // Update input controls:
            if (!(event.type == SDL_MOUSEMOTION && bFreeMouse))
                for_each (g.input().used_list().begin(), g.input().used_list().end(), Update(event));
        }

        // For mouse as input:
        if (g.input().number_available(TYPE_MOUSE) == 1)
            if (Mouse* pm = dynamic_cast < Mouse * > (g.input().get(TYPE_MOUSE, 0)))
                pm->maybe_stop_mousemotion();

        // Update timer, current state and renderer:
        g.timer().refresh();
        g.render().BeginFrame();
        State::current()->on_draw();
        g.render().EndFrame();
    }

    // delete all states:
    State::delete_states();

    // delete the input controls:
    g.input().delete_all();

    g.anim().Shut();
    SDL_Quit();
    return 0;
}
