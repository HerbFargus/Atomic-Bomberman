// v0.5 by gm (created)
// v0.6 by gm (removed some functions; game_info() added)
// v0.7 by gm (values() added, changed some function names --> attention: dependencies)
// v0.8 by gm (removed some functions, options() added)
// v0.9 by gm (made some functions const)

#ifndef GLOBALS_H
#define GLOBALS_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

class Render;
class MainConfig;
class KeyConfig;
class TextMessages;
class ImageList;
class SoundList;
class Sound;
class AnimMng;
class Timer;
class GameInfo;
class ValueList;
class Options;
class SoundToText;

#include "inputmanager.h"
using input::Manager;

/**
 * this class is designed to have only ONE instance;
 * all values are to be loaded from file;
 */
class Globals
{
public:
    Globals ();
    virtual ~Globals ();

    static const MainConfig& maincfg();

    /**
     * returns a reference to the render engine
     */
    static Render& render();

    /**
     * returns a reference to the animation manager
     */
    static AnimMng& anim();

    /**
     * returns a reference to the global timer
     */
    static Timer& timer();

    /**
     * returns a reference to the key configuration
     */
    static KeyConfig& keycfg();

    /**
     * returns a reference to the sound engin
     */
    static Sound& sound();

    /**
     * returns a reference to the input manager
     */
    static input::Manager& input();

    /**
     * returns a reference to the text messages class
     */
    static const TextMessages& textmsg();

    /**
     * returns a reference to the image list
     */
    static ImageList& images();

    /**
     * returns a reference to the sound list
     */
    static SoundList& soundlist();

    /**
     * returns a reference to the game info object
     */
    static GameInfo& game();

    /**
     * returns a reference to the value list
     */
    static const ValueList& values();

    /**
     * returns a reference to the options
     */
    static Options& options();

    /**
     * returns a reference to the soundtotext object
     */
    static SoundToText& snd2txt();


protected:
private:
    // no member variables allowed!
};

#endif // GLOBALS_H
