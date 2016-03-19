// v0.1 by gm (created)

#ifndef STATEOUTRO_H
#define STATEOUTRO_H

#include "state.h"

struct  TexInfo;
class   SndInfo;

namespace state
{

class Outro : public State
{ 
public:
    Outro ();
    virtual ~Outro ();

	virtual   void on_enter();
	virtual   void on_exit();
	virtual   void on_draw();
	virtual	  void on_key_down(UINT keysym);

protected:

    // sound
	const SndInfo*  m_snd_game_exit;
    const SndInfo*  m_snd_back;

    // textures
    TexInfo*    m_img_mainmenu;
private:

};

}

#endif // STATEOUTRO_H
