// v0.1 by gm (created)

#include "cell.h"

namespace cell
{
    Cell::Cell (int x, int y)
        : m_x(x), m_y(y)
    {
        m_bDeleteMe = false;
    }

    Cell::Cell (const Cell & rhs)
    {
        m_x = rhs.m_x;
        m_y = rhs.m_y;
        m_bDeleteMe = rhs.m_bDeleteMe;
        m_anim = rhs.m_anim;
    }

    Cell::~Cell ()
    {
    }

    int
    Cell::x()
    {
        return m_x;
    }

    int
    Cell::y()
    {
        return m_y;
    }

    bool
    Cell::to_be_deleted() const
    {
        return m_bDeleteMe;
    }

    Animation&
    Cell::anim()
    {
        return m_anim;
    }

    void
    Cell::delete_me()
    {
        m_bDeleteMe = true;
    }

    void
    Cell::set_x (int x)
    {
        m_x = x;
    }

    void
    Cell::set_y (int y)
    {
        m_y = y;
    }
}
