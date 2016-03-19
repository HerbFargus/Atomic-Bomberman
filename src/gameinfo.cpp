// v0.1  by gm (created)
// v0.11 by gm (development phase)
// v0.2  by gm (core functionality added)
// v0.21 by gm (windows compability)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include "gameinfo.h"
#include "player.h"
#include "scheme.h"
#include "fieldextras.h"
#include "globals.h"
#include "valuelist.h"
#include <iostream>
using namespace std;

GameInfo::GameInfo()
{
    init();
}

GameInfo::~GameInfo()
{
    delete m_pScheme;
    delete m_pExtras;

    for (int i = 0; i < Globals::values().max_players(); ++i)            // (TODO: algorithm) ???
    {
        delete m_players[i];
    }
}

void
GameInfo::init()
{
    m_nWinValue = 0;
    m_bWinOnWins = 0;

    m_pScheme = 0;
    m_pExtras = 0;

    m_nMap = 0;

    int max_players = Globals::values().max_players();
    m_players.resize(max_players);

    for (int i = 0; i < max_players; ++i)
    {
         m_players[i] = new Player(i);
    }

    m_pField = 0;
}

void
GameInfo::set_new_match(string scheme_filename, string extra_filename, int map, int win_value, bool win_on_round_wins)
{
    delete m_pScheme;

    delete m_pExtras;

    m_pScheme = new Scheme();
    if (!m_pScheme->load_from_file(scheme_filename))
        cerr << "GameInfo::set_new_game(...): failed to load scheme file: '" << scheme_filename << "'" << endl;

    // TODO: Extras
    m_pExtras = new FieldExtras();
    extra_filename = "";   // wegen warning
//    m_pExtras

    if (map < 0 || map >= Globals::values().max_maps())
        cerr << "GameInfo::set_new_game(...): 'map' out of range: " << map << endl;

    m_nMap = map;

    if (win_value < 1)
        cerr << "GameInfo::set_new_game(...): 'win_value' out of range: " << win_value << endl;

    m_nWinValue = win_value;

    m_bWinOnWins = win_on_round_wins;

    m_nRound = 0;

    reset_round();
}

void
GameInfo::reset_round()
{
    if (!m_pScheme)
        cerr << "Error: GameInfo::reset_round(): m_pScheme == 0; possible reason: GameInfo::set_new_game(...) was not called" << endl;

    if (!m_pExtras)
        cerr << "Error: GameInfo::reset_round(): m_pExtras == 0; possible reason: GameInfo::set_new_game(...) was not called" << endl;

    for (int i = 0; i < Globals::values().max_players(); ++i)
    {
        if (m_players[i])
            m_players[i]->reset_round();
    }

    ++m_nRound;
}

int
GameInfo::round()
{
    return m_nRound;
}

Player&
GameInfo::player(int who)
{
    if (who < 0 || who >= Globals::values().max_players())
        cerr << "Error (by programer): GameInfo::player(int who): 'who' out of range: " << who << endl;

    return *m_players[who];
}

int
GameInfo::active_nondead_players()
{
    int cnt = 0;
    for (int i = 0; i < Globals::values().max_players(); ++i)
    {
        if (player(i).active() && !player(i).dead())
            ++cnt;
    }
    return cnt;
}

const Scheme&
GameInfo::scheme()
{
    return *m_pScheme;
}

const FieldExtras&
GameInfo::extras()
{
    return *m_pExtras;
}

int
GameInfo::map()
{
    return m_nMap;
}

int
GameInfo::win_value()
{
    return m_nWinValue;
}

bool
GameInfo::win_on_round_wins()
{
    return m_bWinOnWins;
}

void
GameInfo::set_field (const Field* pField)
{
    m_pField = pField;
}

const Field*
GameInfo::field() const
{
    if (!m_pField)
        cerr << "Possible error: GameInfo::field(): a field pointer was requested though it is 0." << endl;

    return m_pField;
}
