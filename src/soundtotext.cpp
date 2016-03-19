// v0.1  by gm (created)

/**
 * SEE HEADER-FILE FOR MORE INFORMATION
 */

#include "soundtotext.h"
#include <fstream>
#include <algorithm>
#include <cctype>

SoundToText::SoundToText()
{
}

SoundToText::~SoundToText()
{
}

bool
SoundToText::load_from_file (string file)
{
    ifstream is (file.c_str());

    if (!is) return false;

    char buf[512];
    string  strLine;
    string  strSound;
    string  strText;

    while (is.getline(buf, sizeof buf))
    {
        strLine = buf;

        if (!strLine.empty())
        {
            // wegen Windows Zeilenendzeichen (muss entfernt werden)
            if (strLine[strLine.size()-1] == '\r')
                strLine.erase(strLine.end() - 1);

            // SoundToText begin

            if (strLine[0] != ' ' && strLine[0] != ';')  // if not commentary
            {
                string::size_type pos;
                pos = strLine.find(" ");
                strSound = string(strLine, 0, pos);
                for (string::iterator it = strSound.begin(); it != strSound.end(); ++it)
                    *it = tolower(*it);
///*did not work with gcc3.3*/ transform(strSound.begin(), strSound.end(), strSound.begin(), tolower);

                strText = string (strLine, pos, string::npos);
                while (strText[0] == ' ')
                    strText.erase(0, 1);

                Sound sound;
                sound.sound = strSound;
                sound.raw_text = strText;

                sound.raw_text_to_text();

//                cout << sound.sound << " - ";
//                cout << sound.raw_text << " - c";
//                cout << sound.bNotCertain << ", t";
//                cout << sound.bText << ", d";
//                cout << sound.bDescription;
//                cout << endl;

                m_map[sound.sound] = sound;

                strLine = "";
            }

            // SoundToText end
        }
    }

    return true;
}

bool
SoundToText::lookup (string sound)
{
    sound = strip_lookup_sound(sound);
    if (m_map.find (sound) != m_map.end())
    {
        m_sound = m_map[sound];
        return true;
    }
    else
    {
        return false;
    }
}

string
SoundToText::text()
{
    return m_sound.text;
}

const
SoundToText::Sound& SoundToText::info()
{
    return m_sound;
}

string
SoundToText::strip_lookup_sound(string lookup_sound)
{
    string::size_type pos = lookup_sound.rfind(".");
    lookup_sound.erase(pos);
    pos = lookup_sound.rfind("/");
    lookup_sound.erase(0, pos + 1);
    return lookup_sound;
}

void
SoundToText::Sound::raw_text_to_text ()
{
    string::size_type pos = raw_text.find("  ?");

    if (pos != string::npos)
        bNotCertain = true;
    else
        bNotCertain = false;

    string::size_type pos1 = raw_text.find("<");
    string::size_type pos2 = raw_text.find(">");
    if (pos1 != string::npos)
    {
        if (pos2 != string::npos)
        {
            bDescription = true;
            if (pos1 == 0 && pos2 == raw_text.length() - 1)
                bText = false;
            else
                bText = true;
        }
        else
        {
            bDescription = false;
            bText = true;
        }
    }
    else
    {
        bDescription = false;
        bText = true;
    }

    if (bNotCertain)
        text = "(" + string(raw_text, 0, pos) + ")";      // put not certain texts in parentheses
    else
        text = raw_text;

    if (bDescription)
    {
        text_descr = text;
    }

}
