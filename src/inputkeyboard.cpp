// v0.1  by gm (created)
// v0.11 by gm (development phase)
// v0.2  by gm (minor changes, release-candidate)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "inputkeyboard.h"
#include "globals.h"
#include "keyconfig.h"
#include "enumkeys.h"
#include <iostream>

namespace input
{
    using namespace std;

    Keyboard::Keyboard(int keyset)
        : m_keyset(keyset)
    {
        if (m_keyset < 0 || m_keyset > 1)
            cerr << "Keyboard::Keyboard(int keyset): 'keyset' out of range: " << keyset << endl;
    }

    Keyboard::~Keyboard()
    {
    }

    void
    Keyboard::update_keyboard(UINT keysym, bool bDown)
    {
        update_key(KEY_UP, keysym, bDown);
        update_key(KEY_LEFT, keysym, bDown);
        update_key(KEY_DOWN, keysym, bDown);
        update_key(KEY_RIGHT, keysym, bDown);
        update_key(KEY_BOMB, keysym, bDown);
        update_key(KEY_SPECIAL, keysym, bDown);
    }

    void
    Keyboard::update_key (EnumPlayerKeys key, UINT keysym, bool bDown)
    {
        if (Globals::keycfg().player_keys(m_keyset).key(key) == keysym)
        {
            if (bDown)
                key_down(key);
            else
                key_up(key);
        }
    }
}
