// v0.1 by gm (created)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "options.h"
#include "globals.h"
#include "mainconfig.h"
#include "valuelist.h"

Options::Options()
    : m_ndf(Globals::maincfg().get(MC_OPTIONS_CONFIG))
{
    m_ndf.load();
}

Options::~Options()
{
}

// ATTENTION: g.values().keyStrings() must be declared static in ValueList because otherwise
//            ValueList's ctor was called and an infinite loop will occur
//            (but only on Linux !?, we all wait for the new linux kernel... :-])

bool
Options::exists (EnumValues which) const
{
    return m_ndf.exists(ValueList::keyStrings()[which].c_str());
}

int
Options::get(EnumValues which) const
{
    return m_ndf.get(ValueList::keyStrings()[which].c_str());
}

void
Options::set(EnumValues which, int value)
{
    m_ndf.set(ValueList::keyStrings()[which].c_str(), value);
}

string
Options::get(EnumOptionsStr which) const
{
    return m_ndf.get(ndf_option_strings_str[which].c_str());
}

void
Options::set(EnumOptionsStr which, string value)
{
    m_ndf.set(ndf_option_strings_str[which].c_str(), value);
}

// TODO: testen (vor allem ndf::remove()!!!)
void
Options::reset()
{
    for (int i = 0; i < VAL_NUMBER_OF; ++i)
    {
        m_ndf.remove(ValueList::keyStrings()[i].c_str());
    }
}
