#ifndef ENUMVALUES_H
#define ENUMVALUES_H

/**
 * if you add an entry, you must modify ValueList::load()
 *
 * detailed value descriptions see ./data/config/valuelist.res
 */
// index: description                                                           (default value)
enum EnumValues { VAL_RES_W         = 0       , // Screen resolution (width)                                                (1024)
                  VAL_RES_H                   , //                    (height)                                               (768)
                  //------------------------------
                  VAL_CELL_W                  , // Size of a tile (field cell) in pixels (width)                            (64)
                  VAL_CELL_H                  , //                                           (height)                        (64)
                  //------------------------------
                  VAL_FIELD_OFFSET_X          , // distance between screen border and field in pixels (x)
                  VAL_FIELD_OFFSET_Y          , //                                                     (y)
                  //------------------------------
                  VAL_SHOVE_W                 , // "shove pixel" (width)
                  VAL_SHOVE_H                 , //                (height)
                  //------------------------------
                  VAL_MAX_MAPS                , // the number of different maps                                             (11)
                  //------------------------------
                  VAL_INTRO_TIME_LOGO         , // StateIntro: maximum time in seconds our logo will be displayed
                  VAL_INTRO_TIME_TITLE        , // StateIntro: maximum time in seconds the title image will be displayed
                  //------------------------------
                  VAL_FIELD_WIDTH             , // number of blocks in the field horizontally                               (15)
                  VAL_FIELD_HEIGHT            , //                               vertically                                 (11)
                  //------------------------------
                  VAL_MAX_PLAYERS             , // maximum number of players                                                (10)
                  //------------------------------
                  VAL_NUM_TO_WIN_MATCH,
                  VAL_WIN_ON_WINS,
                  VAL_ENCLOSEMENT_DEPTH,
                  VAL_TEAMPLAY,
                  VAL_GAME_MUSIC,
                  VAL_MENU_MUSIC,
                  VAL_MAP,
                  VAL_ROUNDTIME,
                  VAL_FULLSCREEN,
                  VAL_PLAYER_RANDOM_START,
                  VAL_GOLDBOMBERMAN,
                  VAL_CONVEYOR_SPEED,
                  VAL_LOST_NET_REVERT_AI,
                  VAL_STOMPED_BOMBS_DETONATE,
                  //------------------------------
                  VAL_PLAYER_SPEED            , // initial player speed in pixels per second
                  VAL_PLAYER_SPEED_ADD        , // additional speed in pixels per second if player gets a speed powerup
                  VAL_PLAYER_SPEED_MOLASSES,
                  VAL_PLAYER_SPEED_CRACK,
                  VAL_PLAYER_SPEED_CRACK_ADD,
                  VAL_BOMB_ROLL_SPEED,
                  VAL_BOMB_PUNCH_SPEED,
                  //------------------------------
                  VAL_MAINMENU_FONT_COLOR_R   , // Mainmenu's font color (red)                                              (255)
                  VAL_MAINMENU_FONT_COLOR_G   , // Mainmenu's font color (green)                                            (255)
                  VAL_MAINMENU_FONT_COLOR_B   , // Mainmenu's font color (blue)                                             (255)
                  VAL_MENU_KEYREPEAT_DELAY    , // time in milliseconds till keyrepeat starts                               (250)
                  VAL_MENU_KEYREPEAT_INTERVAL , // keyrepeat interval in milliseconds                                       (100)
                  VAL_DOUBLECLICK_TIME        , // (100)
                  //------------------------------
                  VAL_FUZE_TIME_NORMAL        , // time in milliseconds till explosion: normal
                  VAL_FUZE_TIME_SHORT         , // time in milliseconds till explosion: short fuze
                  VAL_FUZE_TIME_DUD_MIN       , // time in milliseconds till explosion: dud minimal
                  VAL_FUZE_TIME_DUD_ADD       , // time in milliseconds till explosion: dud additional
                  VAL_TIME_FLAME_TRIGGER      , // if a flame hits another bomb: time in milliseconds till this bomb explodes
                  VAL_TIME_FLAME              , // TODO: doc                                                                (1000)
                  VAL_TIME_BRICK_DISINTEGRATE , //                                                                           (1000)
                  //------------------------------
                  VAL_MAX_TIME_PER_FRAME      , //                                                                           (150)
                  //------------------------------
                  VAL_TEAMPLAY_TIME_TRUECOLORS, //                                                                           (2000)
                  //------------------------------
                  VAL_SHOW_POWERUPS_IN_BRICKS ,  //                                                                              (0)
                  VAL_SUICIDE_IMPOSSIBLE      ,  //                                                                              (0)
                  //------------------------------
                  VAL_FIREINTHEHOLE_BOMBS     ,  // if 'VAL_FIREINTHEHOLE_BOMBS' bombs are thrown in...
                  VAL_FIREINTHEHOLE_TIME      ,  // ...'VAL_FIREINTHEHOLE_TIME' milliseconds then a sound is played
                  //------------------------------
                  VAL_PLAYER_KEEPS_ADDITIONAL_PUS,          // (1)
                  VAL_TIME_POWERUP_RECYCLE,                 // (3)
                  VAL_POWERUPS_DESTROYABLE,                 // (0)
                  VAL_DISEASES_DESTROYABLE,                 // (1)
                  VAL_TRY_HIDING_DEAD_PLAYER_PUS,           // (0)
                  VAL_TRY_HIDING_EXCLUSION_PUS,           // (0)
                  VAL_TRY_HIDING_OTHER_RECYCLED_PUS,        // (1)
                  //------------------------------
                  VAL_PU_INIT_BOMB            , //                                                                           (1)
                  VAL_PU_INIT_FLAME           , //                                                                           (2)
                  VAL_PU_INIT_DISEASE         , //                                                                           (0)
                  VAL_PU_INIT_ABILITY_KICK    , //                                                                           (0)
                  VAL_PU_INIT_EXTRA_SPEED     , //                                                                           (0)
                  VAL_PU_INIT_ABLITY_PUNCH    , //                                                                           (0)
                  VAL_PU_INIT_ABILITY_GRAB    , //                                                                           (0)
                  VAL_PU_INIT_SPOOGER         , //                                                                           (0)
                  VAL_PU_INIT_GOLDFLAME       , //                                                                           (0)
                  VAL_PU_INIT_TRIGGER         , //                                                                           (0)
                  VAL_PU_INIT_JELLY           , //                                                                           (0)
                  VAL_PU_INIT_EBOLA           , //                                                                           (0)
                  VAL_PU_INIT_RANDOM          , //                                                                           (0)
                  //------------------------------
                  VAL_PU_MAX_BOMB             , //                                                                              8
                  VAL_PU_MAX_FLAME            , //                                                                               8
                  VAL_PU_MAX_DISEASE          , //                     not used                                                0
                  VAL_PU_MAX_ABILITY_KICK     , //                                                                                      4
                  VAL_PU_MAX_EXTRA_SPEED      , //                                                                                     4
                  VAL_PU_MAX_ABILITY_PUNCH    , //                                                                                       1
                  VAL_PU_MAX_ABILITY_GRAB     , //                                                                                      1
                  VAL_PU_MAX_SPOOGER          , //                                                                                 1
                  VAL_PU_MAX_GOLDFLAME        , //                                                                                   1
                  VAL_PU_MAX_TRIGGER          , //                                                                                 1
                  VAL_PU_MAX_JELLY            , //                                                                               1
                  VAL_PU_MAX_EBOLA            , //                 ; not used...                                               0
                  VAL_PU_MAX_RANDOM           , //               ; not used...                                                 0
                  //------------------------------
                  VAL_PU_FIELD_BOMB           , //                                                                                10
                  VAL_PU_FIELD_FLAME          , //                                                                                 10
                  VAL_PU_FIELD_DISEASE        , //                                                                                   3
                  VAL_PU_FIELD_ABILITY_KICK   , //                                                                                        4
                  VAL_PU_FIELD_EXTRA_SPEED    , //                                                                                       8
                  VAL_PU_FIELD_ABLITY_PUNCH   , //                                                                                        2
                  VAL_PU_FIELD_ABILITY_GRAB   , //                                                                                        2
                  VAL_PU_FIELD_SPOOGER        , //                                                                                   1
                  VAL_PU_FIELD_GOLDFLAME      , //                                                                                   -2
                  VAL_PU_FIELD_TRIGGER        , //                                                                                   -4
                  VAL_PU_FIELD_JELLY          , //                                                                                 1
                  VAL_PU_FIELD_EBOLA          , //                                                                                 -4
                  VAL_PU_FIELD_RANDOM         , //                                                                                  -2
                  //------------------------------
                  VAL_DSE_TIME_LIMITED,                // (1)
                  VAL_DSE_MULTIPLY,       // (1)
                  VAL_DSE_MIN_KEEP_BEFORE_PASS,       // (500)
                  VAL_DSE_ARE_CUREABLE,       // (1)
                  VAL_DSE_CURE_CHANCE,       // (10)
                  //------------------------------
                  VAL_DSE_TIME_MOLASSES,       // (15)
                  VAL_DSE_TIME_CRACK,       // (15)
                  VAL_DSE_TIME_CONSTIPATION, // (15)
                  VAL_DSE_TIME_POOPS,       // (15)
                  VAL_DSE_TIME_SHORTFLAME,       // (15)
                  VAL_DSE_TIME_CRACKPOOPS,       // (15)
                  VAL_DSE_TIME_SHORTFUZE,       // (15)
                  VAL_DSE_TIME_SWAP,       // (0)
                  VAL_DSE_TIME_REVERSED,       // (15)
                  VAL_DSE_TIME_LEPROSY,       // (15)
                  VAL_DSE_TIME_INVISIBLE,       // (15)
                  VAL_DSE_TIME_DUDS,       // (15)
                  VAL_DSE_TIME_HYPERSWAP,       // (0)
                  //------------------------------
                  VAL_DSE_PROB_MOLASSES,
                  VAL_DSE_PROB_CRACK,
                  VAL_DSE_PROB_CONSTIPATION,
                  VAL_DSE_PROB_POOPS,
                  VAL_DSE_PROB_SHORTFLAME,
                  VAL_DSE_PROB_CRACKPOOPS,
                  VAL_DSE_PROB_SHORTFUZE,
                  VAL_DSE_PROB_SWAP,
                  VAL_DSE_PROB_REVERSED,
                  VAL_DSE_PROB_LEPROSY,
                  VAL_DSE_PROB_INVISIBLE,
                  VAL_DSE_PROB_DUDS,
                  VAL_DSE_PROB_HYPERSWAP,
                  //------------------------------
                  VAL_COLOR_PLAYER_0R         , //                                                                           255
                  VAL_COLOR_PLAYER_0G         , //                                                                           255
                  VAL_COLOR_PLAYER_0B         , //                                                                           255
                  VAL_COLOR_PLAYER_1R         , //                                                                           50
                  VAL_COLOR_PLAYER_1G         , //                                                                           50
                  VAL_COLOR_PLAYER_1B         , //                                                                           50
                  VAL_COLOR_PLAYER_2R         , //                                                                           255
                  VAL_COLOR_PLAYER_2G         , //                                                                           0
                  VAL_COLOR_PLAYER_2B         , //                                                                           0
                  VAL_COLOR_PLAYER_3R         , //                                                                           0
                  VAL_COLOR_PLAYER_3G         , //                                                                           0
                  VAL_COLOR_PLAYER_3B         , //                                                                           255
                  VAL_COLOR_PLAYER_4R         , //                                                                           0
                  VAL_COLOR_PLAYER_4G         , //                                                                           255
                  VAL_COLOR_PLAYER_4B         , //                                                                           0
                  VAL_COLOR_PLAYER_5R         , //                                                                           255
                  VAL_COLOR_PLAYER_5G         , //                                                                           255
                  VAL_COLOR_PLAYER_5B         , //                                                                           0
                  VAL_COLOR_PLAYER_6R         , //                                                                           0
                  VAL_COLOR_PLAYER_6G         , //                                                                           255
                  VAL_COLOR_PLAYER_6B         , //                                                                           255
                  VAL_COLOR_PLAYER_7R         , //                                                                           255
                  VAL_COLOR_PLAYER_7G         , //                                                                           0
                  VAL_COLOR_PLAYER_7B         , //                                                                           255
                  VAL_COLOR_PLAYER_8R         , //                                                                           255
                  VAL_COLOR_PLAYER_8G         , //                                                                           128
                  VAL_COLOR_PLAYER_8B         , //                                                                           0
                  VAL_COLOR_PLAYER_9R         , //                                                                           128
                  VAL_COLOR_PLAYER_9G         , //                                                                           0
                  VAL_COLOR_PLAYER_9B         , //                                                                           255
                  //---------------------------------------------------------------------------------------------------------------
                  VAL_NUMBER_OF                // xx: this is the number of values
};


#endif // ENUMVALUES_H
