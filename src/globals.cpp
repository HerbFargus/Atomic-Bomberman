// v0.5 by gm (created)
// v0.6 by gm (removed some functions; game_info() added)
// v0.7 by gm (values() added, changed some function names --> attention: dependencies)
// v0.8 by gm (removed some functions, options() added)
// v0.9 by gm (made some functions const)

#include "globals.h"
#include "render.h"
#include "keyconfig.h"
#include "textmessages.h"
#include "imagelist.h"
#include "soundlist.h"
#include "sound.h"
#include "animmng.h"
#include "timer.h"
#include "mainconfig.h"
#include "gameinfo.h"
#include "valuelist.h"
#include "options.h"
#include "soundtotext.h"

Globals::Globals ()
{
    // must be empty !!!
}

Globals::~Globals ()
{
    // must be empty !!!
}

Render&
Globals::render()
{
    static Render r;
    return r;
}

AnimMng&
Globals::anim()
{
    static AnimMng am;
    return am;
}

Timer&
Globals::timer()
{
    static Timer t;
    return t;
}

Sound&
Globals::sound()
{
    static Sound snd;
    return snd;
}

input::Manager&
Globals::input()
{
    static input::Manager im;
    return im;
}

KeyConfig&
Globals::keycfg()
{
    static KeyConfig k;
    return k;
}

const MainConfig&
Globals::maincfg()
{
    static MainConfig mc;
    return mc;
}

const TextMessages&
Globals::textmsg()
{
    static TextMessages tm;
    return tm;
}

ImageList&
Globals::images()
{
    static ImageList il;
    return il;
}

SoundList&
Globals::soundlist()
{
    static SoundList sl;
    return sl;
}

GameInfo&
Globals::game()
{
    static GameInfo gi;
    return gi;
}

const ValueList&
Globals::values()
{
    static ValueList vl;
    return vl;
}

Options&
Globals::options()
{
    static Options o;
    return o;
}

SoundToText&
Globals::snd2txt()
{
    static SoundToText stt;
    return stt;
}

/**************************************************************************************************/
/**
 * splits a string into tokens delimited by delimiters
 */

namespace std
{
    void
    tokenize_string(const string& str, vector<string>& tokens, const string& delimiters = " ")
    {
        // Skip delimiters at beginning.
        string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        // Find first "non-delimiter".
        string::size_type pos     = str.find_first_of(delimiters, lastPos);

        while (string::npos != pos || string::npos != lastPos)
        {
            // Found a token, add it to the vector.
            tokens.push_back(str.substr(lastPos, pos - lastPos));
            // Skip delimiters.  Note the "not_of"
            lastPos = str.find_first_not_of(delimiters, pos);
            // Find next "non-delimiter"
            pos = str.find_first_of(delimiters, lastPos);
        }
    }
}
