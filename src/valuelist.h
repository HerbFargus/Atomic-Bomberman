// v0.1 by gm (created)
// v0.2 by gm (improvement of class design, new values added)

#ifndef VALUELIST_H
#define VALUELIST_H

#ifdef WIN32
#pragma warning(disable: 4786)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#endif

#include "enumvalues.h"

#include <vector>
#include <string>
using namespace std;

class Options;

/**
 * ValueList contains values that are NOT intended to be changed
 * interactively. This task does Options.
 * reads the file ./data/config/valuelist.res
 */
class ValueList
{
public:
    ValueList ();
    virtual ~ValueList ();

    /**
     * loads the data from the valuelist file
     * and applies the customization from the options file.
     * Will NOT be called in ctor, because of many errors that may occur.
     * Call only ONCE!
     */
    static void load();

    /**
     * returns the desired value
     */
    const int get(EnumValues which) const;

    const int max_maps() const;
    const int res_w() const;
    const int res_h() const;
    const int field_w() const;
    const int field_h() const;
    const int cell_w() const;
    const int cell_h() const;
    const int max_players() const;

    typedef vector < string > StringVector;
    /**
     * returns a const reference to the keyStrings vector
     */
    static const StringVector& keyStrings();

    /**
     * applies the values stored in options
     */
    static void apply_options (const Options & options);

protected:
    /**
     * increases the index to access the m_keyStrings vector
     * prints an error if cnt >= VAL_NUMBER_OF
     */
    static int save_inc(int* cnt);

    static void init_keystrings();

private:
    typedef vector < int > IntVector;
    static IntVector m_values;

    /**
     * stores the corresponding string keys (NamedDataFile) to m_values
     */
    static StringVector m_keyStrings;
};

#endif // VALUELIST_H
