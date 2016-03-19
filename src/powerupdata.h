// v0.1 by gm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef POWERUPDATA_H
#define POWERUPDATA_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include "typedefs.h"

#include <list>
using std::list;

/**
 * PowerupData
 * manages all the powerup functionality
 */
class PowerupData
{
public:
    PowerupData();
    virtual ~PowerupData();
    
    /**
     * resets all values
     */
    void reset();
    
    /**
     * trigger bomb
     * TODO: doc
     */
    void set_trigger_bombs(int number);
    void inc_trigger_bombs(int offset);
    int trigger_bombs() const;
    void add_bomb_id (UINT bomb_id);
    UINT remove_next_bomb_id();


protected:

private:
    /**
     * [(1) the player can put m_nTriggerBombs plus as many trigger bombs as PU_BOMBS he has.]
     * if the player gets PU_TRIGGER --> (1)
     * if the player gets PU_BOMB --> (1)
     */
    int m_nTriggerBombs;
    
    typedef list < int > TriggerBombIdList;
    
    TriggerBombIdList m_tbombIDs;

};

#endif // POWERUPDATA_H
