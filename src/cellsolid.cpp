// v0.1 by gm (created)

#include "cellsolid.h"
#include "globals.h"
#include "gameinfo.h"
#include "valuelist.h"

namespace cell
{
    Solid::Solid (int x, int y)
        : Cell(x, y)
    {
        // TODO: testen
        anim().SetAnimation(ANI_TILE_SOLID, Globals::game().map());
    }

    Solid::~Solid ()
    {

    }

//     EnumBlocks Solid::class_id() const
//     {
//         return BLOCK_SOLID;
//     }

    void
    Solid::draw()
    {
        Globals g;
        int w = g.values().cell_w();
        int h = g.values().cell_h();

        anim().Draw(x() * w, y() * h, w, h);
    }

    bool
    Solid::solid() const
    {
        return true;
    }

}
