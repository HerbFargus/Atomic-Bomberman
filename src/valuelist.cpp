// v0.1 by gm (created)
// v0.2 by gm (class design improvemed, new values added)

#include "valuelist.h"
#include "globals.h"
#include "mainconfig.h"
#include "options.h"
#include <iostream>

ValueList::IntVector ValueList::m_values;
ValueList::StringVector ValueList::m_keyStrings;

ValueList::ValueList ()
{

}

ValueList::~ValueList ()
{

}

int
ValueList::save_inc(int* cnt)
{
    if (*cnt >= VAL_NUMBER_OF)
    {
        cerr << "ValueList::load(): Programming error in 'valuelist.cpp': cnt >= VAL_NUMBER_OF!" << endl;
        return *cnt;
    }
    else
    {
        return (*cnt)++;
    }
}

void
ValueList::load()
{
    init_keystrings();

    NamedDataFile ndf (Globals::maincfg().get(MC_VALUE_LIST));
    ndf.load();

    m_values.resize(VAL_NUMBER_OF);

    int i = 0;
    for (i = 0; i < VAL_NUMBER_OF; ++i)
    {
        m_values[i] = ndf.get(keyStrings()[i].c_str());
    }

    // apply customized values from Options:

    apply_options(Globals::options());
}

const int
ValueList::get(EnumValues which) const
{
//    if (which >= m_values.size())
//        cerr << "ValueList::get(EnumValues which): Error in 'valuelist.cpp': 'which' out of range." << endl
//             << "         Since 'which' is an enumeration the value 'number_of_values' is to small." << endl;

    return m_values[which];
}

// TODO: test!!!
void
ValueList::apply_options (const Options & options)
{
    for (int i = 0; i < VAL_NUMBER_OF; ++i)
    {
        EnumValues val = static_cast <EnumValues> (i);
        if (options.exists(val))
            m_values[i] = options.get(val);
    }
}

const int
ValueList::max_maps() const
{
    return get(VAL_MAX_MAPS);
}

const int
ValueList::res_w() const
{
    return get(VAL_RES_W);
}

const int
ValueList::res_h() const
{
    return get(VAL_RES_H);
}

const int
ValueList::field_w() const
{
    return get(VAL_FIELD_WIDTH);
}

const int
ValueList::field_h() const
{
    return get(VAL_FIELD_HEIGHT);
}

const int
ValueList::cell_w() const
{
    return get(VAL_CELL_W);
}

const int
ValueList::cell_h() const
{
    return get(VAL_CELL_H);
}


const int
ValueList::max_players() const
{
    return get(VAL_MAX_PLAYERS);
}

const ValueList::StringVector&
ValueList::keyStrings()
{
    return m_keyStrings;
}

void
ValueList::init_keystrings()
{
    m_keyStrings.resize(VAL_NUMBER_OF);

    int cnt = 0;
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_RES_W";
    m_keyStrings[save_inc(&cnt)] = "VAL_RES_H";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_CELL_W";
    m_keyStrings[save_inc(&cnt)] = "VAL_CELL_H";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_FIELD_OFFSET_X";
    m_keyStrings[save_inc(&cnt)] = "VAL_FIELD_OFFSET_Y";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_SHOVE_W";
    m_keyStrings[save_inc(&cnt)] = "VAL_SHOVE_H";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_MAX_MAPS";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_INTRO_TIME_LOGO";
    m_keyStrings[save_inc(&cnt)] = "VAL_INTRO_TIME_TITLE";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_FIELD_WIDTH";
    m_keyStrings[save_inc(&cnt)] = "VAL_FIELD_HEIGHT";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_MAX_PLAYERS";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_NUM_TO_WIN_MATCH";
    m_keyStrings[save_inc(&cnt)] = "VAL_WIN_ON_WINS";
    m_keyStrings[save_inc(&cnt)] = "VAL_ENCLOSEMENT_DEPTH";
    m_keyStrings[save_inc(&cnt)] = "VAL_TEAMPLAY";
    m_keyStrings[save_inc(&cnt)] = "VAL_GAME_MUSIC";
    m_keyStrings[save_inc(&cnt)] = "VAL_MENU_MUSIC";
    m_keyStrings[save_inc(&cnt)] = "VAL_MAP";
    m_keyStrings[save_inc(&cnt)] = "VAL_ROUNDTIME";
    m_keyStrings[save_inc(&cnt)] = "VAL_FULLSCREEN";
    m_keyStrings[save_inc(&cnt)] = "VAL_PLAYER_RANDOM_START";
    m_keyStrings[save_inc(&cnt)] = "VAL_GOLDBOMBERMAN";
    m_keyStrings[save_inc(&cnt)] = "VAL_CONVEYOR_SPEED";
    m_keyStrings[save_inc(&cnt)] = "VAL_LOST_NET_REVERT_AI";
    m_keyStrings[save_inc(&cnt)] = "VAL_STOMPED_BOMBS_DETONATE";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_PLAYER_SPEED";
    m_keyStrings[save_inc(&cnt)] = "VAL_PLAYER_SPEED_ADD";
    m_keyStrings[save_inc(&cnt)] = "VAL_PLAYER_SPEED_MOLASSES";
    m_keyStrings[save_inc(&cnt)] = "VAL_PLAYER_SPEED_CRACK";
    m_keyStrings[save_inc(&cnt)] = "VAL_PLAYER_SPEED_CRACK_ADD";
    m_keyStrings[save_inc(&cnt)] = "VAL_BOMB_ROLL_SPEED";
    m_keyStrings[save_inc(&cnt)] = "VAL_BOMB_PUNCH_SPEED";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_MAINMENU_FONT_COLOR_R";
    m_keyStrings[save_inc(&cnt)] = "VAL_MAINMENU_FONT_COLOR_G";
    m_keyStrings[save_inc(&cnt)] = "VAL_MAINMENU_FONT_COLOR_B";
    m_keyStrings[save_inc(&cnt)] = "VAL_MENU_KEYREPEAT_DELAY";
    m_keyStrings[save_inc(&cnt)] = "VAL_MENU_KEYREPEAT_INTERVAL";
    m_keyStrings[save_inc(&cnt)] = "VAL_DOUBLECLICK_TIME";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_FUZE_TIME_NORMAL";
    m_keyStrings[save_inc(&cnt)] = "VAL_FUZE_TIME_SHORT";
    m_keyStrings[save_inc(&cnt)] = "VAL_FUZE_TIME_DUD_MIN";
    m_keyStrings[save_inc(&cnt)] = "VAL_FUZE_TIME_DUD_ADD";
    m_keyStrings[save_inc(&cnt)] = "VAL_TIME_FLAME_TRIGGER";
    m_keyStrings[save_inc(&cnt)] = "VAL_TIME_FLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_TIME_BRICK_DISINTEGRATE";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_MAX_TIME_PER_FRAME";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_TEAMPLAY_TIME_TRUECOLORS";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_SHOW_POWERUPS_IN_BRICKS";
    m_keyStrings[save_inc(&cnt)] = "VAL_SUICIDE_IMPOSSIBLE";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_FIREINTHEHOLE_BOMBS";
    m_keyStrings[save_inc(&cnt)] = "VAL_FIREINTHEHOLE_TIME";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_PLAYER_KEEPS_ADDITIONAL_PUS";
    m_keyStrings[save_inc(&cnt)] = "VAL_TIME_POWERUP_RECYCLE";
    m_keyStrings[save_inc(&cnt)] = "VAL_POWERUPS_DESTROYABLE";
    m_keyStrings[save_inc(&cnt)] = "VAL_DISEASES_DESTROYABLE";
    m_keyStrings[save_inc(&cnt)] = "VAL_TRY_HIDING_DEAD_PLAYER_PUS";
    m_keyStrings[save_inc(&cnt)] = "VAL_TRY_HIDING_EXCLUSION_PUS";
    m_keyStrings[save_inc(&cnt)] = "VAL_TRY_HIDING_OTHER_RECYCLED_PUS";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_BOMB";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_FLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_DISEASE";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_ABILITY_KICK";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_EXTRA_SPEED";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_ABLITY_PUNCH";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_ABILITY_GRAB";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_SPOOGER";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_GOLDFLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_TRIGGER";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_JELLY";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_EBOLA";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_INIT_RANDOM";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_BOMB";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_FLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_DISEASE";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_ABILITY_KICK";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_EXTRA_SPEED";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_ABILITY_PUNCH";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_ABILITY_GRAB";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_SPOOGER";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_GOLDFLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_TRIGGER";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_JELLY";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_EBOLA";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_MAX_RANDOM";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_BOMB";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_FLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_DISEASE";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_ABILITY_KICK";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_EXTRA_SPEED";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_ABLITY_PUNCH";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_ABILITY_GRAB";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_SPOOGER";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_GOLDFLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_TRIGGER";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_JELLY";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_EBOLA";
    m_keyStrings[save_inc(&cnt)] = "VAL_PU_FIELD_RANDOM";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_LIMITED";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_MULTIPLY";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_MIN_KEEP_BEFORE_PASS";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_ARE_CUREABLE";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_CURE_CHANCE";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_MOLASSES";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_CRACK";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_CONSTIPATION";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_POOPS";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_SHORTFLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_CRACKPOOPS";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_SHORTFUZE";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_SWAP";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_REVERSED";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_LEPROSY";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_INVISIBLE";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_DUDS";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_TIME_HYPERSWAP";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_MOLASSES";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_CRACK";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_CONSTIPATION";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_POOPS";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_SHORTFLAME";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_CRACKPOOPS";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_SHORTFUZE";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_SWAP";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_REVERSED";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_LEPROSY";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_INVISIBLE";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_DUDS";
    m_keyStrings[save_inc(&cnt)] = "VAL_DSE_PROB_HYPERSWAP";
    //--------------------------------------------------
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_0R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_0G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_0B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_1R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_1G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_1B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_2R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_2G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_2B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_3R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_3G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_3B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_4R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_4G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_4B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_5R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_5G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_5B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_6R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_6G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_6B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_7R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_7G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_7B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_8R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_8G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_8B";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_9R";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_9G";
    m_keyStrings[save_inc(&cnt)] = "VAL_COLOR_PLAYER_9B";
    //--------------------------------------------------

    if (cnt != VAL_NUMBER_OF)
        cerr << "ValueList::load(): Error in 'valuelist.cpp': number of enum entries does not match with number of load instructions!" << endl;
}
