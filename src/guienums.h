#ifndef GUIENUMS_H
#define GUIENUMS_H

namespace gui
{
    enum TextAlignment {
        TAL_LEFT = 0,
        TAL_CENTER,
        TAL_RIGHT
    };

    enum CheckBoxAlignment {
        CBA_LEFT = 0,
        CBA_RIGHT
    
    };
    
    enum BorderType { 
         BT_ALWAYS = 0, // always draw border
         BT_FOCUS,      // draw when focused
         BT_MOUSE_OVER, // when wnd has focus OR mouse is over
         BT_NEVER       // never draw border
    };
}

#endif // GUIENUMS_H
