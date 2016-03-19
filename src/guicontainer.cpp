/**
 * file: container.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "guicontainer.h"

#include <SDL/SDL_keysym.h>

namespace gui
{

    Container::Container()
        : p_last_focused_wnd(0), m_autodelete(false)
    {
    }

    Container::~Container()
    {
        if (m_wnds.size() > 0)
            clear();
    }

    // add a from Base derived control
    void Container::add(Base* pWnd)
    {
        m_wnds.push_back(pWnd);
        
        if (p_last_focused_wnd == 0)
            p_last_focused_wnd = pWnd;
    }

    // creates the tab-order using the order from the vector
    void Container::create_tab_order()
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            if (i < m_wnds.size() - 1)
            {
                m_wnds[i]->set_next_focus(m_wnds[i+1]);
            }
            else
            {
                m_wnds[i]->set_next_focus(m_wnds[0]);
            }
        }
    }
    
    void Container::tab_backward()
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            if (m_wnds[i]->has_focus())
            {
                m_wnds[i]->set_focus(false);
                if (i > 0)
                {
                    m_wnds[i-1]->set_focus(true);
                }
                else
                {
                    m_wnds[m_wnds.size()-1]->set_focus(true);
                }
                break;
            }
        }

        update_last_focused_wnd();
        restore_focus();
    }

    void Container::set_autodelete(bool autodel)
    {
        m_autodelete = autodel;
    }


    int Container::current_focused()
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            if (m_wnds[i]->has_focus())
                return i;
        }

        return -1;
    }

    // gives the key events to all controls
    void Container::on_key_down (UINT keysym)
    {
        if (keysym == SDLK_TAB)
        {
            // SDLK_TAB is a special case
            for (UINT i = 0; i < m_wnds.size(); ++i)
            {
                if (m_wnds[i]->has_focus())
                {
                    m_wnds[i]->on_key_down(keysym);
                    break;
                }
            }
        }
        else
        {
            for (UINT i = 0; i < m_wnds.size(); ++i)
            {
                m_wnds[i]->on_key_down(keysym);
            }
        }

        update_last_focused_wnd();
        restore_focus();
    }

    void Container::on_key_up (UINT keysym)
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            m_wnds[i]->on_key_up(keysym);
        }
    }

    // gives the mouse events to all controls 
    void Container::on_mouse_down (int x, int y)
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            m_wnds[i]->on_mouse_down(x, y);
        }

        update_last_focused_wnd();
        restore_focus();
    }

    void Container::on_mouse_up (int x, int y)
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            m_wnds[i]->on_mouse_up(x, y);
        }
    }

    void Container::on_mouse_move (int x, int y)
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            m_wnds[i]->on_mouse_move(x, y);
        }
    }

    void Container::draw_all()
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            m_wnds[i]->draw();
        }
    }

    void Container::clear()
    {
        if (m_autodelete)
        {
            for (UINT i = 0; i < m_wnds.size(); ++i)
            {
                delete m_wnds[i]; 
            }
        }

        m_wnds.clear();
        p_last_focused_wnd = 0;
    }

    /*************************************
     * P R O T E C T E D   M E M B E R S *
     *************************************/

    void Container::restore_focus()
    {
        // if a wnd has the focus leave this function
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            if (m_wnds[i]->has_focus())
                return;
        }

        // oops: no wnd has the focus --> restore
        if (p_last_focused_wnd)
            p_last_focused_wnd->set_focus(true);
    }

    void Container::update_last_focused_wnd()
    {
        for (UINT i = 0; i < m_wnds.size(); ++i)
        {
            if (m_wnds[i]->has_focus())
            {
                p_last_focused_wnd = m_wnds[i];
                break;
            }
        }
    }
}
