// v0.1 by gm (created)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "cellblank.h"

namespace cell
{
    Blank::Blank(int x, int y)
        : Cell(x, y)
    {
    }

    Blank::~Blank()
    {
    }

// EnumBlocks Blank::class_id() const
// {
//     return BLOCK_BLANK;
// }

    void
    Blank::draw()
    {

    }

    bool
    Blank::solid() const
    {
        return false;
    }

}
