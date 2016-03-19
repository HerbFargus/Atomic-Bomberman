// v0.1 by gm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

// todo: VIEL

#ifndef BRICKEXTRA_H
#define BRICKEXTRA_H

#include "cell.h"

namespace cell
{
    /**
     * Extra
     */
    class Extra : public Cell
    {
    public:
        Extra(int x, int y);
        virtual ~Extra();

//         virtual EnumBlocks class_id() const;

        virtual void draw();

        virtual bool solid() const;
    };
}

#endif // BRICKEXTRA_H
