// v0.1 by gm (created)

#ifndef SOLIDBRICK_H
#define SOLIDBRICK_H

#include "cell.h"

namespace cell
{
    class Solid : public Cell
    {
    public:
        Solid (int x, int y);
        virtual ~Solid ();

//         virtual EnumBlocks class_id() const;

        virtual void draw();

        virtual bool solid() const;
    };
}

#endif // SOLIDBRICK_H
