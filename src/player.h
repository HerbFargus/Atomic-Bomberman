// v0.1  by gm (created)
// v0.11 by gm (development phase)
// v0.2  by gm (added new functions)
// v0.21 by gm (fixed memory handling errors)

/******************************************************************************
 *                                                                            *
 * LICENSE: GPL v2 (General Public License v2)                                *
 *                                                                            *
 ******************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#ifdef WIN32
#pragma warning(disable: 4786)
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#endif

#include "powerups.h"
#include "powerupdata.h"
#include "animmng.h"
#include "cellbomb.h"
#include "diseases.h"
#include "input.h"

/**
 * Player:
 * stores information about the state of the player during the game:
 * control interface, Powerups, wins, kills, ...
 */
class Player
{
public:
    /**
     * ctor:
     *
     * index:  the index where this player object is located in the Player array
     */
    Player(int index);

    virtual ~Player();

    /**
     * set a player active or inactive
     *
     * 'active' == true : activate Player
     * 'active' == false: disable Player
     */
    void set_active(bool active = true);

    /**
     * returns true, if the player is activated for the current game; else false
     */
    bool active() const;

    /**
     * returns a pointer to the input interface
     */
    input::Input* input();

    /**
     * sets the players control type.
     * important: use input::Manager to get the input pointer!
     */
    void set_input(input::Input* pInput);

    /**
     * resets wins and kills of the player, calls reset_round()  (begin of a new match)
     */
    void reset_match();

    /**
     * resets the powerups, sets the initial pixel pos (begin of a new round)
     */
    void reset_round();

    /**
     * updates the player before correcting it's position
     */
    void update();

    /**
     * sets walking direction depending on the actually covered distance
     */
    void update_animation();

    /**
     * draws the player
     */
    void draw();

    /**
     * returns a const reference to the Powerups object
     */
    const Powerups& powerups() const;
    
    /**
     * returns a reference to the player's PowerupData
     */
    PowerupData & pudata();
    
    /**
     * returns a non-const reference to the Diseases object
     */
    Diseases& diseases();


    /**
     * adds a powerup and updates relevant player data
     * return true, if successful
     * return false, if player exceeded the maximum number of the powerup 'pu'
     */
    bool add_powerup (EnumPowerups pu);

    /**
     * removes a powerup and updates relevant player data
     * return true, if successful
     * else false;
     */
    bool remove_powerup (EnumPowerups pu);

    /**
     * return true, if player wants to give back a powerup (if one powerup excludes the other)
     * if so, the function will actually remove the powerup using remove_powerup(...)
     */
    bool maybe_give_back_powerup(EnumPowerups *pu);
    
    /**
     * return the ID of the next trigger bomb;
     * attention: maybe this bomb already detonated;
     * returns 0 if there is no id in the list
     */
    UINT next_trigger_bomb_id();
    
    
    /**
     * increase the number of wins by 'amount'
     */
    void inc_wins(int amount = 1);

    /**
     * increase the number of kills by 'amount'
     */
    void inc_kills(int amount = 1);

    /**
     * return the number of wins
     */
    int wins() const;

    /**
     * return the number of kills
     */
    int kills() const;

    /**
     * returns the player's index
     */
    int index() const;

    /**
     * sets the player's position in screen pixels (logical field positions will be adapted)
     */
    void set_pixelpos(double x, double y);

    /**
     * returns the pixel positions
     */
    double pixelpos_x() const;
    double pixelpos_y() const;

    /**
     * sets the player's logical field posistion (pixel posistions will be adapted)
     */
    void set_fieldpos(int x, int y);

    /**
     * returns logical field position
     */
    int fieldpos_x() const;
    int fieldpos_y() const;

    /**
     * returns the current speed of the player in pixels per second
     */
    double speed() const;

    /**
     * returns the current direction of the player
     */
    EnumDir direction() const;

    /**
     * logical "coming" field position if player moves away from field element's centre,
     * depends on current direction;
     * will NEVER return same values as fieldpos_x,y() (hope so => TODO: correctness proof)
     */
    void coming_fieldpos(int *x, int *y) const;

    /**
     * like above but it is NOT depending on the player's current pixelpos
     */
    void coming_fieldpos2(int *x, int *y) const;

    /**
     * creates a bomb (dynamically allocated - will be deleted by class Field)
     * with suitible parameters
     * returns 0, if no bomb was created (e. g. if ill or if max. bomb number was exeeded)
     *
     * optional: bomb's position (used by Field to implement spooger)
     *           (there is no test if pos. is valid!)
     */
    cell::Bomb* create_bomb(int x = -1, int y = -1);

    /**
     * Field calls this if a player's bomb explodes
     */
    void inc_available_bombs();

    /**
     * true if player is walking
     */
    bool walking();

    /**
     * if a player hit a flame
     */
    void kill();

    /**
     * return true if the player is dead
     */
    bool dead() const;

    /**
     * TODO: return the center of a cell
     */
    double cell_center (double *center_x, double *center_y, double pixx, double pixy, int direction);


    /**
     * swaps the position with another player
     */
    void swap_positions (Player & swap_partner);

    void debug_print_powerups();

protected:
    /**
     * called in the contructor
     */
    void init();

    /**
     * reads the pixel positions and calculates the logical field positions
     */
    void pixel2field(const double& px, const double& py, int *fx, int *fy);

    /**
     * vice versa
     */
    void field2pixel(const int& fx, const int& fy, double *px, double *py);

    /**
     * apply powerup values:
     * 1) PU_EXTRA_SPEED --> anim speed
     * 2) todo
     */
    void apply_powerup_values();

private:
    /**
     * do not allow copying!
     */
    Player (Player &);
    Player& operator == (Player &);

private:
    bool m_bActive;

    input::Input *m_pInput;

    /**
     * stores the player's powerup values
     */
    Powerups       m_powerups;
    
    /**
     * manages all Powerup relevant data
     */
    PowerupData    m_pudata;

    /**
     * manages the player's diseases
     */
    Diseases m_diseases;

    /**
     * number of bombs on the field
     */
    int m_nBombsOnField;

    int            m_nWins;

    int            m_nKills;

    int            m_nArrayIndex;

    int            m_fieldpos_x;
    int            m_fieldpos_y;

    /**
     * screen position of the player's shadow (centre)
     */
    double          m_pixelpos_x;
    double          m_pixelpos_y;

    /**
     * current speed in pixels per second
     */
    double          m_speed;

    /**
     * the player's animation
     */
    Animation     m_anim;
    EnumAnims     m_curAnim;

    /**
     * current direction (see EnumDir in animmng.h), always a valid value
     * m_direction is either equal m_dir1 or m_dir2
     */
    EnumDir       m_direction;

    /**
     * direction if one key is pressed; if no second key pressed, equal m_direction
     */
    EnumDir       m_dir1;

    /**
     * direction if a second key is pressed; may be -1
     */
    int            m_dir2;

    /**
     * true, if currently walking
     */
    bool           m_bWalking;

    /**
     * true, if direction changed and immediately false after starting new anim
     */
    // TODO
    bool           m_bDirChanged;
    EnumDir m_oldDir;
    double  m_oldx;
    double  m_oldy;

    /**
     * TODO
     */
    double m_fith_starttime;
    double m_fith_bombs;

    bool m_bDead;

    /**
     * see maybe_give_back_powerup (...)
     * -1, if no powerup is to be given back
     */
    int m_nGiveBackPu;
};

#endif // PLAYER_H
