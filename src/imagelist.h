// v0.9   by gm (created)
// v0.901 by gm (cosmetic changes)

#ifndef IMAGELIST_H
#define IMAGELIST_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include <vector>
#include <string>
using namespace std;

typedef vector < string > StringVector;


class ImageList
{
public:
    /**
     * loads the image list
     */
    ImageList ();

    virtual ~ImageList ();

    /******************************************************
     * all functions below return the images' absolute path
     ******************************************************/

    /**
     * "background"
     * one of the background images
     */
    string   background_random();

    /**
     * "mainmenu"
     * mainmenu image
     */
    string   mainmenu();

    /**
     * "results"
     * image for the game result screen
     */
    string   game_result();

    /**
     * "roulette"
     * image of the gold bomberman roulette
     */
    string   roulette();

    /**
     * "draw_game"
     * draw game image
     */
    string   draw_game();

    /**
     * "map_field"
     * background of one of the 10 maps;
     * map = 0..9
     */
    string   map_field(int map);

    /**
     * "logo"
     * our logo
     */
    string   logo();

    /**
     * "title"
     * title image
     */
    string   title();

    /**
     * "victory"
     * image of the victory of one of the players
     * player = 0..9
     */
    string   victory(int player);

    /**
     * "team_victory"
     * team = 0..1
     */
    string   team_victory(int team);

protected:
    /**
     * loads the image list data
     * interpretes the * in the config values
     */
    void     load();

private:
    StringVector  m_background;
    string        m_drawgame;
    string        m_gameresult;
    string        m_logo;
    string        m_mainmenu;
    StringVector  m_mapfield;
    string        m_roulette;
    StringVector  m_teamvictory;
    string        m_title;
    StringVector  m_victory;

    string        m_imagepath;
};

#endif // IMAGELIST_H
