// v0.1 by gm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef DISEASES_H
#define DISEASES_H

#include "enumdiseases.h"

/**
 * Diseases
 */
class Diseases
{
public:
    Diseases();
    virtual ~Diseases();

    /**
     * deactivates all diseases: todo: scheme customization
     */
    void reset();

    /**
     * activates 'number' new different diseases
     */
    void infect (int number);

    /**
     * deactivates all diseases
     */
    void cure_all();

    /**
     * returns the number of diseases the player has got
     */
    int infected ();
    
    /**
     * returns true, if disease 'which' is enabled
     */ 
    const bool active(EnumDiseases which) const;

    /**
     * returns the speed the player should have if he has got molasses
     */
    double speed_molasses() const;

    /**
     * returns the speed the player should have if he has got crack
     */
    double speed_crack() const;

    /**
     * call this to confirm swapping
     */
    void swap_ok();

    /**
     * prints which diseases are active / inactive
     */
    void debug_print_diseases();

protected:
    /**
     * deactivates all diseases
     */
    void init();
    
    void play_sound (EnumDiseases which);

    /**
     * activates / deactivates the disease 'which';
     * handles exclusion rules.
     */ 
    void activate(EnumDiseases which, bool bActivate = true);

    EnumDiseases choose_random();

private:
    /**
     * is a disease active or not:
     */
    bool m_diseases[DSE_NUMBER_OF];

    // TODO:
    static int m_times[DSE_NUMBER_OF];

    static int m_probablities[DSE_NUMBER_OF];
};

#endif // DISEASES_H
