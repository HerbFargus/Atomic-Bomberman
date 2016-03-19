// v0.1  by gm (created)
// v0.2  by dh
// v0.3  by dh (added protected enum-type: STATES; removed timer)
// v0.31 by gm (forgotten...)

#ifndef STATEINTRO_H
#define STATEINTRO_H

#include "state.h"

struct  TexInfo;
class   SndInfo;

namespace state
{

class Intro : public State
{
public:
    Intro ();
    virtual ~Intro ();

	virtual   void on_enter();
	virtual   void on_exit();
	virtual   void on_draw();
	virtual	  void on_key_down(UINT keysym);

protected:
    enum STATE { STATE_LOGO = 0, STATE_TITLE };
    STATE     m_current_state;

     // sound-pointers
    const SndInfo   *m_snd_back;
    const SndInfo   *m_snd_ab;
    const SndInfo   *m_snd_stateexit;

    // image-pointers
    TexInfo         *m_img_logo;
    TexInfo         *m_img_title;

    // some timing specific variables
    unsigned int    m_duration_logo;
    unsigned int    m_duration_title;
private:

};

}

#endif // STATEINTRO_H

