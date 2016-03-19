// v0.9   by gm (created)
// v0.901 by gm (cosmetic changes)

#include "imagelist.h"
#include "globals.h"
#include "filefinder.h"
#include "nameddatafile.h"
#include "mainconfig.h"
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <time.h>

ImageList::ImageList ()
{
    srand(time(0));
    load();
}

ImageList::~ImageList ()
{

}

void
ImageList::load()
{
    NamedDataFile ndf (Globals::maincfg().get(MC_IMAGE_LIST));
    ndf.load();

    FileFinder finder;

    m_imagepath = Globals::maincfg().get(MC_IMAGE_PATH);

    m_drawgame   = ndf.get("draw_game").to_string();
    m_gameresult = ndf.get("results").to_string();
    m_logo       = ndf.get("logo").to_string();
    m_mainmenu   = ndf.get("mainmenu").to_string();
    m_roulette   = ndf.get("roulette").to_string();
    m_title      = ndf.get("title").to_string();

//  cout << "remove this line!!! Debug: ImageList: m_imagepath = " << m_imagepath << endl;

    m_background = finder.find_files(m_imagepath, ndf.get("background"));
    sort(m_background.begin(), m_background.end());

    m_mapfield = finder.find_files(m_imagepath, ndf.get("map_field"));
    sort(m_mapfield.begin(), m_mapfield.end());

    m_teamvictory = finder.find_files(m_imagepath, ndf.get("team_victory"));
    sort(m_teamvictory.begin(), m_teamvictory.end());

    m_victory = finder.find_files(m_imagepath, ndf.get("victory"));
    sort(m_victory.begin(), m_victory.end());

    // Error detection:
    if (m_drawgame == "") cerr << "ImageList::load(): m_drawgame == \"\"\n";
    if (m_gameresult == "") cerr << "ImageList::load(): m_gameresult == \"\"\n";
    if (m_logo == "") cerr << "ImageList::load(): m_logo == \"\"\n";
    if (m_mainmenu == "") cerr << "ImageList::load(): m_mainmenu == \"\"\n";
    if (m_roulette == "") cerr << "ImageList::load(): m_roulette == \"\"\n";
    if (m_title == "") cerr << "ImageList::load(): m_title == \"\"\n";

    if (m_background.size() < 1) cerr << "ImageList::load(): m_background.size() < 1\n";
    if (m_mapfield.size() < 1) cerr << "ImageList::load(): m_mapfield.size() < 1\n";
    if (m_teamvictory.size() < 2) cerr << "ImageList::load(): m_teamvictory.size() < 2\n";
    if (m_victory.size() < 10) cerr << "ImageList::load(): m_victory.size() < 10\n";
}


string
ImageList::background_random()
{
    if (m_background.size() > 0)
    {
        return m_imagepath + m_background[rand() % m_background.size()];
    }
    else
    {
        cerr << "ImageList::background_random(): no images available.\n";
        return "";
    }
}

string
ImageList::mainmenu()
{
    return m_imagepath + m_mainmenu;
}

string
ImageList::game_result()
{
    return m_imagepath + m_gameresult;
}

string
ImageList::roulette()
{
    return m_imagepath + m_roulette;
}

string
ImageList::draw_game()
{
    return m_imagepath + m_drawgame;
}

string
ImageList::map_field(int map)
{
    return m_imagepath + m_mapfield[map];
}

string
ImageList::logo()
{
    return m_imagepath + m_logo;
}

string
ImageList::title()
{
    return m_imagepath + m_title;
}

string
ImageList::victory(int player)
{
    return m_imagepath + m_victory[player];
}

string
ImageList::team_victory(int team)
{
    return m_imagepath + m_teamvictory[team];
}
