// v0.9 by gm (created)
// v1.0 by gm (fixed error in linux section)

#ifndef FILEFINDER_H
#define FILEFINDER_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <vector>
#include <string>
using namespace std;

typedef vector < string > StringVector;

class FileFinder
{
public:
    FileFinder ();
    virtual ~FileFinder ();

    /**
     * path:   where to search (with / at the end)
     * files:  filename (with wildcards)
     * allowed wildcard: * stands for any or no character
     *
     * return value: the vector conains the found filenames (inclusive file extension)
     */
    StringVector find_files(string path, string files);
};

#endif // FILEFINDER_H
