/**
 * soundlist.cpp - SEE soundlist.h FOR MORE INFORMATION
 */
#include "soundlist.h"
#include "listreader.h"
#include "globals.h"
#include "mainconfig.h"

#include <iostream>
#include <time.h>

typedef vector < string > StringVector;

SoundList::SoundList ()
{
    /**
     * first randomize
     */
    srand(time(NULL));

    /**
     * create sound maps / vectors...
     */
    create();
 }

SoundList::~SoundList ()
{
}

/**
 * reads the file soundlist.res with the help of the
 * class ListReader and creates a map-vector-array
 * in which all sounds are registered.
 */
void SoundList::create()
{
    string sp; // sp = sound_path
    string sl; // sl = sound_list

    sp = "";
    sl = Globals::maincfg().get(MC_SOUND_LIST); // sl: path and file!

    ListReader lr;


    StringVector keyStrings;
    keyStrings.resize(SND_NUMBER_OF);

    int cnt = 0;
    keyStrings[cnt++] = "SND_MENU_EXIT";
    keyStrings[cnt++] = "SND_MENU_MOVE";
    keyStrings[cnt++] = "SND_NOT_ALLOWED";
    keyStrings[cnt++] = "SND_BOMB_DROP";
    keyStrings[cnt++] = "SND_BOMB_KICK";
    keyStrings[cnt++] = "SND_BOMB_STOP";
    keyStrings[cnt++] = "SND_BOMB_PUNCH";
    keyStrings[cnt++] = "SND_BOMB_BOUNCING";
    keyStrings[cnt++] = "SND_BOMB_GRAB";
    keyStrings[cnt++] = "SND_BOMB_EXPLOSION";
    keyStrings[cnt++] = "SND_BOMB_HIT";
    keyStrings[cnt++] = "SND_JELLY_BOUNCING";
    keyStrings[cnt++] = "SND_HURRY_BRICK";
    keyStrings[cnt++] = "SND_DIE";
    keyStrings[cnt++] = "SND_MATCH_WIN";
    keyStrings[cnt++] = "SND_BURNEDUP";
    keyStrings[cnt++] = "SND_TRAMPOLINE";
    keyStrings[cnt++] = "SND_POWERUP";
    keyStrings[cnt++] = "SND_POWERUP_MANY";
    keyStrings[cnt++] = "SND_POOP";
    keyStrings[cnt++] = "SND_DEATH_TAUNT";
    keyStrings[cnt++] = "SND_MUSIC_TITLE";
    keyStrings[cnt++] = "SND_MUSIC_MENU_MAIN";
    keyStrings[cnt++] = "SND_MUSIC_MENU_INPUT";
    keyStrings[cnt++] = "SND_MUSIC_GAME_OVER";
    keyStrings[cnt++] = "SND_MUSIC_MENU_NETWORK";
    keyStrings[cnt++] = "SND_BACKGROUND_MUSIC";
    keyStrings[cnt++] = "SND_MUSIC_ENDOFGAME";
    keyStrings[cnt++] = "SND_ON_MANY_BOMBS";
    keyStrings[cnt++] = "SND_ROULETTE_TICK";
    keyStrings[cnt++] = "SND_HANDS_CLAPPING";
    keyStrings[cnt++] = "SND_BUZZER";
    keyStrings[cnt++] = "SND_WARP_HOLE";
    keyStrings[cnt++] = "SND_DRAW_GAME";
    keyStrings[cnt++] = "SND_YOU_WIN";
    keyStrings[cnt++] = "SND_DISEASE";
    keyStrings[cnt++] = "SND_GAME_EXIT";
    keyStrings[cnt++] = "SND_HURRY";
    keyStrings[cnt++] = "SND_TITLE_INTRO";
    keyStrings[cnt++] = "SND_DISEASE_MOLASSES";
    keyStrings[cnt++] = "SND_DISEASE_CRACK";
    keyStrings[cnt++] = "SND_DISEASE_CONSTIPATION";
    keyStrings[cnt++] = "SND_DISEASE_POOPS";
    keyStrings[cnt++] = "SND_DISEASE_SHORTFLAME";
    keyStrings[cnt++] = "SND_DISEASE_CRACKPOOPS";
    keyStrings[cnt++] = "SND_DISEASE_SHORTFUZE";
    keyStrings[cnt++] = "SND_DISEASE_SWAP";
    keyStrings[cnt++] = "SND_DISEASE_REVERSED";
    keyStrings[cnt++] = "SND_DISEASE_LEPROSY";
    keyStrings[cnt++] = "SND_DISEASE_INVISIBLE";
    keyStrings[cnt++] = "SND_DISEASE_DUDS";


    m_sound_list.resize(SND_NUMBER_OF);

    for (int i = 0; i < SND_NUMBER_OF; ++i)
    {
        m_sound_list[i] = lr.get(sp, sl, keyStrings[i]);
    }


    /**
     * and finally create the random_list from the complete list
     */
    random();
}

/**
 * return: a sound from type "type"...
 */
string SoundList::get_random_sound(EnumSounds type) const
{
    const vector < string >& list = m_random_list[type];

    if ( list.size() > 0 )
    {
        return Globals::maincfg().get(MC_SOUND_PATH) + (list[ rand() % list.size() ]);
    }
    else
    {
        cerr << "Error: SoundList: random sound array emty: m_random_list.size() == 0; EnumSounds-type: " << type << endl;
        return string("error");
    }
}

void SoundList::random()
{
    m_random_list = m_sound_list;

    /**
     * clip here! (TODO)
     */
    // example: clip_random_list(SND_DEATH_TAUNT, 10);
    clip_random_list(SND_MUSIC_TITLE, 1);
    clip_random_list(SND_MUSIC_MENU_MAIN, 1);
}

/**
 * return a const referenced string-vector of the random_list that the user
 * can use it in a for-loop (here: that we can load all
 * sounds before the game starts and NOT during the gameplay)
 */
const vector < string >& SoundList::get_string_vector(EnumSounds type) const
{
    return m_random_list[type];
}

/**
 * example: there are about 40 SND_DEATH_TAUNT sounds. But during
 * one game we only want to have 10 sounds that will be played.
 * Then use: abbreviate_random_list(SND_DEATH_TAUNT, 10);
 */
void SoundList::clip_random_list (EnumSounds type, unsigned int max_count_of_sounds)
{
    int i;

    vector < string >::iterator it;

    while (m_random_list[type].size() > max_count_of_sounds)
    {
        i = rand() % m_random_list[type].size();

        it = m_random_list[type].begin();
        it += i;

        m_random_list[type].erase(it);
    }
}
