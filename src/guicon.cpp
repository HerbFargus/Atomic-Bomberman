#ifdef WIN32

#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include "guicon.h"

#ifndef _USE_OLD_IOSTREAMS
using namespace std;
#endif

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;
static const WORD MAX_CONSOLE_WIDTH = 180;

void
RedirectIOToConsole()
{
    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;
    
    // allocate a console for this app
    AllocConsole();
    
    // set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);

    coninfo.dwSize.Y = MAX_CONSOLE_LINES;
    coninfo.dwSize.X = MAX_CONSOLE_WIDTH;

    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

//    coninfo.srWindow.Left   = 0;
//    coninfo.srWindow.Top    = 0;
//    coninfo.srWindow.Right  += 100;
//    coninfo.srWindow.Bottom += 100;
//    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &coninfo.srWindow);

    
    // redirect unbuffered STDOUT to the console
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );
    
    // redirect unbuffered STDIN to the console
    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );
    
    // redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );

    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog 
    // point to console as well
    ios::sync_with_stdio();
}

#endif
