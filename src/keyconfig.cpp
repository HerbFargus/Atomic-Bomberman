// v0.2  by gm (created)
// v0.21 by gm (debug_key_name added, more menu keys)
// v0.22 by gm (key enum changed --> keys.cfg changed)
// v0.25 by gm (write_to_file, removed menu keys, save only if data was changed)

#include "keyconfig.h"
#include <SDL/SDL_keysym.h>
#include "globals.h"
#include "mainconfig.h"
#include "nameddatafile.h"

#include <iostream>
using namespace std;

KeyConfig::PlayerKeys::PlayerKeys ()
{

}

KeyConfig::PlayerKeys::~PlayerKeys ()
{

}

UINT
KeyConfig::PlayerKeys::key(EnumPlayerKeys which) const
{
    return m_keys[which];
}

void
KeyConfig::PlayerKeys::set_key(EnumPlayerKeys which, UINT key)
{
    m_keys[which] = key;
}

//--------------------------------------------------------------------------------

KeyConfig::KeyConfig ()
{
    NamedDataFile ndf (Globals::maincfg().get(MC_KEY_CONFIG));
    ndf.load();

//     set_key(KEY_MENU_UP,     ndf.get("menu_up"    ));
//     set_key(KEY_MENU_LEFT,   ndf.get("menu_left"  ));
//     set_key(KEY_MENU_DOWN,   ndf.get("menu_down"  ));
//     set_key(KEY_MENU_RIGHT,  ndf.get("menu_right" ));
//     set_key(KEY_SCROLL_UP,   ndf.get("scroll_up"  ));
//     set_key(KEY_SCROLL_DOWN, ndf.get("scroll_down"));
//     set_key(KEY_MENU_HOME,   ndf.get("menu_home"  ));
//     set_key(KEY_MENU_END,    ndf.get("menu_end"   ));
//     set_key(KEY_MENU_OK,     ndf.get("menu_ok"    ));
//     set_key(KEY_MENU_CANCEL, ndf.get("menu_cancel"));
    set_key(KEY_GAME_PAUSE,  ndf.get("game_pause" ));
    set_key(KEY_GAME_ABORT,  ndf.get("game_abort" ));

    player_keys_change(0).set_key(KEY_UP     , ndf.get("p0_up"     ));
    player_keys_change(0).set_key(KEY_LEFT   , ndf.get("p0_left"   ));
    player_keys_change(0).set_key(KEY_DOWN   , ndf.get("p0_down"   ));
    player_keys_change(0).set_key(KEY_RIGHT  , ndf.get("p0_right"  ));
    player_keys_change(0).set_key(KEY_BOMB   , ndf.get("p0_bomb"   ));
    player_keys_change(0).set_key(KEY_SPECIAL, ndf.get("p0_special"));

    player_keys_change(1).set_key(KEY_UP     , ndf.get("p1_up"     ));
    player_keys_change(1).set_key(KEY_LEFT   , ndf.get("p1_left"   ));
    player_keys_change(1).set_key(KEY_DOWN   , ndf.get("p1_down"   ));
    player_keys_change(1).set_key(KEY_RIGHT  , ndf.get("p1_right"  ));
    player_keys_change(1).set_key(KEY_BOMB   , ndf.get("p1_bomb"   ));
    player_keys_change(1).set_key(KEY_SPECIAL, ndf.get("p1_special"));

    m_bSaveOnExit = false;
}

KeyConfig::~KeyConfig ()
{
    if (m_bSaveOnExit)
    {
        write_to_file();
    }
}

UINT
KeyConfig::key(EnumKeys which)
{
    return m_keys[which];
}

void
KeyConfig::set_key(EnumKeys which, UINT key)
{
    m_bSaveOnExit = true;
    m_keys[which] = key;
}

const KeyConfig::PlayerKeys&
KeyConfig::player_keys(int keyset) const
{
    return m_playerkeys[keyset];
}

KeyConfig::PlayerKeys&
KeyConfig::player_keys_change(int keyset)
{
    m_bSaveOnExit = true;
    return m_playerkeys[keyset];
}

void
KeyConfig::write_to_file()
{
    NamedDataFile ndf (Globals::maincfg().get(MC_KEY_CONFIG));
    ndf.load(); // to preserve commentary entries

//     ndf.set("menu_up"    , key(KEY_MENU_UP)    );
//     ndf.set("menu_left"  , key(KEY_MENU_LEFT)  );
//     ndf.set("menu_down"  , key(KEY_MENU_DOWN)  );
//     ndf.set("menu_right" , key(KEY_MENU_RIGHT) );
//     ndf.set("scroll_up"  , key(KEY_SCROLL_UP)  );
//     ndf.set("scroll_down", key(KEY_SCROLL_DOWN));
//     ndf.set("menu_home"  , key(KEY_MENU_HOME)  );
//     ndf.set("menu_end"   , key(KEY_MENU_END)   );
//     ndf.set("menu_ok"    , key(KEY_MENU_OK)    );
//     ndf.set("menu_cancel", key(KEY_MENU_CANCEL));
    ndf.set("game_pause" , key(KEY_GAME_PAUSE) );
    ndf.set("game_abort" , key(KEY_GAME_ABORT) );

    ndf.set("p0_up"     , player_keys(0).key(KEY_UP     ));
    ndf.set("p0_left"   , player_keys(0).key(KEY_LEFT   ));
    ndf.set("p0_down"   , player_keys(0).key(KEY_DOWN   ));
    ndf.set("p0_right"  , player_keys(0).key(KEY_RIGHT  ));
    ndf.set("p0_bomb"   , player_keys(0).key(KEY_BOMB   ));
    ndf.set("p0_special", player_keys(0).key(KEY_SPECIAL));

    ndf.set("p1_up"     , player_keys(1).key(KEY_UP     ));
    ndf.set("p1_left"   , player_keys(1).key(KEY_LEFT   ));
    ndf.set("p1_down"   , player_keys(1).key(KEY_DOWN   ));
    ndf.set("p1_right"  , player_keys(1).key(KEY_RIGHT  ));
    ndf.set("p1_bomb"   , player_keys(1).key(KEY_BOMB   ));
    ndf.set("p1_special", player_keys(1).key(KEY_SPECIAL));

    ndf.save();

    m_bSaveOnExit = false;
}

void
KeyConfig::debug_print_keyname (UINT keysym)
{
//     if (keysym == key(KEY_MENU_UP    )) cout << "keysym " << keysym << ": " << "KEY_MENU_UP"    ;
//     if (keysym == key(KEY_MENU_LEFT  )) cout << "keysym " << keysym << ": " << "KEY_MENU_LEFT"  ;
//     if (keysym == key(KEY_MENU_DOWN  )) cout << "keysym " << keysym << ": " << "KEY_MENU_DOWN"  ;
//     if (keysym == key(KEY_MENU_RIGHT )) cout << "keysym " << keysym << ": " << "KEY_MENU_RIGHT" ;
//     if (keysym == key(KEY_SCROLL_UP  )) cout << "keysym " << keysym << ": " << "KEY_SCROLL_UP"  ;
//     if (keysym == key(KEY_SCROLL_DOWN)) cout << "keysym " << keysym << ": " << "KEY_SCROLL_DOWN";
//     if (keysym == key(KEY_MENU_HOME  )) cout << "keysym " << keysym << ": " << "KEY_MENU_HOME"  ;
//     if (keysym == key(KEY_MENU_END   )) cout << "keysym " << keysym << ": " << "KEY_MENU_END"   ;
//     if (keysym == key(KEY_MENU_OK    )) cout << "keysym " << keysym << ": " << "KEY_MENU_OK"    ;
//     if (keysym == key(KEY_MENU_CANCEL)) cout << "keysym " << keysym << ": " << "KEY_MENU_CANCEL";
    if (keysym == key(KEY_GAME_PAUSE )) cout << "keysym " << keysym << ": " << "KEY_GAME_PAUSE" ;
    if (keysym == key(KEY_GAME_ABORT )) cout << "keysym " << keysym << ": " << "KEY_GAME_ABORT" ;

    cout << " - ";

    if (keysym == player_keys(0).key(KEY_UP     )) cout << "keysym " << keysym << ": keyset0: " << "KEY_UP"     ;
    if (keysym == player_keys(0).key(KEY_LEFT   )) cout << "keysym " << keysym << ": keyset0: " << "KEY_LEFT"   ;
    if (keysym == player_keys(0).key(KEY_DOWN   )) cout << "keysym " << keysym << ": keyset0: " << "KEY_DOWN"   ;
    if (keysym == player_keys(0).key(KEY_RIGHT  )) cout << "keysym " << keysym << ": keyset0: " << "KEY_RIGHT"  ;
    if (keysym == player_keys(0).key(KEY_BOMB   )) cout << "keysym " << keysym << ": keyset0: " << "KEY_BOMB"   ;
    if (keysym == player_keys(0).key(KEY_SPECIAL)) cout << "keysym " << keysym << ": keyset0: " << "KEY_SPECIAL";

    if (keysym == player_keys(1).key(KEY_UP     )) cout << "keysym " << keysym << ": keyset1: " << "KEY_UP"     ;
    if (keysym == player_keys(1).key(KEY_LEFT   )) cout << "keysym " << keysym << ": keyset1: " << "KEY_LEFT"   ;
    if (keysym == player_keys(1).key(KEY_DOWN   )) cout << "keysym " << keysym << ": keyset1: " << "KEY_DOWN"   ;
    if (keysym == player_keys(1).key(KEY_RIGHT  )) cout << "keysym " << keysym << ": keyset1: " << "KEY_RIGHT"  ;
    if (keysym == player_keys(1).key(KEY_BOMB   )) cout << "keysym " << keysym << ": keyset1: " << "KEY_BOMB"   ;
    if (keysym == player_keys(1).key(KEY_SPECIAL)) cout << "keysym " << keysym << ": keyset1: " << "KEY_SPECIAL";

    cout << endl;
}
