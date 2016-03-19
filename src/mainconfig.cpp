// v0.5 by gm (created)
// v0.6 by gm (made the EnumMainConfigKeys global, changed the identifier)
// v0.7 by gm (get (...) is now const)
// v0.8 by gm (gui path added)

#include "mainconfig.h"
#include <iostream>

MainConfig::MainConfig () :
    m_ndf("./ab.cfg")
{
    m_ndf.load();
}

MainConfig::~MainConfig ()
{

}

const string
MainConfig::get(EnumMainConfigKeys which) const
{
    switch (which)
    {
    case MC_ANIM_PATH:
        return m_ndf.get("anim_path"); break;

    case MC_ANIM_LIST:
        return m_ndf.get("anim_list"); break;

    case MC_KEY_CONFIG:
        return m_ndf.get("key_config"); break;

    case MC_IMAGE_PATH:
        return m_ndf.get("image_path"); break;

    case MC_IMAGE_LIST:
//      cout << "remove this line!!!: Debug: MainConfig: " << m_ndf.get("image_list").to_string() << endl;
        return m_ndf.get("image_list"); break;

    case MC_OPTIONS_CONFIG:
        return m_ndf.get("options_config"); break;

    case MC_MESSAGE_LIST:
        return m_ndf.get("message_list"); break;

    case MC_SCHEME_PATH:
//      cout << "remove this line!!!:" << m_ndf.get("scheme_path").to_string();
        return m_ndf.get("scheme_path"); break;

    case MC_SOUND_LIST:
        return m_ndf.get("sound_list"); break;

    case MC_SOUND_PATH:
        return m_ndf.get("sound_path"); break;

    case MC_VALUE_LIST:
        return m_ndf.get("value_list"); break;

    case MC_SOUNDTOTEXT:
        return m_ndf.get("sound2text_list"); break;

    case MC_GUI_PATH:
        return m_ndf.get("gui_path"); break;

    default:
        cerr << "MainConfig::get(...): ERROR." << endl;
        return "";
    }
}
