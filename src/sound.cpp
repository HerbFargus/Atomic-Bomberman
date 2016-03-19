/*************************************************
 *
 * class Sound -- source file: cpp
 * see header-file for more information
 *
 *************************************************/

#include "sound.h"

#include <iostream>
#include <algorithm>

/**
 * definition of static variable snd_container
 */
vector < SndInfo* > Sound::snd_container;

/**
 * constructor - emtpty: so it is possioble to have a global variable of this Sound
 */
Sound::Sound() {}

/**
 * destructor frees the sound data and shot down the audio sub system cleanly
 */
Sound::~Sound()
{
    /**
     * pause the audio before deleting the sample data
     */
    SDL_PauseAudio(1);

    /**
     * lock Audio, free sample data and unlock audio
     */
    SDL_LockAudio();
    free_sound_data();
    free_array();
    m_map_sound_table.clear();
    m_map_filename_table.clear();
    SDL_UnlockAudio();

	/**
	 * quit SDL_sound addon system
	 */
	Sound_Quit();

    /**
     * shut down the audio sub system cleanly
     */
//    cout << "SND: Shutting down audio sub system: OK" << endl;
    if (b_init_audio_sub_system == true)
    {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }

    SDL_CloseAudio();
}

/*---------------------------------------
 **  THE Audio-Callback-FUNCTION - called from the sound-card
 *--------------------------------------*/

/**
 * AudioCallback is called from the sound-card
 * the first value (is user_data) is not needed
 */
void Sound::AudioCallback(void*, Uint8 *audio, int length)
{
    /* user_data - the first parameter - is not needed */

    /**
     * Clear the audio buffer so we can mix samples into it.
     */
    memset(audio, 0, length);

    /**
     * Mix in each sound.
     */
    vector <SndInfo*>::iterator it;

    for (it = snd_container.begin(); it != snd_container.end(); ++it)
    {
        vector <SndInfo::SndPlayInfos>::iterator pos;

        for (pos = (*it)->positions.begin(); pos != (*it)->positions.end(); )
        {
            /**
             * position and sound variables for mixing
             */
            Uint8 *sound_buf;
            Uint32 sound_len;
            /**
             * extra data and position variables
             * needed, when the sound transition in loopmode happens
             */
            Uint8 *snd_loop_buf;
            Uint32 snd_loop_len;

            /**
             * Locate this sound's current buffer position.
             */
            sound_buf = static_cast<Uint8*>((*it)->sound->buffer);
            sound_buf += pos->position;

            /**
             * need extra handling when bTransition is true, that means in
             * loopmode a transition happens
             */
            bool bTransition = false;

            /**
             * Determine the number of samples to mix OR
             * handle loop
             */
            if ((pos->position + length) > (*it)->length_in_bytes)
            {
                /**
                 * calculate the difference between position and the end of the sample data
                 */
                sound_len = (*it)->length_in_bytes - pos->position;

                /**
                 * if loop is true: extra handling ;)
                 */
                if (pos->loop)
                {
                    bTransition = true;

                    /**
                     * the length of the difference between pos and end of sample data
                     */
                    snd_loop_len = sound_len;

                    /**
                     * allocate new sample data for the extra handling mixing bla...
                     */
                    snd_loop_buf = (Uint8 *) malloc(length);

                    /**
                     * copy the end of the original sample data
                     */
                    memcpy(snd_loop_buf, sound_buf, sound_len);
                    sound_buf = static_cast<Uint8*>((*it)->sound->buffer);

                    /**
                     * copy the beginning of the origional sample data
                     */
                    memcpy(snd_loop_buf + sound_len, sound_buf, length - snd_loop_len);

                    /**
                     * now the sound_len is again length!
                     */
                    sound_len = length;
                }
            }
            else
            {
                sound_len = length;
            }

            if (bTransition)
            {
                /**
                 * Mix in the sample from extra handling ;) (see above)
                 */
                SDL_MixAudio(audio, snd_loop_buf, sound_len, SDL_MIX_MAXVOLUME);
            }
            else
            {
                /**
                 * Mix this sound into the stream.
                 */
                SDL_MixAudio(audio, sound_buf, sound_len, SDL_MIX_MAXVOLUME);
            }

            /**
             * Update the sound buffer's position.
             */
            if (bTransition)
            {
                pos->position = length - snd_loop_len;

                /**
                 * free the extra-sound buffer
                 */
                free(snd_loop_buf);
            }
            else
            {
                pos->position += length;
            }

            /**
             * Have we reached the end of the sound?
             */
            if (pos->position >= (*it)->length_in_bytes)
            {
                /**
                 * NOTE: we do not need loop handling here. It was handled already earlier...
                 */

                /**
                 * delete from position-array
                 */
                pos = (*it)->positions.erase(pos);
            }
            else
            {
                ++pos;
            }
        }
    }
}

/*-------------------------------------
 **  THE PUBLIC FUNCTIONS FOR THE USER
 *------------------------------------*/

/**
 * initialize sound. You have to call this before sound-actions.
 * int freq: possible values are: {44100, 22050}
 * bool stereo: true -> stereo, else mono
 */
bool Sound::init(int freq, bool stereo)
{
    b_init_audio_sub_system = false;
    /**
     * check whether the user has already initialized the audio sub system
     */
    if (!( SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO ))
    {
        /**
         * initialize the sub-system now
         */
        SDL_InitSubSystem(SDL_INIT_AUDIO);
        b_init_audio_sub_system = true;
//        cout << "SND: SDL audio sub system initialized." << endl;
    }

    /**
     * Open the audio device. The sound driver will try to give us
     * the requested format, but it might not succeed. The 'obtained'
     * structure will be filled in with the actual format data.
     */
    m_desired.freq      = freq;     /* desired output sample rate */
    m_desired.format    = AUDIO_S16;/* request signed 16-bit samples */
    m_desired.samples   = 1024;     /* this is more or less discretionary */
    m_desired.channels  = (stereo==true)?2:1;  /* ask for stereo */
    m_desired.callback  = Sound::AudioCallback;
    m_desired.userdata  = NULL;     /* we don't need this */

    /**
     * Open the AudioDevice with the requested format
     */
    if (SDL_OpenAudio(&m_desired, &m_obtained) < 0)
    {
        cerr << "SND: Unable to open audio device: '" << SDL_GetError() << "'" << endl;
        return false;
    }

    /**
	 * Init SDL_sound
	 */
    if (!Sound_Init())
    {
        cerr << "SND: Sound_Init() failed! Reason: '" << Sound_GetError() << "'." << endl;
        return false;
    }

    /**
     * Stop audio at the beginning
     */
    SDL_PauseAudio(1);

    /**
     * set free_id to 0 because no id is used yet
     */
    m_free_id = 0;

    /**
     * initialization successful
     */
//    cout << "SND: Audio device opened" << endl;
    return true;
}

/**
 * load sound file.
 * return SoundInfo with which the user can play the sound.
 * if SndInfo == NULL the loading failed!
 */
const SndInfo* Sound::load(const string& file_name)
{
    map < string, SndInfo* >::iterator it;

    /**
     * check whether the file is loaded already because I want to avoid to load a sound twice
     */
    it = m_map_filename_table.find(file_name);
    if ( it == m_map_filename_table.end() )
    {
        /**
         * create a new soundinfo first and put in the file_name
         */
        SndInfo* new_sound_info = new SndInfo;
        new_sound_info->file_name = file_name;

        /**
         * initialize samples as NULL because if load_and_convert_sound failes
         * the "else­routine" tests whether sound is NULL or not
         */
        new_sound_info->sound = 0;

        /**
         * try to load and convert sound
         */
        if (load_and_convert_sound(new_sound_info) == true)
        {
            /**
             * set the sound's id to m_free_id
             */
            new_sound_info->snd_id = m_free_id++;

            /**
             * add new sound data to the sound-array
             */
            snd_container.push_back(new_sound_info);

            /**
             * add the new sound to the assignment tables
             */
            m_map_sound_table    [new_sound_info->snd_id   ] = new_sound_info;
            m_map_filename_table [new_sound_info->file_name] = new_sound_info;

            return new_sound_info;
        }
        else
        {
            if ( new_sound_info != NULL )
            {
                if (new_sound_info->sound != NULL)
                    Sound_FreeSample(new_sound_info->sound);
                delete new_sound_info;
            }

            return 0; // NULL
        }
    }
    else
    {
        /**
         * the sound is already loaded.
         * Return: it's pointer
         */
//        cout << "SND: using already loaded file: '" << file_name.c_str() << "'" << endl;
        return it->second;
    }
}

/**
 * unloads a sound. Needed to free memory (mostly for slow PCs with a few memory)
 */
void Sound::unload(const SndInfo* info)
{
    /**
     * if info && inf exists
     */
    if (info != NULL)
    {
        SndInfo* inf = info_from_id(info->snd_id);

        if (inf != NULL)
        {
            /**
             * deny AudioCallback
             */
            SDL_LockAudio();

            /**
             * free sample-data
             * remove entries from both maps
             * remove sound from container
             */
            Sound_FreeSample(inf->sound);
			inf->sound = 0;
            m_map_sound_table.erase(inf->snd_id);
            m_map_filename_table.erase(inf->file_name);

            /**
             * clear position array
             */
            inf->positions.clear();

            vector <SndInfo*>::iterator it = find(snd_container.begin(), snd_container.end(), inf);

            if (it != snd_container.end())
            {
                delete *it;
                snd_container.erase(it);
            }

            /**
             * allow AudioCallback
             */
            SDL_UnlockAudio();
        }
    }
}

/**
 * plays the sound SndInfo contains. It is possible to play the
 * sound more than one times at the same time
 */
void Sound::play(const SndInfo* info, bool loop)
{
    /**
     * add new info to the "position-list"
     */
    if (info != NULL)
    {
        /**
         * create a new "Info-table"
         */
        SndInfo::SndPlayInfos snd_play_infos;

        /**
         * set standard values
         */
        snd_play_infos.position = 0;
        snd_play_infos.loop = loop;

        SndInfo* inf = info_from_id(info->snd_id);
        if ( inf != NULL )
        {
            SDL_LockAudio();
            inf->positions.push_back(snd_play_infos);
            SDL_UnlockAudio();
        }
    }
}

/**
 * loads and plays a sound
 */
const SndInfo* Sound::play(const string& file_name, bool loop)
{
    const SndInfo* info = load(file_name);
    play(info, loop);

    return info;
}

/**
 * stops the sound SndInfo contains.
 */
void Sound::stop(const SndInfo* info)
{
    if (info != NULL)
    {
        SndInfo* inf = info_from_id(info->snd_id);
        if ( inf != NULL )
        {
            SDL_LockAudio();
            inf->positions.clear();
            SDL_UnlockAudio();
        }
    }
}

/**
 * check whether a sound is active
 */
bool Sound::is_running(const SndInfo* info)
{
    if (info != NULL)
    {
        SndInfo* inf = info_from_id(info->snd_id);
        if ( inf != NULL )
        {
            if (inf->positions.size() > 0) return true;
        }
    }
    return false;
}

/*---------------------------------------
 **  THE PRIVATE FUNCTIONS FOR INTERN USE
 *--------------------------------------*/

/**
 * frees all sound data
 */
void Sound::free_sound_data()
{
    /*
     * delete all samples... (really important - otherwise: memory leaks)
     */
    vector <SndInfo*>::iterator it;

    for (it = snd_container.begin(); it != snd_container.end(); ++it)
    {
        if ( (*it)->sound != 0 ) // !=NULL
        {
            Sound_FreeSample((*it)->sound);
			(*it)->sound = 0;
        }
    }
}

/**
 * frees the container array
 */
void Sound::free_array()
{
    vector < SndInfo* >::iterator it;

    for ( it = snd_container.begin(); it != snd_container.end(); ++it )
    {
        /**
         * delete the pointers...
         */
        if (*it)
            delete (*it);
    }

    snd_container.clear();
}

/**
 * load and convert sound into the requested format.
 * called by load_sound
 */
bool Sound::load_and_convert_sound(SndInfo* info)
{
	Sound_AudioInfo audio_info;
	audio_info.format = m_obtained.format;
	audio_info.channels = m_obtained.channels;
	audio_info.rate = m_obtained.freq;

	Sound_Sample *sample = Sound_NewSampleFromFile(info->file_name.c_str(), &audio_info, 16384);
	if (sample == 0)
	{
		cerr << "SND::load_and_convert_sound: '" << Sound_GetError() << "'" << endl;
		return false;
	}

	Sound_DecodeAll(sample);
	if (sample->flags & SOUND_SAMPLEFLAG_ERROR)
	{
		cerr << "SND::load_and_convert_sound: Couldn't fully decode \"" << info->file_name.c_str() << "\"!\n reason: '" << Sound_GetError() << "'." << endl;
		Sound_FreeSample(sample);
		return false;
	}

	if (sample->buffer == 0)
	{
		cerr << "SND::load_and_convert_sound: 'sample->buffer == 0'decode \"" << endl;
	Sound_FreeSample(sample);
		return false;
	}

	info->sound = sample;

	info->length_in_bytes = sample->buffer_size;
	info->length_in_ms = (static_cast<double>(info->length_in_bytes) / static_cast<double>(( sample->actual.rate * sample->actual.channels * 2 ))) * 1000.0;

	return true;
}

/**
 * return the SndInfo-class which has the id id.
 */
inline SndInfo* Sound::info_from_id(unsigned int id) const
{
    return m_map_sound_table[id];
}

