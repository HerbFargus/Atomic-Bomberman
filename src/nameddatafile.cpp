/*************************************************************************
class:         NamedDataFile
author:        Gregor Mitsch
version:       1.9
detailed info: see nameddatafile.h
*************************************************************************/

#include "nameddatafile.h"
#include <algorithm>
#include <iostream>

typedef map < string, string > DataMap;
string  NamedDataFile::Data::m_strValue;

#ifdef WIN32
#include <stdlib.h>
#endif


NamedDataFile::NamedDataFile (const string& filename)
    : m_str_filename (filename)
{

}

NamedDataFile::~NamedDataFile ()
{

}


bool
NamedDataFile::load()
{
    ifstream is (m_str_filename.c_str());
    if (!is) return false;

    bool    bErrorOccured;
    bool    bEof = false;   // damit am Ende der Datei nicht unbedingt eine Leerzeile stehen muss

    char buf[256];      // längere Zeilen werden häppchenweise gelesen
    string  strLine;
    string  strKey;
    string  strValue;

    while (!bEof && (is.getline(buf, sizeof buf) || is.gcount()))
    {
        bEof = is.eof();

        if (is.fail())  // Zeile ist länger als Puffer
        {
            is.clear (is.rdstate() & ~ios::failbit);
            strLine += buf;
        }
        else
        {
            strLine += buf;

            if (strLine.empty() || strLine[0] == ' ' || strLine[0] == '#' || strLine[0] == ';' || strLine[0] == '/')
            {
                strLine = "";
                // That's a commentary.
            }
            else
            {
                string::size_type spacepos = strLine.find(' ');
                if (spacepos == string::npos)
                {
                    bErrorOccured = true;
                }
                else
                {
                    strKey = strLine.substr(0, spacepos);
                    strValue = strLine.substr(spacepos + 1, string::npos);

                    // wegen Windows Zeilenendzeichen (muss entfernt werden)
                    if (strValue[strValue.size()-1] == '\r')
                        strValue.erase(strValue.end() - 1);

                    strLine = "";

                    m_datamap[strKey] = strValue;
                }
            }
        }
    }

    return true;
}

bool
NamedDataFile::save()
{
    ofstream of (m_str_filename.c_str());
    if (!of) return false;

    for (DataMap::iterator it = m_datamap.begin(); it != m_datamap.end(); ++it)       // (TODO: algorithm) ???
    {
        of << it->first << ' ' << it->second << endl;
    }

    return true;
}

bool
NamedDataFile::exists (const char * entry) const
{
    m_str_last_key = entry;
    if (m_str_last_key == "")
        return false;
    else
        return m_datamap.find (entry) != m_datamap.end();
}

void
NamedDataFile::remove (const char * entry)
{
    if (exists(entry))
        m_datamap.erase (m_datamap.find(entry));
}

NamedDataFile::Data
NamedDataFile::get() const
{
    string key = m_str_last_key;
    return Data(m_datamap[key]);
}

NamedDataFile::Data
NamedDataFile::get(const char * entry) const
{
    if (exists(entry))
        return Data(m_datamap[entry]);
    else
    {
        cerr << "Warning: NamedDataFile::get(const char* entry): unknown 'entry': '" << entry << "' ; return a zero value." << endl;
        return Data ("");
    }
}

void
NamedDataFile::set (const char * entry, int value)
{
#ifdef WIN32
    char buffer[64];
    sprintf (buffer, "%d", value);
    m_datamap[entry] = buffer;
#else
    ostringstream os;
    os << value;
    m_datamap[entry] = os.str();
#endif
}

void
NamedDataFile::set (const char * entry, unsigned int value)
{
#ifdef WIN32
    char buffer[64];
    sprintf (buffer, "%u", value);
    m_datamap[entry] = buffer;
#else
    ostringstream os;
    os << value;
    m_datamap[entry] = os.str();
#endif
}

void
NamedDataFile::set (const char * entry, double value)
{
#ifdef WIN32
    char buffer[64];
    sprintf (buffer, "%f", value);
    m_datamap[entry] = buffer;
#else
    ostringstream os;
    os << value;
    m_datamap[entry] = os.str();
#endif
}

void
NamedDataFile::set (const char * entry, bool value)
{
    m_datamap[entry] = value?"1":"0";
}

void
NamedDataFile::set (const char * entry, string value)
{
    m_datamap[entry] = value;
}

void
NamedDataFile::set (const char * entry, const char * value)
{
//#ifdef WIN32
//#else
    ostringstream os;
    os << value;
    m_datamap[entry] = os.str();
//#endif
}
