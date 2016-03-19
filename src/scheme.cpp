// v1.1 by gm (created)
// v1.2 by gm (minor changes)
// v1.3 by gm (minor changes)

#include "scheme.h"
#include "enumblocks.h"
#include "powerups.h"
#include "fieldextras.h"
#include "globals.h"
#include "valuelist.h"

#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Scheme::Scheme () : m_bValidData(false)
{

}

Scheme::~Scheme ()
{

}

bool
Scheme::load_from_file(string filename)
{
    m_error_line = 0;   // save line in case of error
    m_bValidData = false;

    ifstream ifstr;
    ifstr.open(filename.c_str());

    string line;

    if (!ifstr) return false;

    while (ifstr)
    {
        ++m_error_line;

        char cline[256];    // line buffer: 256 characters
        ifstr.getline(cline, 256);
        line = cline;

        if (line[line.size()-1] == '\r')
            line.erase(line.end() - 1);

        if (line.length() > 0)
        {
            if (line[0] == '-')
            {
                switch (line[1])
                {
                case 'V':
                {
                    istringstream is(line.substr(3, 2).c_str());
                    is >> m_version_number;
                    break;
                }

                case 'N':
                {
                    m_name = line.substr(3, -1);
                    break;
                }

                case 'B':
                {
                    istringstream is(line.substr(3, 3).c_str());
                    is >> m_brick_density;
                    if (m_brick_density < 0 || m_brick_density > 100)
                    {
                        m_bValidData = false;
                        return false;
                    }

                    break;
                }

                case 'R':
                {
                    if (line.length() < 21)
                    {
                        m_bValidData = false;
                        return false;
                    }

                    istringstream is(line.substr(3, 2).c_str());
                    int y;
                    is >> y;

                    if (y < 0 || y > 10)
                    {
                        m_bValidData = false;
                        return false;
                    }

                    for (int x = 0; x < FIELD_WIDTH; ++x)
                    {
                        switch (line[6 + x])
                        {
                        case '#':
                            m_field_data[x][y] = BLOCK_SOLID;
                            break;
                        case ':':
                            m_field_data[x][y] = BLOCK_BREAKABLE;
                            break;
                        case '.':
                            m_field_data[x][y] = BLOCK_BLANK;
                            break;
                        default:
                            m_bValidData = false;
                            return false;
                        }
                    }
                    break;
                }

                case 'S': // PlayerLocations
                {
                    vector <string> result;
                    tokenize_string(line.substr(3, -1), result, ",");

                    if (result.size() < 3)
                    {
                        m_bValidData = false;
                        return false;
                    }

                    int plno, x, y, team = -1;
                    istringstream is(result[0]);
                    is >> plno;
                    is.clear(); is.str(result[1]);
                    is >> x;
                    is.clear(); is.str(result[2]);
                    is >> y;

                    // if team is specified...
                    if (result.size() == 4)
                    {
                        is.clear(); is.str(result[3]);
                        is >> team;
                    }

                    m_player_locations[plno].x    = x;
                    m_player_locations[plno].y    = y;
                    m_player_locations[plno].team = team;
                    break;
                }

                case 'P': // Powerup Infos
                {
                    vector <string> result;
                    tokenize_string(line.substr(3, -1), result, ",");

                    if (result.size() < 6)
                    {
                        m_bValidData = false;
                        return false;
                    }

                    int puno, bw, has_ov, ov, fb;
                    istringstream is(result[0]);
                    is >> puno;
                    is.clear(); is.str(result[1]);
                    is >> bw;
                    is.clear(); is.str(result[2]);
                    is >> has_ov;
                    is.clear(); is.str(result[3]);
                    is >> ov;
                    is.clear(); is.str(result[4]);
                    is >> fb;

                    m_powerup_info[puno].born_with      = bw;
                    m_powerup_info[puno].has_override   = has_ov==0?false:true;
                    m_powerup_info[puno].override_value = ov;
                    m_powerup_info[puno].bForbidden     = fb==0?false:true;
                    break;
                }
                
                // version 3:
                
                case 'A':      // Arrows
//                    -A,E,1,0
//                    -A,E,1,1
//                    -A,E,1,2
//                    -A,W,1,3
//                    -A,N,1,4
//                    -A,E,1,5
                    break;
                    
                case 'C':     // Conveyer Belt
//                    -C,E,1,2
//                    -C,S,2,2
//                    -C,W,3,2
//                    -C,S,4,2
//                    -C,N,5,2
//                    -C,W,6,2
//                    -C,E,7,2
                    break;
                    
                case 'T':      // Trampoline
//                   -T,2,2
//                   -T,-3,2
//                   -T,2,-3
//                   -T,-3,-3
//                   -T,H,H
//                   -T,H,H
//                   -T,H,H
//                   -T,H,H
                    break;
                    
                case 'W':     // Warp Holes
                    //-W,1,0, 0, 0,7
                    //-W,1,1, 0, 5,8
                    //-W,1,2, 0,10,4
                    //-W,1,3, 7, 0,5
                    break;
                    
                case 'I':     // Ice
//                    -I,1,2
//                    -I,2,2
//                    -I,3,2
//                    -I,4,2
//                    -I,5,2
//                    -I,6,2
//                    -I,7,2
                    break;
                    
                }
            }
        }
    }

    m_bValidData = true;
    return true;
}

int
Scheme::version() const
{
    return m_version_number;
}

string
Scheme::name() const
{
    return m_name;
}

int
Scheme::brick_density() const
{
    return m_brick_density;
}

int
Scheme::field_data(int x, int y) const
{
    return m_field_data[x][y];
}

void
Scheme::player_locations(int player_no, int* x, int* y, int* team) const
{
    if (player_no < 0 || player_no >= MAX_PLAYERS)
        cerr << "Scheme::player_locations(...): 'player_no' out of range: " << player_no << endl;

    *x    = m_player_locations[player_no].x;
    *y    = m_player_locations[player_no].y;
    *team = m_player_locations[player_no].team;
}

void
Scheme::powerup_info(int powerup, int* born_with, bool* has_override, int* override_value, bool* bForbidden) const
{
    if (powerup < 0 || powerup >= PU_NUMBER_OF)
        cerr << "Scheme::powerup_info(...): 'powerup' out of range: " << powerup << endl;
    
    if (version() == 2) // version 2
    {
        if (powerup > 12)  // version 2 knows the powerups 0..12
        {   
            *born_with = 0;
            *has_override = false;
        }
        else
        {
            *born_with      = m_powerup_info[powerup].born_with;    
            *has_override   = m_powerup_info[powerup].has_override;
            *override_value = m_powerup_info[powerup].override_value;
            *bForbidden     = m_powerup_info[powerup].bForbidden;
            
        }
    }
    else // version 3
    {
        // TODO: auch einschraenken!!!
        *born_with      = m_powerup_info[powerup].born_with;    
        *has_override   = m_powerup_info[powerup].has_override;
        *override_value = m_powerup_info[powerup].override_value;
        *bForbidden     = m_powerup_info[powerup].bForbidden;
    }
}

void
Scheme::powerup_info_player (Powerups * powerups) const
{
    Globals g;
    int i;
    
    int born_with, override_value;
    bool bHasOverride, bForbidden;
    
    for (i = 0; i < PU_NUMBER_OF; ++i)
    {
        powerup_info(i, &born_with, &bHasOverride, &override_value, &bForbidden);
        
        if (0 != born_with)      // non-zero value will be used for 'born_with'
        {
            powerups->set(static_cast < EnumPowerups > (i), born_with);
        }
        else
        {
            // Attention: make sure that VAL_INIT_PU_BOMB is the first of the VAL_INIT_PU... values
            powerups->set(static_cast < EnumPowerups > (i), g.values().get(static_cast <EnumValues> (VAL_PU_INIT_BOMB + i)));  
        }
    }
}

void
Scheme::powerup_info_field (Powerups * powerups) const
{
    Globals g;
    int i;
    
    int born_with, override_value;
    bool bHasOverride, bForbidden;
    
    for (i = 0; i < PU_NUMBER_OF; ++i)
    {
        powerup_info(i, &born_with, &bHasOverride, &override_value, &bForbidden);
        
        if (bHasOverride || bForbidden)
        {
            if (bForbidden)
                powerups->set(static_cast < EnumPowerups > (i), 0);
            else
                powerups->set(static_cast < EnumPowerups > (i), override_value);
        }
        else
        {
            // Attention: make sure that VAL_INIT_PU_BOMB is the first of the VAL_INIT_PU... values
            powerups->set(static_cast < EnumPowerups > (i), g.values().get(static_cast <EnumValues> (VAL_PU_FIELD_BOMB + i)));
        }
    }
}

int
Scheme::get_error() const
{
    if (m_bValidData)
        return -1;
    else
        return m_error_line;
}
