// v0.11 by gm (created)
// v0.12 by mm
// v0.13 by gm (for testing only)
// v0.14 by gm (for testing only)
// v0.15 by gm (for testing only)

#include "stategame.h"
#include "globals.h"
#include "keyconfig.h"
#include "SDL/SDL.h"
#include <iostream>
#include <iomanip>
#include "player.h"
#include "gameinfo.h"
#include "imagelist.h"
#include "valuelist.h"

#include "render.h"
#include "input.h"
#include "inputkeyboard.h"

namespace state
{
    using namespace std;

    Game::Game ()
    {

    }

    Game::~Game ()
    {

    }

// EnumStates Game::id()
// {
//     return STATE_GAME;
// }

    void Game::on_enter()
    {
        Globals g;
//     g.game().player(0).set_active();
//     g.game().player(0).set_control(CONTROL_KEYBOARD, 0);
//     g.game().player(3).set_active();
//     g.game().player(3).set_control(CONTROL_KEYBOARD, 1);

        m_nDir = DIR_NORTH;
        m_Animation.SetAnimation(ANI_STAND, m_nDir);
        m_Animation.Start();

        m_back = g.render().LoadTexture("data/images/field00.png");
    }

    void
    Game::on_exit()
    {
        m_Animation.Stop();
    }

    void
    Game::on_draw()
    {
        Globals g;

//    SDL_Rect rect = {0, 0, 100, 100};
        //Globals::render().FillRect(rect, 0.0f, 1.0f, 1.0);
        //Globals::render().DrawText(10, 10, 1.0f, 0.0f, 0.0f, "Hallo");

        g.render().DrawTile(0, 0, g.values().res_w(), g.values().res_h(), m_back);

        m_Animation.Update();
        m_Animation.Draw(200, 200, 176, 176);

        static int xOff = 0;
        static int yOff = 0;

//  bool bIsMove = false;
//  static EnumAnims oldAnim = ANI_STAND;

//  Player& pi = g.game().player(0);
//  if(pi.control()->pressed(KEY_UP))
//  {
//      yOff -= 5;
//      if(m_nDir != DIR_NORTH)
//      {
//          m_nDir = DIR_NORTH;
//      }
//      bIsMove = true;
//  }
//  else if(pi.control()->pressed(KEY_LEFT))
//  {
//      xOff -= 5;
//      if(m_nDir != DIR_WEST)
//      {
//          m_nDir = DIR_WEST;
//      }
//      bIsMove = true;
//  }
//  else if(pi.control()->pressed(KEY_DOWN))
//  {
//      yOff += 5;
//      if(m_nDir != DIR_SOUTH)
//      {
//          m_nDir = DIR_SOUTH;
//      }
//      bIsMove = true;
//  }
//  else if(pi.control()->pressed(KEY_RIGHT))
//  {
//      xOff += 5;
//      if(m_nDir != DIR_EAST)
//      {
//          m_nDir = DIR_EAST;
//      }
//      bIsMove = true;
//  }

//  if(bIsMove)
//  {
//      if(oldAnim != ANI_WALK)
//      {
//          m_Animation.SetAnimation(ANI_WALK, m_nDir);
//          oldAnim = ANI_WALK;
//      }
//  }
//  else
//  {
//      if(oldAnim != ANI_STAND)
//      {
//          m_Animation.SetAnimation(ANI_STAND, m_nDir);
//          oldAnim = ANI_STAND;
//      }

//  }

        Globals::render().SetOffset(xOff, yOff);


        /**
         * Test, Debug, ...
         */
//     for (int i = 0; i < g.values().max_players(); ++i)
//     {
//      Player& pi = g.game().player(i);
//      if (pi.active())
//      {
//          if (pi.control()->pressed(KEY_UP))
//          cout << "Player " << setw(2) << i << ": UP " << "pressed." << endl;
//          else
//          ;//cout << "Player " << setw(2) << i << ": UP " << "released." << endl;

//          if (pi.control()->pressed(KEY_DOWN))
//          cout << "Player " << setw(2) << i << ": DOWN " << "pressed." << endl;
//          else
//          ;//cout << "Player " << setw(2) << i << ": DOWN " << "released." << endl;

//          if (pi.control()->pressed(KEY_LEFT))
//          cout << "Player " << setw(2) << i << ": LEFT " << "pressed." << endl;
//          else
//          ;//cout << "Player " << setw(2) << i << ": LEFT " << "released." << endl;

//          if (pi.control()->pressed(KEY_RIGHT))
//          cout << "Player " << setw(2) << i << ": RIGHT " << "pressed." << endl;
//          else
//          ;//cout << "Player " << setw(2) << i << ": RIGHT " << "released." << endl;

//          if (pi.control()->pressed(KEY_BOMB))
//          cout << "Player " << setw(2) << i << ": BOMB " << "pressed." << endl;
//          else
//          ;//cout << "Player " << setw(2) << i << ": BOMB " << "released." << endl;

//          if (pi.control()->pressed(KEY_SPECIAL))
//          cout << "Player " << setw(2) << i << ": SPECIAL " << "pressed." << endl;
//          else
//          ;//cout << "Player " << setw(2) << i << ": SPECIAL " << "released." << endl;

//      }
//     }
    }

    void
    Game::on_key_event(bool bKeydown, UINT keysym)
    {
        Globals g;



        if (bKeydown)
        {
            if (g.keycfg().key(KEY_GAME_ABORT) == keysym)
            {
                cerr << "hey..";
                input().set_cancel();
                next_state();
            }
        }
        else
        {
        }
    }

}
