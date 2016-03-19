// v0.1  by gm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/


#ifndef BRICKBOMB_H
#define BRICKBOMB_H

#include "cell.h"

class Field;

namespace cell
{
    enum EnumBombType { BOMB_NORMAL = 0,
                        BOMB_JELLY,
                        BOMB_TRIGGER
    };

/**
 * Bomb
 */
    class Bomb : public Cell
    {
    public:
        /**
         * nPlayer: who dropped the bomb
         */
        Bomb(int x, int y, int nPlayer, EnumBombType type, int flame_length, int fuze_time);

        /**
         * copy ctor
         * TODO: check if all members are used!!!
         */
        Bomb(const Bomb & rhs);

        virtual ~Bomb();

        virtual void draw();

        virtual bool solid() const;

        /**
         * who droped the bomb
         */
        int player();

        /**
         * true, if bomb was triggered
         */
        bool triggered();

        /**
         * trigger the bomb
         * if (flame_delay == false) the bomb triggers immediately
         * if (flame_delay == true)  the bomb waits a short moment (see VAL_TIME_FLAME_TRIGGER)
         */
        void trigger(bool flame_delay = false);

        /**
         * returns the flame length of the bomb
         */
        int flame_length();
        
        EnumBombType type();
        
        /**
         * returns the unique bomb ID;
         * used to determine which trigger bomb is to be triggered
         */
        UINT bomb_id();

        /**
         * TODO
         */
        void kick(EnumDir dir);
        bool rolling() const;
        EnumDir roll_dir() const;

        /**
         * returns true if bomb is within cell
         * returns false if bomb is outside cell (field should create a new bomb and destroy the old one)
         * if outofcenter == true: return true if rolled over cell's center (or is right over the center)
         */
        bool out_of_cell(bool outofcenter);

        /**
         * changes m_rollPixPos to fit for the new bomb pos;
         * changes the position
         */
        void prepare_for_copy();
        void stop_rolling();

    private:
        /**
         * who droped the bomb
         */
        int m_player;

        /**
         * type of the flame
         */
        EnumBombType m_type;
        
        /**
         * the unique bomb ID
         */
        UINT m_nBombID;
        
        static int m_increasing_number;

        /**
         * length of the bomb's flame
         */
        int m_flame_length;

        /**
         * time till explosion (in milliseconds)
         */
        int m_time;

        /**
         * reference (in seconds) for m_time
         */
        double m_start_time;

        /**
         * true, if bomb was triggered
         */
        bool m_bTriggered;

        
        /**
         * rolling members
         */

        bool m_bRolling;
        EnumDir m_rollDir;
        double m_rollSpeed;
        double m_rollPixPos;
    };
}

#endif // BRICKBOMB_H
