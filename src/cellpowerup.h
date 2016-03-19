// v0.1 by gm (created)

#ifndef POWERUP_H
#define POWERUP_H

// todo: VIEL

#include "cell.h"
#include "enumpowerups.h"

namespace cell
{
    class Powerup : public Cell
    {
    public:
        Powerup (int x, int y, EnumPowerups type, bool bInBrick = false);
        virtual ~Powerup ();

        virtual void draw();

        virtual bool solid() const;

        EnumPowerups type() const;

    private:
        /**
         * what type of powerup
         * if type == PU_DISEASE: disease type will be determined when a player gets one
         */
        EnumPowerups m_type;

        /**
         * true if VAL_SHOW_POWERUPS_IN_BRICKS is true
         */
        bool m_bInBrick;
    };
}

#endif // POWERUP_H
