// v0.5   by gm (created)
// v0.501 by gm (cosmetic changes)

#ifndef SCHEMEMANAGER_H
#define SCHEMEMANAGER_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <string>
#include <vector>
using namespace std;

#include "typedefs.h"

class SchemeManager
{
public:
    class SchemeInfo
    {
    public:
        string filename;
        string name;
        int    version;
    };

    typedef vector < SchemeInfo > SchemeInfoVector;

public:
    SchemeManager ();
    virtual ~SchemeManager ();

    /**
     * looks in the standard scheme directory for *.sch files
     * and fills the SchemeManager class
     */
    void   find_schemes();

    /**
     * number of found schemes
     */
    int    number();

    /**
     * returns a SchemeInfo reference
     * index = 0..number()-1
     */
    const SchemeInfo& scheme(UINT index);

private:
    SchemeInfoVector   m_schemes;
};

#endif // SCHEMEMANAGER_H
