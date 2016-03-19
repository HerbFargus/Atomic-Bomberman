// v1.1 by gm (created)
// v1.2 by gm (minor changes)
// v1.3 by gm (minor changes)

#ifndef SCHEME_H
#define SCHEME_H

#ifdef WIN32
#pragma warning(disable: 4786)
#endif

#include "defines.h"
#include "enumpowerups.h"
#include "enumfieldextras.h"

#include <string>
#include <vector>
using namespace std;

class Powerups;

namespace std
{
    void tokenize_string(const string& str, vector<string>& tokens, const string& delimiters = " ");
}

/** TODO: Version 3 (with FieldExtras) **/

class Scheme
{
public:
    Scheme ();
    virtual ~Scheme ();

    bool load_from_file(string filename);

    /**
     * internal version control number
     * should be 2
     */
    int         version() const;

    /**
     * name of the sheme
     */
    string      name() const;

    /**
     * scheme brick density (0..100 %)
     */
    int         brick_density() const;

    /**
     * get the brick at pos (x, y):
     * BLANK, BRICK or SOLID
     */
    int         field_data(int x, int y) const;

    /**
     * player_no: number of the player
     *         x: x-Pos
     *         y: y-Pos
     *      team: 0..1 (Team 0 or Team 1), -1 not specified
     */
    void player_locations(int player_no, int* x, int* y, int* team) const;
    
    /**
     * fills the Powerups object with scheme values for the player's "born with" powerups
     * if the scheme file does not have a value for a powerup the global default value will be used
     */
    void powerup_info_player (Powerups * powerups) const;
    
    /**
     * fills the Powerups object with scheme values for field powerup information
     * if the scheme file does not have a value for a powerup the global default value will be used
     */
    void powerup_info_field (Powerups * powerups) const;

    /**
     * -1: if there was no error
     * else the line where the error occurs;
     */
    int get_error() const;
    
protected:
    /**
     *        powerup: what powerup (see enumpowerups.h)
     *
     *      born_with: number of this powerup that the players get at the beginning of a match
     *                 == 0: use default
     *                  > 0: use born_with as override (player)
     *
     *   if (has_override)
     *   override_value: the number of powerups to be on the field
     *
     *      forbidden: the powerup will never appear on the field and in the random powerup
     */
    void        powerup_info(int powerup, int* born_with, bool* has_override, int* override_value, bool* bForbidden) const;


private:
    struct PlayerInfo
    {
        int x;
        int y;
        int team;
    };

    struct PowerupInfo
    {
        int born_with;
        bool has_override;
        int override_value;
        bool bForbidden;
    };
    
    struct FieldExtraInfo
    {
        EnumFieldExtras type;
        int x;
        int y;
        int dir;
        int id;
        int warp_to;
    };

    int            m_version_number;
    string         m_name;
    int            m_brick_density;
    int            m_field_data[FIELD_WIDTH][FIELD_HEIGHT];
    PlayerInfo     m_player_locations[MAX_PLAYERS];
    PowerupInfo    m_powerup_info[PU_NUMBER_OF];
    FieldExtraInfo m_fieldextra_info[FE_NUMBER_OF];

    /**
     * flag: true if the data seems to be valid
     *       false if no file was loaded or there was an error
     */
    bool        m_bValidData;
    int         m_error_line;

};

#endif // SCHEME_H
