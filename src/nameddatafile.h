/*************************************************************************
class:         NamedDataFile
author:        Gregor Mitsch
version:       1.81
              v1.82: 'const' compability added
              v1.83: load(): commentary will be ignored (beginning of a line is empty, space, ;, # or /)
              v1.84: protected --> private
              v1.9 : new member: remove(...)

last modified: 2003-05-13

description:   Loads and stores data to / from a text file.

// usage (sample): //
/////////////////////

#include "nameddatafile.h"

NamedDataFile file ("data.txt");    // select a file
file.load();        // load all the file's readable data

if (file.exists("number1"))
int number = file.get("number1");       // reads the value stored under the key "number1"

if (file.exists("number2"))
int num2 = file.get();                    // nameddatefile remembers last key used by exist(...)

if (file.exists("number3"))
cout << file.get().to_int();

file.set("doubleval", 5.5)              // stores the value 5.5 under the key "doubleval"
file.save();                        // saves the file
*************************************************************************/

#ifndef NAMEDDATAFILE_H
#define NAMEDDATAFILE_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <string>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

class NamedDataFile
{
protected:
    typedef map < string, string > DataMap;

    class Data
    {
    public:
        Data (const string& string_val)
            {
                m_strValue = string_val;
            }

        operator int() const
            {
                istringstream is (m_strValue.c_str());
                int val;
                is >> val;
                return val;
            }

        operator unsigned int() const
            {
                istringstream is (m_strValue.c_str());
                unsigned int val;
                is >> val;
                return val;
            }

        operator bool() const
            {
                istringstream is (m_strValue.c_str());
                int val;
                is >> val;
                return val==0?false:true;
            }

        operator double() const
            {
                istringstream is (m_strValue.c_str());
                double val;
                is >> val;
                return val;
            }

        operator string() const
            {
                return m_strValue;
            }

        const char* c_str() const
            {
                return m_strValue.c_str();
            }

        const int to_int() const
            {
                return static_cast <int> (*this);
            }

        const int to_uint() const
            {
                return static_cast <unsigned int> (*this);
            }
        
        const double to_double() const
            {
                return static_cast <double> (*this);
            }

        const bool to_bool() const
            {
                return static_cast <bool> (*this);
            }

        const string to_string() const
            {
                return static_cast <string> (*this);
            }

    protected:
        static  string      m_strValue;
    };

public:
    /**
     * constructs an object
     * the filename will not be validated
     */
    NamedDataFile (const string& filename);

    virtual ~NamedDataFile ();

    /**
     * rewrites the file with all data the internal data map contains
     * return: true, if all went ok
     *         false, if the output stream could not be created
     */
    bool save();

    /**
     * loads all the file's readable data
     * return: true, if all went ok
     *         false, if an error occured
     */
    bool load();

    /**
     * returns: true, if the entry entry exists
     *          otherwise false
     */
    bool exists (const char * entry) const;

    /**
     * removes the key 'entry' and therefore deletes it's value
     */
    void remove (const char * entry);


    NamedDataFile::Data get() const ;
    NamedDataFile::Data get(const char * entry) const;

    void set (const char * entry, int value);
    void set (const char * entry, unsigned int value);
    void set (const char * entry, double value);
    void set (const char * entry, bool value);
    void set (const char * entry, string value);
    void set (const char * entry, const char * value);

private:
    mutable DataMap m_datamap;
    string  m_str_filename;
    mutable string  m_str_last_key;        // set by exists(...)
};

#endif // NAMEDDATAFILE_H
