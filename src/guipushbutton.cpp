/**
 * file: pushbutton.cpp
 *
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "guipushbutton.h"

#include "globals.h"
#include "render.h"

namespace gui
{

    PushButton::PushButton()
        : Button()
    {
        set_caption("");
    }

    PushButton::PushButton(string cap)
        : Button()
    {
        set_caption(cap);
    }

    PushButton::~PushButton()
    {
    }

    void PushButton::click()
    {
        Button::click();

        // emit signal
        on_clicked.emit();
    }

    void PushButton::draw()
    {
        draw_border();
        
        Globals g;

        g.render().SetTextSizes(m_font_size_w, m_font_size_h);

        switch (text_alignment())
        {
            case TAL_LEFT:
            {
                g.render().DrawText(m_x +15 , m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, caption());
                break;
            }

            case TAL_CENTER:
            {
                g.render().DrawText(wnd_size(), 1, 1, 1, caption());
                break;
            }

            case TAL_RIGHT:
            {
                g.render().DrawText(m_x + m_w - g.render().TextWidth(caption()) - 15, m_y + m_h/2 - m_font_size_h/2, 1, 1, 1, caption());
                break;
            }
        }
    }

}
