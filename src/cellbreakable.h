// v0.1 by gm (created)

#ifndef BREAKABLEBRICK_H
#define BREAKABLEBRICK_H

#include "cell.h"
#include "enumpowerups.h"

namespace cell
{
    class Breakable : public Cell
    {
    public:
        Breakable (int x, int y);
        virtual ~Breakable ();

        virtual void draw();

        virtual bool solid() const;

        /**
         * call this if a flame hits the block
         */
        void break_it();

        /**
         * assigns a powerup to this breakable brick
         */
        void set_powerup(EnumPowerups which);
        
        /**
         * returns true if the cell has a associated powerup
         */
        bool has_powerup() const;

        /**
         * returns the powerup id assigned to the cell
         */
        EnumPowerups powerup() const;

    private:
        bool m_bHasPowerup;
        EnumPowerups m_powerup;

        bool m_bBreak;

        /**
         * reference time value for 'how long should the destroy process last'
         */
        double m_start_time;


    };
}

#endif // BREAKABLEBRICK_H
