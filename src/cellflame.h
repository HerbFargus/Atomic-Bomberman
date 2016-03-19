// v0.1  by gm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef BRICKFLAME_H
#define BRICKFLAME_H

#include "cell.h"

namespace cell
{
    enum EnumFlameType { FLAME_CROSS = 0,
                         FLAME_HORIZ,
                         FLAME_VERT,
                         FLAME_NORTH,     // end pieces
                         FLAME_WEST,
                         FLAME_SOUTH,
                         FLAME_EAST
    };

/**
 * Flame
 */
    class Flame : public Cell
    {
    public:
        /**
         * nPlayer: who's bomb created this flame
         */
        Flame(int x, int y, int nPlayer, EnumFlameType type);

        virtual ~Flame();

        EnumFlameType type() const;

        virtual void draw();

        virtual bool solid() const;

        /**
         * who's bomb exploded?
         */
        int player() const;


    private:
        /**
         * type of the flame
         */
        EnumFlameType m_type;

        /**
         * who's bomb exploded?
         */
        int m_player;

        /**
         * reference time value for 'how long should the flame burn'
         */
        double m_start_time;
    };
}

#endif // BRICKFLAME_H
