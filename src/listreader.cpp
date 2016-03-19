/*********************************************
 * SEE configreader.h FOR FURTHER INFORMATIN *
 *********************************************/

#include "listreader.h"

#include <fstream>
#include <iostream>

ListReader::ListReader()
{
}

ListReader::~ListReader()
{
}

/**
 * path:    where to search (with / at the end)
 * file:    filename of the config-file
 * section: the section can be like the following: "SEK" or "[SEK" or "[SEK]". the result is in all cases "[SEK]"
 */
StringVector ListReader::get(string path, string file, string section)
{
    StringVector vec;

    /**
     * complete the section-string with brackets
     */
    if (section[0] != '[') 
        section = "[" + section;
    if (section[section.length() - 1] != ']') 
        section = section + "]";

    /**
     * tmp-variables
     */
    string str;
    char buf [256];

    /**
     * open config file
     */
    ifstream is((path + file).c_str());

    /**
     * error message: possibilities:
     * 1) file does not exist
     * 2) permission denied
     */
    if (!is)
    {
        cerr << "Error: ListReader: file '" << file.c_str() << "' not found or permission denied." << endl;
    }

    /**
     * seek to the correct position (section) in the file
     */
    if (goto_section(&is, section) == true)
    {
        m_read_more_entries = true;

        while (is && m_read_more_entries)
        {
            is.getline(buf, sizeof buf);
            str = buf;

            /**
             * validate entry
             */
            if (is_valid_entry(str) )
            {
                vec.push_back(get_entry());
            }
        }
    }

    is.close();

    return vec;
}

/**
 * seek to the line which contains the string sec
 */
bool ListReader::goto_section(ifstream* is, string sec)
{
    string str;
    char buf [256];

    while (*is)
    {
        (*is).getline(buf, sizeof buf);
        str = buf;

        if (str[str.size() - 1] == '\r')
            str.erase(str.end() - 1);

        /**
         * make sections the same size. then we can check whether we are at the right position
         */
        if ( str.size() > sec.size())
        {
            str.erase(sec.size());
        }

        if ((str[0] == '[') && (str == sec))
        {
            /**
             * now we are at the correct position in the file
             */
            return true;
        }
    }

    /**
     * keyword sec does not exist!
     */
    cerr << "warning: ListReader::goto_section: Section not found." << endl;
    return false;
}

/**
 * checks the line's validation
 * return true: the current line containts a valid entry
 */
bool ListReader::is_valid_entry(string entry)
{
    if (entry[entry.size() - 1] == '\r')
        entry.erase(entry.end() - 1);

    if ( (entry.size() > 0) && (entry[0] != ';') && (entry[0] != ' ') && (entry[0] != '\t') && (entry[0] != '\n') )
    {
        if ( entry[0] == '[')
        {
            m_read_more_entries = false;
            return false;
        }

        /**
         * if there are blanks at the string's end remove them all
         */
        while (entry[entry.size() - 1] == ' ')
            entry.erase(entry.end() - 1);

        m_valid_entry = entry;

        return true;
    }

    return false;
}

/**
 * if is_valid_entry is true get the entry with this function
 */
inline string ListReader::get_entry() const
{
    return m_valid_entry;
}

