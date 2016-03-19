/*************************************************
 *
 * class Sound -- header file: h
 *
 * Autor: Dominik Haumann
 * Datum: 2002/07/27 - 2003/05/11
 * Version: 2.0
 *
 *************************************************/

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/


#ifndef SOUND_H
#define SOUND_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

/**
 * I use the stl
 */
#include <vector>
#include <string>
#include <map>
using namespace std;

#include <SDL/SDL.h>
#include <SDL/SDL_sound.h>

/**
 * class SndInfo
 * need: SndPlayInfos
 */
class SndInfo
{
public: // classes

    /**
     * struct SndPlayInfos
     * position: position in the snd_data
     * loop: if true: sound will be looped
     */
    class SndPlayInfos
    {
        public:
            /**
             * contaings the current position in the sound-buffer
             */
            Uint32   position;

            /**
             * if true the sound will be looped
             */
            bool     loop;
    };


public: // variables
    /**
     * the sound's id
     */
    unsigned int snd_id;

    /**
     * length in seconds
     */
    double length_in_ms;

    /**
     *size in byte
     */
    Uint32 length_in_bytes;

    /**
     * the file_name in which the sound is saved
     */
    string file_name;

    /**
     * use SDL_sound functions to load and unload samples
	 * contains: ->sample: raw PCM sample data
	 *           ->
     */
    Sound_Sample *sound;

    /**
     * if true: loop
     */
    bool loop;

    /**
     * current positions in the sound-buffer including loop[true|false]. vector, so it is possible to play the sound as many times as you wish
     */
    vector <SndPlayInfos> positions;
};


/**
 * class: Sound
 * uses: SndInfo
 */
class Sound
{
public: // user functions

    /**
     * constructor (is empty)
     */
    Sound();

    /**
     * destructor frees the sound data and shot down the audio sub system cleanly
     */
    ~Sound();

    /**
     * some necessary audio initializations
     * freq: the desired frequency
     * stereo: stereo or mono sound
     */
    bool init(int freq = 44100, bool stereo = true);

    /**
     * the user has to load a sound and retreives a SndInfo with which he is able to play the sound
     * If SndInfo is NULL the loading failed!
     */
    const SndInfo* load(const string& file_name);

    /**
     * the user can play a sound...
     */
    void play(const SndInfo* info, bool loop = false);

    /**
     * load and play a sound
     */
    const SndInfo* play(const string& file_name, bool loop = false);

    /**
     * the user can stop a sound
     */
    void stop(const SndInfo* info);

    /**
     * unload sound to free memory.
     * unloads a sound and frees allocated memory. (mostly needed for old PCs)
     */
    void unload(const SndInfo* info);

    /**
     * check whether a sound is active
     */
    bool is_running(const SndInfo* info);

public: // static "globals"

    /**
     * container-array for all sounds.
     * (static because it is used by AudioCallback)
     */
    static vector <SndInfo*> snd_container;

    /**
     * is called from the sound-card
     * the first value (is user_data) is not needed
     */
    static void AudioCallback(void*, Uint8 *audio, int length);


private: // intern functions

    /**
     * frees all sound data
     */
    void free_sound_data();

    /**
     * frees the container array
     */
    void free_array();

    /**
     * load file and convert sample data;
     * used by load_sound
     */
    bool load_and_convert_sound(SndInfo* info);

    /**
     * return the SndInfo-class which has the id id.
     */
    inline SndInfo* info_from_id(unsigned int id) const;


private: // member variables

    /**
     * if the Audio sub system was not initialized: true
     */
    bool b_init_audio_sub_system;

    /**
     * "saves" the number of used ids
     */
    unsigned int m_free_id;

    /**
     * the desired format
     */
    SDL_AudioSpec m_desired;

    /**
     * the real format we will use
     */
    SDL_AudioSpec m_obtained;

    /**
     * m_map_sound_table is a table that returns the SndInfo* by its id
     * (It is very fast!)
     */
    mutable map < unsigned int, SndInfo* > m_map_sound_table;

    /**
     * m_map_filename_table is a table that returns the SndInfo* by its filename
     * (It is very fast!)
     */
    map < string, SndInfo* > m_map_filename_table;
};

#endif // SDL_SND_H
