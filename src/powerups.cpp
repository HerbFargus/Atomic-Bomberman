// v0.1 by gm (created)
// v0.2 by gm (some functionality added)
// v0.5 by gm (copy_numbers(...) added)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "powerups.h"
#include "globals.h"
#include "gameinfo.h"
#include "scheme.h"
#include "valuelist.h"

#include <iostream>
#include <algorithm>
using namespace std;

Powerups::Powerups()
{
    init();
}

Powerups::~Powerups()
{
}

void
Powerups::init()
{
    int i;
    for (i = 0; i < PU_NUMBER_OF; ++i)       // (TODO: algorithm)
    {
        m_powerups[i] = 0;
    }
}

void
Powerups::copy_numbers (const Powerups & rhs)
{
    copy (rhs.m_powerups, rhs.m_powerups + PU_NUMBER_OF, m_powerups);
}


void
Powerups::reset()
{
    init();

//    Globals g;
//    const Scheme& scheme = Globals::game().scheme();
//
//    scheme.powerup_info(this);

//    int i;
//    // Reset Powerups:
//    int born_with, override_value;
//    bool bForbidden;
//    for (i = 0; i < PU_NUMBER_OF; ++i)
//    {
//        scheme.powerup_info(i, &born_with, &override_value, &bForbidden);
//        if (born_with != 0)
//        {
//            m_powerups[i] = born_with;     // born_with override
//        }
//        else
//        {
//            // Attention: make sure that VAL_INIT_PU_BOMB is the first of the VAL_INIT_PU... values
//            m_powerups[i] = g.values().get(static_cast <EnumValues> (VAL_PU_INIT_BOMB + i));  
//        }
//    }
//    if (g.values().get(static_cast <EnumValues> (VAL_PU_INIT_BOMB + PU_NUMBER_OF)) != g.values().get(VAL_PU_INIT_LAST))
//        cerr << "Error: Powerups::reset(): number of VAL_INIT_UP_... entries does not match with PU_NUMBER_OF" << endl;


}

void
Powerups::set(EnumPowerups which, int value)
{
    m_powerups[which] = value;
}

const int
Powerups::get(EnumPowerups which) const
{
    return m_powerups[which];
}

void
Powerups::inc(EnumPowerups which, int offset)
{
    m_powerups[which] += offset;
}


