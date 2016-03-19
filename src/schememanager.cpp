// v0.5   by gm (created)
// v0.501 by gm (cosmetic changes)

#include "schememanager.h"
#include <iostream>
#include <algorithm>
#include "filefinder.h"
#include "scheme.h"
#include "globals.h"
#include "mainconfig.h"

SchemeManager::SchemeManager ()
{

}

SchemeManager::~SchemeManager ()
{

}

void
SchemeManager::find_schemes()
{
    Globals g;
    FileFinder finder;

    StringVector files = finder.find_files(g.maincfg().get(MC_SCHEME_PATH), "*.sch");
    sort(files.begin(), files.end());

    m_schemes.clear();

    for (StringVector::iterator it = files.begin(); it != files.end(); ++it)           // (TODO: algorithm) ???
    {
        Scheme scheme;

        if (scheme.load_from_file(g.maincfg().get(MC_SCHEME_PATH) + (*it)))
        {
            SchemeInfo si;
            si.filename = Globals::maincfg().get(MC_SCHEME_PATH) + (*it);
            si.name = scheme.name();
            si.version = scheme.version();

            m_schemes.push_back(si);
        }
    }
}

int
SchemeManager::number()
{
    return m_schemes.size();
}

const SchemeManager::SchemeInfo&
SchemeManager::scheme(UINT index)
{
    if (index >= 0 && index < m_schemes.size())
    {
        return m_schemes[index];
    }
    else
    {
        cerr << "SchemeManager::scheme(int index): 'index' out of range! When this message appears you have to recall find_schemes()" << endl;
        SchemeInfo err;
        m_schemes.push_back(err);
        return m_schemes[0];
    }
}
