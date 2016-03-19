// v0.1  by gm (created)

/***************************************************************************
 *                                                                         *
 *   This program(class) is free software; you can redistribute it and/or  *
 *   modify it under the terms of the GNU General Public License as        *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 ***************************************************************************/

#ifndef SOUNDTOTEXT_H
#define SOUNDTOTEXT_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <string>
#include <map>
using namespace std;

/**
 * SoundToText
 */
class SoundToText
{
protected:
    class Sound
    {
    public:
        void raw_text_to_text();

    public:
        string sound;          // sound identifier (key of m_map)
        string raw_text;       // raw text string

        bool bNotCertain;      // true if "  ?" is at the end of raw_text
        bool bText;            // true if raw_text contains text
        bool bDescription;     // true if raw_text contains a <description>

        string text;           // Text that can be printed.
        string text_descr;      // Text with description
    };

public:
    SoundToText();
    virtual ~SoundToText();

    bool load_from_file (string file);

    bool lookup (string sound);

    string text();
    const Sound& info();

protected:
    string strip_lookup_sound(string lookup_sound);

    string raw_text_to_text (string raw_text);

private:
    typedef map < string, Sound > SoundMap;

    SoundMap m_map;

    string m_lookup_sound;

    Sound m_sound;

};

#endif // SOUNDTOTEXT_H
