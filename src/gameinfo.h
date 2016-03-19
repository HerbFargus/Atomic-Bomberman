// v0.1  by gm (created)
// v0.11 by gm (development phase)
// v0.2  by gm (core functionality added)
// v0.21 by gm (windows compability)

/**
 * Classname / filename: GameInfo / gameinfo.h
 * Author: g m
 * Version: 0.1
 */

/******************************************************************************
 * LICENSE: GPL v2 (General Public License v2)                                *
 ******************************************************************************/

#ifndef GAMEINFO_H
#define GAMEINFO_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <string>
#include <vector>
using namespace std;

class Scheme;
class Player;
class FieldExtras;
class Field;


/**
 * GameInfo:
 * stores information about the structure of the current game
 * like Scheme, Map, Extras, Players, win_value, ...
 * you can get an instance by looking in Globals
 */
class GameInfo
{
public:
    GameInfo();
    virtual ~GameInfo();

    /**
     * sets a new match (a match consists of serveral rounds), calls reset_round()
     * (after each round the results are displayed)
     * TODO: Extras
     */
    void set_new_match(string scheme_filename, string extra_filename, int map, int win_value, bool win_on_match_wins);

    /**
     * IMPORTANT! This function must NOT be called BEFORE a set_new_game(...) call!
     *
     * call this function to reset the game state (powerups of players) for a new round
     * (after StateGameResults was displayed)
     */
    void reset_round();

    /**
     * returns 1    if first round.
     * returns > 1  if more than one round.
     */
    int round();

    /**
     * returns a reference to the current scheme
     */
    const Scheme& scheme();

    /**
     * returns a reference to the current map extras
     */
    const FieldExtras& extras();

    /**
     * returns the number of the current map (0..MAX_MAPS)
     */
    int map();

    /**
     * who: 0..MAX_PLAYERS - 1
     * returns a reference to a Player instance
     */
    Player& player(int who);

    /**
     * returns the number of active and nondead players
     */
    int active_nondead_players();

    /**
     * returns the win value
     */
    int win_value();

    /**
     * returns true if the players wins the match by round wins
     * returns false if the players wins the by kills
     */
    bool win_on_round_wins();

    /**
     * call this right after a new field was allocated
     */
    void set_field (const Field* pField);

    /**
     * returns a pointer to a const Field object
     */
    const Field* field() const;

protected:
    void init();

private:
    int  m_nWinValue;
    bool m_bWinOnWins;

    int m_nRound;

    /**
     * dynamically allocated
     */
    Scheme* m_pScheme;
    FieldExtras* m_pExtras;

    int m_nMap;

    typedef vector < Player * > PPlayerVector;

    /**
     * pointers are dynamically allocated
     */
    PPlayerVector m_players;

    /**
     * a const pointer to the current field
     * may be 0
     * handle with care
     */
    const Field* m_pField;
};

#endif // GAMEINFO_H
