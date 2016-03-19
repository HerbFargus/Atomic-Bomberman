// v0.1 by gm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef OPTIONS_H
#define OPTIONS_H

#include "nameddatafile.h"
#include "enumoptions.h"
#include "enumvalues.h"

// todo: testen

/**
 * Options contains values that are intended to be changed
 * interactively by the user
 */
class Options
{
public:
    Options();
    virtual ~Options();

    /**
     * returns true if 'which' is customized
     */
    bool exists (EnumValues which) const;

    int    get(EnumValues which) const;
    string get(EnumOptionsStr which) const;
    
    void set(EnumValues which, int value);
    void set(EnumOptionsStr which, string value);

    /**
     * removes all customizations
     */
    void reset ();

private:
    NamedDataFile m_ndf;

};

#endif // OPTIONS_H
