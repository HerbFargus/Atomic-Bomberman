// v0.1 by gm (created)

#ifndef STATEDISPLAYGAMERESULTS_H
#define STATEDISPLAYGAMERESULTS_H

#include "state.h"

/**
 * Some hints to implement this state:
 *
 * Globals g;
 * g.game().round();                     // number of the round
 * g.game().win_value();                 // wins / kill to win the match
 * g.game().win_on_match_wins();         // true: wins, false: kills
 *
 * Player& p = g.game().player(0..10);   // get player info
 * p.active();             // is active
 * p.wins();               // number of wins
 * p.kills();              // number of kills
 */

namespace state
{
    class DisplayGameResults : public State
    {
    public:
        DisplayGameResults ();
        virtual ~DisplayGameResults ();
    };

}

#endif // STATEDISPLAYGAMERESULTS_H
