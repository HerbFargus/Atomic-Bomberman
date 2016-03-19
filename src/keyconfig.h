// v0.2  by gm (created)
// v0.21 by gm (debug_key_name added, more menu keys)
// v0.22 by gm (key enum changed --> keys.cfg changed)
// v0.25 by gm (write_to_file, removed menu keys, save only if data was changed)

#ifndef KEYCONFIG_H
#define KEYCONFIG_H

#include <string>
using namespace std;

#include "typedefs.h"

#include "enumkeys.h"

class KeyConfig
{
public:
    class PlayerKeys
    {
    public:
        PlayerKeys ();
        virtual ~PlayerKeys ();

        /**
         * returns a keysym
         */
        UINT key(EnumPlayerKeys which) const;

        /**
         * sets a keysym
         */
        void set_key(EnumPlayerKeys which, UINT key);

    protected:
        UINT m_keys[6];
    };

public:
    /**
     * loads the key config from file
     */
    KeyConfig ();

    /**
     * saves the key config to file
     */
    virtual ~KeyConfig ();

    /**
     * returns a non-player keysym (menu, ...)
     */
    UINT key(EnumKeys which);

    /**
     * sets a non-player keysym
     */
    void set_key(EnumKeys which, UINT key);

    /**
     * returns a PlayerKeys reference that allows access to the player's keys
     * keyset = 0..1 (keyset0 or keyset1)
     */
    const PlayerKeys& player_keys(int keyset) const;

    /**
     * use this function if you want to change a key binding
     */
    PlayerKeys& player_keys_change(int keyset);

    /**
     * writes config to file
     */
    void write_to_file();

    /**
     * prints the name of the Enum-Entry of a given keysym
     */
    void debug_print_keyname (UINT keysym);


private:
    UINT        m_keys[12];
    PlayerKeys  m_playerkeys[2];

    /**
     * true: keyconfig will be saved to file in the destructor
     */
    bool        m_bSaveOnExit;
};

#endif // KEYCONFIG_H
