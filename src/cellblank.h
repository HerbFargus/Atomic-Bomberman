// v0.1 by gm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef BRICKBLANK_H
#define BRICKBLANK_H

#include "cell.h"

namespace cell
{
/**
 * Blank
 * no block
 */
    class Blank : public Cell
    {
    public:
        Blank(int x, int y);
        virtual ~Blank();

//         virtual EnumBlocks class_id() const;

        virtual void draw();

        virtual bool solid() const;
    };
}

#endif // BRICKBLANK_H
