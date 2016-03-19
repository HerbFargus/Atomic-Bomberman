/***********************************************
 *                                             *
 * Author: Dominik Haumann                     *
 * E-Mail: haumann@gmdsoft.de                  *
 * Web   : http://www.gmdsoft.de               *
 *                                             *
 * class: ListReader                           *
 * Version: 0.3                                *
 * History: 0.1 - 0.3 dh                       *
 *                                             *
 * LICENSE: GPLv2 (General Public License v2)  *
 *                                             *
 ***********************************************/


#ifndef LIST_READER_H
#define LIST_READER_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <fstream>
#include <vector>
#include <string>
using namespace std;

typedef vector < string > StringVector;

/**
 * class ListReader
 * task: Read a sektion and return it as a vector <string>
 *
 * use: // really easy! works on Linux & Win32
 *
 *   ListReader cr;
 *   StringVector sv = cr.get_config("./", "config_file", "SEK");
 *
 *   // NOTE: "SEK" is the same as "[SEK" and "[SEK]"
 */
class ListReader
{
public:
    ListReader();
    virtual ~ListReader();

    /**
     * path:    where to search (with / at the end)
     * file:    filename of the config-file
     * section: the section can be like the following: "SEK" or "[SEK" or "[SEK]". the result is in all cases "[SEK]"
     */
    StringVector get(string path, string file, string section);

protected: // functions
    /**
     * seek to the line in the file that contaings the string sec
     * return false: the section does not exist
     */
    bool goto_section(ifstream* is, string sec);

    /**
     * checks the line's validation
     * return true: the current line containts a valid entry
     */
    bool is_valid_entry(string entry);

    /**
     * if is_valid_entry is true get the entry with this function
     */
    inline string get_entry() const;

protected: // variables
    /**
     * contains the last valid entry
     */
    string m_valid_entry;

    /**
     * true when the section is not read completely
     */
    bool m_read_more_entries;
    
};
#endif // LIST_READER_H
