// v0.5  by gm (created)
// v0.51 by gm (cosmetic changes)

#include "textmessages.h"
#include "globals.h"
#include "mainconfig.h"
#include <iostream>

TextMessages::TextMessages () :
    m_ndf(Globals::maincfg().get(MC_MESSAGE_LIST))
{
    m_ndf.load();
}

TextMessages::~TextMessages ()
{

}

const string
TextMessages::get(string which) const
{
    string str = m_ndf.get(which.c_str());
    if (str == "")
        cerr << "Warning: class TextMessages::get(): string is empty." << endl;
    return str;
}
