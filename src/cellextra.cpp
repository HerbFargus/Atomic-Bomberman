// v0.1 by gm (created)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "cellextra.h"

namespace cell
{
    Extra::Extra(int x, int y)
        : Cell(x, y)
    {
    }

    Extra::~Extra()
    {
    }

//     EnumBlocks Extra::class_id() const
//     {
//         return BLOCK_EXTRA;
//     }

    void
    Extra::draw()
    {

    }

    bool
    Extra::solid() const
    {
        return true;
    }
}
