// v0.1 by gm (created)
// v0.5 by gm (improved class design [removed class_id()])

#ifndef CELL_CELL_H
#define CELL_CELL_H

#include "animmng.h"
#include "enumblocks.h"

namespace cell
{
    class Cell
    {
    public:
        /**
         * x, y: logical field position
         */
        Cell (int x, int y);

        /**
         * copy ctor
         */
        Cell (const Cell & rhs);

        virtual ~Cell ();

        /**
         * true, if the object wants to be deleted
         */
        bool to_be_deleted() const;

        /**
         * draws the brick
         */
        virtual void draw() = 0;

        /**
         * true, if a player cannot enter the area through this block
         * else, false
         */
        virtual bool solid() const = 0;

        /**
         * returns the fieldpos (x, y)
         */
        int x();
        int y();


    protected:
        /**
         * call this in derived classes, if you want that the object will be deleted
         */
        void delete_me();

        /**
         * returns a non-const reference to the anim object of this cell
         */
        Animation& anim();

        void set_x (int x);
        void set_y (int y);

    private:
        /**
         * the (logical) x-, y-position on the field
         */
        int m_x;
        int m_y;

        /**
         * true: Field::process_field() will delete this brick
         */
        bool      m_bDeleteMe;

        /**
         * animation of the brick
         */
        Animation m_anim;
    };
}

#endif // CELL_CELL_H
