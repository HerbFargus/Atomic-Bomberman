/**
 * classname / filename: SoundList / soundlist.h
 * Author: Dominik Haumann
 *
 * version: 0.55
 * history: 0.1 - 0.5 dh, 0.51 gm (adjusted to other class changes)
 * history: 0.52 by gm (replaced map by vector)
 * history: 0.55 changed a function, added 2 clip-lines in random()
 */

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef SOUNDLIST_H
#define SOUNDLIST_H

/**
 * TODO: fill the clip-list
 * DONE:
 *  - read soundlist.res
 *  - return const vector of one sound-type (of random_list and/or sound_list)
 *  - fill m_random_list-array for current game play
 */


enum EnumSounds {
    SND_MENU_EXIT = 0,      // exit a menu
    SND_MENU_MOVE,          // cursor movement
    SND_NOT_ALLOWED,        // some kind of "you can't do that here" sound
    SND_BOMB_DROP,          // dropping a bomb
    SND_BOMB_KICK,          // kicking a bomb
    SND_BOMB_STOP,          // stopping a bomb
    SND_BOMB_PUNCH,         // punching a bomb
    SND_BOMB_BOUNCING,      // a punched/grabbed bomb bouncing along
    SND_BOMB_GRAB,          // when you grab a bomb
    SND_BOMB_EXPLOSION,     // bomb explosion
    SND_BOMB_HIT,           // you are stunned by a bomb landing on your head
    SND_JELLY_BOUNCING,     // jelly bomb bouncing
    SND_HURRY_BRICK,        // a solid tile slamming in place
    SND_DIE,                // dying
    SND_MATCH_WIN,          // we have a winner of the match
    SND_BURNEDUP,           // todo: something with a death animation
    SND_TRAMPOLINE,         // step on a trampoline
    SND_POWERUP,            // you get a powerup (a good one)
    SND_POWERUP_MANY,       // you are now AWESOME (7th powerup and 3rd thereafter ???)
    SND_POOP,               // poop sounds
    SND_DEATH_TAUNT,        // after a player death
    SND_MUSIC_TITLE,        //
    SND_MUSIC_MENU_MAIN,    //
    SND_MUSIC_MENU_INPUT,   //
    SND_MUSIC_GAME_OVER,    // ??? nie gehoert
    SND_MUSIC_MENU_NETWORK, 
    SND_BACKGROUND_MUSIC,   // music for actual game play
    SND_MUSIC_ENDOFGAME,    // display results, draw game, victory
    SND_ON_MANY_BOMBS,      // after laying out a HUGE string of bombs
    SND_ROULETTE_TICK,      // periodic roulette "tick" sound
    SND_HANDS_CLAPPING,     // clapping people, happy sound
    SND_BUZZER,             // buzzer sound, you got the molasses roulette powerup (powerdown)
    SND_WARP_HOLE,          // a warp-hole transfer sound
    SND_DRAW_GAME,          // draw game
    SND_YOU_WIN,            // the "we have a winner" sounds
    SND_DISEASE,            // generic (non-specific) disease sound
    SND_GAME_EXIT,          // exiting game (go outside and play now!)
    SND_HURRY,              // plays when "hurry" flashes across the screen.
    SND_TITLE_INTRO,        // title intro statement "ATOMIC BOMBERMAN!"
    SND_DISEASE_MOLASSES,    // disease sounds...
    SND_DISEASE_CRACK,
    SND_DISEASE_CONSTIPATION,
    SND_DISEASE_POOPS,
    SND_DISEASE_SHORTFLAME,
    SND_DISEASE_CRACKPOOPS,
    SND_DISEASE_SHORTFUZE,
    SND_DISEASE_SWAP,
    SND_DISEASE_REVERSED,
    SND_DISEASE_LEPROSY,
    SND_DISEASE_INVISIBLE,
    SND_DISEASE_DUDS,
//--------------------------
    SND_NUMBER_OF
};

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <vector>
#include <string>
using namespace std;

/**
 * SoundList
 */
class SoundList
{ 
public:
    /**
     * constructor calls create()
     */
    SoundList ();
    virtual ~SoundList ();

    /**
     * returns a sound from the requestet type
     */
    string get_random_sound(EnumSounds type) const;
    
    /**
     * creates a new random_list - table
     */
    void random();

    /**
     * return a const referenced string-vector of the random_list that the user
     * can use it in a for-loop (here: that we can load all
     * sounds before the game starts and NOT during the gameplay)
     */
    const vector < string >& get_string_vector(EnumSounds type) const;

protected: // functions

    /**
     * reads the file soundlist.res with the help of the
     * class ListReader and creates a map-vector-array
     * in which all sounds are registered.
     */
    void create();

    /**
     * example: there are about 40 SND_DEATH_TAUNT sounds. But during
     * one game we only want to have 10 sounds that will be played.
     * Then use: abbreviate_random_list(SND_DEATH_TAUNT, 10);
     */
    void clip_random_list(EnumSounds type, unsigned int max_count_of_sounds);

protected: // variables

    /**
     * m_sound_list:  contains all sound-types and sound-filenames
     * m_random_list: contains all sound-types and sound-filenames
     *                which will be used in the current game
     */
    vector < vector <string> > m_sound_list;
    mutable vector < vector <string> > m_random_list;

    /**
     *
     */
    string m_soundpath;

};

#endif // SOUNDLIST_H
