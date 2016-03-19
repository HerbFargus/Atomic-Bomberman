// v0.1 by gm (created)
// v0.2 by gm (some functionality added)
// v0.5 by gm (copy_numbers(...) added)


/******************************************************************************
 * LICENSE: GPL v2 (General Public License v2)                                *
 ******************************************************************************/

#ifndef POWERUPS_H
#define POWERUPS_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include "enumpowerups.h"
#include "cellbomb.h"
using cell::Bomb;


/**
 * Powerups:
 * stores information about how much powerups the player has got / are to be places onto the field
 */
class Powerups
{
public:
    Powerups();
    virtual ~Powerups();

    /**
     * sets all values to zero
     */
    void reset();
    
    /**
     * copies the number of each powerup from rhs;
     * leaves other values untouched
     */
    void copy_numbers (const Powerups & rhs);

    /**
     * sets the number of the specified powerup the player owns
     */
    void set(EnumPowerups which, int value);

    /**
     * gets the number of the specified powerup the player owns
     */
    const int  get(EnumPowerups which) const;

    /**
     * increases the number of the specified powerup the player owns
     */
    void inc(EnumPowerups which, int offset);
    
protected:
    /**
     * sets all values to zero
     */
    void init();

private:
    int  m_powerups[PU_NUMBER_OF];
};

#endif // POWERUPS_H
