// v0.1  by mm (created)
// v0.11 by gm (minor changes)

#ifndef FIELD_H
#define FIELD_H

#ifdef WIN32
#define NOMINMAX
#endif

#include "scheme.h"

#include <vector>
#include <list>
#include <valarray>
#include <memory>
using namespace std;

#include "cellpowerup.h"
#include "cellflame.h"
#include "cellbomb.h"
#include "cellextra.h"

struct TexInfo;
class Player;

class Field
{
public:


    //***************************************************************************************


    /**
     * a element of the field
     */
    class FieldCell
    {
    public:
        FieldCell();
        virtual ~FieldCell();

        /**
         * sets a new brick
         * if 'cell' == 0 the orignial brick remains
         */
        void set(cell::Cell* cell);

        const cell::Cell& cell() const;
        cell::Cell* cell_pointer();

        void draw();

    protected:
        cell::Cell*  m_cell;  // solid, breakable, powerup, bomb

        cell::Extra* m_extra;  // extra
    };

    typedef valarray < valarray < FieldCell > > FieldCellArray;


    //***************************************************************************************


    /**
     * stores a cell posistion
     */
    class CellCoo
    {
    public:
        CellCoo (int xx, int yy)
            : x(xx), y(yy)
            {
            }

        int x;
        int y;
    };

    /**
     * stores information about bricks that are empty so that a powerup can be put there
     */
    typedef vector < CellCoo > PowerupBrickVector;


    //***************************************************************************************


    enum EnumPowerupPlace { PLACE_HIDDEN = 0, PLACE_REVEALED };

    /**
     * used for PlayerPowerupVector and RecyclePowerupVector
     */
    class PowerupInfo
    {
    public:
        /**
         * used for PlayerPowerupList
         */
        PowerupInfo (EnumPowerups type, int player)
            : type (type),
              nPlayer (player),
              dStartTime (0.0)
            {
            }

        /**
         * used for RecyclePowerupList
         */
        PowerupInfo (EnumPowerups type, double start_time, double duration, EnumPowerupPlace place_)
            : type (type),
              nPlayer (-1),
              dStartTime (start_time),
              dDuration (duration),
              place (place_)
            {
            }

        bool operator == (const PowerupInfo& rhs) const
            {
                return type == rhs.type && nPlayer == rhs.nPlayer && place == rhs.place;
            }

        EnumPowerups type;

        /**
         * 0..9: who got the powerup
         * -1  : player is not relevant (= still on field)
         */
        int          nPlayer;

        /**
         * used for PowerupRecycler
         */
        double        dStartTime;
        double        dDuration;
        EnumPowerupPlace place;

    };

    typedef list < PowerupInfo > PlayerPowerupList;

    typedef vector < PowerupInfo > RecyclePowerupList;


    //***************************************************************************************


    /**
     * used in Field::draw() (todo: improve)
     */
    class DrawPlayerHelper
    {
    public:
        DrawPlayerHelper()
            : m_player (0),
              y (10000)
            {
            }

        DrawPlayerHelper(Player * player, double pix_y)
            : m_player (player),
              y (pix_y)
            {
            }

        bool operator< (const DrawPlayerHelper& rhs) const
            {
                return y < rhs.y;
            }

        Player * m_player;
        double    y;
    };

    //***************************************************************************************


public:
    Field ();
    virtual ~Field ();

    /**
     * draws the field
     */
    void draw();

    /**
     * processes the field: creates flames and much much more.
     */
    void process_field();

    /**
     * returns the field array (const)
     */
    bool  solid(int x, int y) const;


    /**
     * returns information about a cell at position (x, y)
     * TODO ???
     */
//    const cell::Cell& cell(int x, int y) const;

protected:
    /**
     * called in ctor:
     * loads the field from the global GameInfo (Globals::game())
     * inits textures, anims, ...
     * creates the field from the scheme data
     */
    void init();

    /**
     * called in dtor:
     */
    void unload();

    /**
     * removes blocks so that the player is not damned to lose at the beginning of a game
     */
    void make_player_space(int x, int y);

    /**
     * searches the field and fills m_powerupPositions with suitable values
     */
    void find_powerup_places();

    /**
     * puts 'count' powerups randomly on the field (hides them in breakable bricks)
     * if there are no "empty" bricks left the powerups are distributed on the free field
     * if there are no free cells left no powerups are put.
     */
    void put_powerup (EnumPowerups which, int count, EnumPowerupPlace where);


    /**
     * TODO: doc
     */
    void pf_delete_cells ();
    void pf_movement (Player& p);   // collision detection
    void pf_player_actions (Player& p);
    void pf_recycle_powerups ();
    void pf_rolling_bombs ();

    /**
     * if a player runs against a solid cell;
     * maybe kick a bomb
     */
    void on_pf_collide(Player& p, EnumDir dir, cell::Cell* pCell);


    /**
     * creates the flames of a just exploded bomb
     */
    void create_flames(cell::Bomb* pBomb);


    /**
     * by mm, gm
     * creates a flame cell:
     * returns true, if flame was set up correctly
     *         false, if flame runs against a barrier
     * player: who's bomb created the flame
     * type: flame type
     */
    bool create_flame(int x, int y, int player, cell::EnumFlameType type);


    /**
     * creates a bomb from Player p on position x,y
     * used for Spooger
     * returns false if bomb could not be created
     */
    bool create_bomb (Player& p, int x, int y);


    enum EnumAxis {HORIZ = 0, VERT};

    /**
     * checks if fieldpos is inside the field,
     * if so returns true
     * bRight = false: fieldpos is left or top
     * bRight = true : fieldpos is right or bottom
     */
    bool inside(EnumAxis axis, bool bRight, int fieldpos);

    /**
     * returns true if a player is on cell (x|y)
     */
    bool player_on_cell (int xx, int yy);

    /**
     * prints the number of each type of powerup lying somewhere on the field
     */
    void debug_count_powerups_on_field();

private:
    /**
     * map background
     */
    TexInfo* m_mapbg;

    /**
     * the game field
     */
    FieldCellArray m_field;

    /**
     * [PLACE_HIDDEN]:   positions of available breakable bricks
     * [PLACE_REVEALED]: positions of available blank bricks
     * (used for fast powerup distribution)
     */
    PowerupBrickVector m_powerupPositions[2];

    /**
     * stores all the powerups a player grabbed.
     * they will be released in case of player's death
     */
    PlayerPowerupList m_playerPowerups;

    /**
     * powerups stored here will be redistributed after a certain amount of time
     */
    RecyclePowerupList m_recycledPowerups;    // TODO: implement (valuelist.*, too)
};

#endif // FIELD_H
