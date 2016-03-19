// v0.9 by gm (created)
// v1.0 by gm (fixed error in linux section)

#include "filefinder.h"
#ifdef WIN32
#include <windows.h>
#else
#include <iostream>
#include <fstream>
#endif

FileFinder::FileFinder ()
{

}

FileFinder::~FileFinder ()
{

}

StringVector
FileFinder::find_files(string path, string files)
{
    StringVector vec;

#ifdef WIN32

    string arg = path + files;
    WIN32_FIND_DATA wfd;
    HANDLE hFind = FindFirstFile(arg.c_str(), &wfd);
    do
    {
        vec.push_back(wfd.cFileName);
    }
    while(FindNextFile(hFind, &wfd));

#else // Linux

    const string tmpfile = path + "____________tmp_file___________";
    const string delcmd = "rm -f " + tmpfile;
    const string lscmd = "ls " + path + files + " -1 > " + tmpfile;

    system (delcmd.c_str());
    system (lscmd.c_str());

    ifstream file;
    file.open(tmpfile.c_str());

    while (file)
    {
        string line;
        file >> line;

        //line = line.substr(path.length(), line.length() - 1); // TO_DO: was soll das, warum geht das nicht??? (rein Interssehalber)
        line.erase(line.begin(), line.begin() + path.length());

        if (!line.empty())         // last line of tmpfile is empty
            vec.push_back(line);
    }

    file.close();

    system (delcmd.c_str());

#endif

    return vec;
}
