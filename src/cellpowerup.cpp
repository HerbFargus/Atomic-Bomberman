// v0.1 by gm (created)

#include "cellpowerup.h"
#include "globals.h"
#include "valuelist.h"

namespace cell
{
    Powerup::Powerup (int x, int y, EnumPowerups type, bool bInBrick)
        : Cell(x, y),
          m_type (type),
          m_bInBrick (bInBrick)
    {

    }

    Powerup::~Powerup ()
    {

    }

    EnumPowerups
    Powerup::type() const
    {
        return m_type;
    }

    void
    Powerup::draw()
    {
        Globals g;

        // TODO: draw gescheit!

        int w = g.values().cell_w();
        int h = g.values().cell_h();

        SDL_Rect r = {x() * w + w / 2, y() * h + h / 2, 2, 2};
        g.render().FillRect(r, 1.0, 0.0, 1.0);

        string text;

        switch (m_type)
        {
        case PU_BOMB:
            text = "PU_BOMB";
            break;

        case PU_FLAME:
            text = "PU_FLAME";
            break;

        case PU_DISEASE:
            text = "PU_DISEASE";
            break;

        case PU_ABILITY_KICK:
            text = "PU_ABILITY_KICK";
            break;

        case PU_EXTRA_SPEED:
            text = "PU_EXTRA_SPEED";
            break;

        case PU_ABLITY_PUNCH:
            text = "PU_ABLITY_PUNCH";
            break;

        case PU_ABILITY_GRAB:
            text = "PU_ABILITY_GRAB";
            break;

        case PU_SPOOGER:
            text = "PU_SPOOGER";
            break;

        case PU_GOLDFLAME:
            text = "PU_GOLDFLAME";
            break;

        case PU_TRIGGER:
            text = "PU_TRIGGER";
            break;

        case PU_JELLY:
            text = "PU_JELLY";
            break;

        case PU_EBOLA:
            text = "PU_EBOLA";
            break;

        case PU_RANDOM:
            text = "PU_RANDOM";
            break;

        case PU_NUMBER_OF:
            text = "!!!ERROR!!!";
            break;

        }

        if (m_bInBrick)
        {
            g.render().SetTextSizes(8, 8);
            g.render().DrawText(x() * w + 5, y() * h + 20, 1.0, 1.0, 1.0, text);
        }
        else
        {
            g.render().SetTextSizes(8, 8);
            g.render().DrawText(x() * w, y() * h, 1.0, 1.0, 1.0, text);
        }

    }

    bool
    Powerup::solid() const
    {
        return false;
    }

}
