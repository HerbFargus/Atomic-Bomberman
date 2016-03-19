// v0.5 by gm (created)
// v0.6 by gm (made the EnumMainConfigKeys global, changed the identifier)
// v0.7 by gm (get (...) is now const)
// v0.8 by gm (gui path added)

#ifndef MAINCONFIG_H
#define MAINCONFIG_H

#include "nameddatafile.h"
#include <string>
using namespace std;

enum EnumMainConfigKeys { MC_ANIM_PATH = 0,
                          MC_ANIM_LIST,
                          MC_KEY_CONFIG,
                          MC_IMAGE_PATH,
                          MC_IMAGE_LIST,
                          MC_OPTIONS_CONFIG,
                          MC_MESSAGE_LIST,
                          MC_SCHEME_PATH,
                          MC_SOUND_LIST,
                          MC_SOUND_PATH,
                          MC_VALUE_LIST,
                          MC_SOUNDTOTEXT,
                          MC_GUI_PATH
};


class MainConfig
{
public:
    MainConfig ();
    virtual ~MainConfig ();

    const string get(EnumMainConfigKeys which) const;

private:
    NamedDataFile m_ndf;
};

#endif // MAINCONFIG_H
