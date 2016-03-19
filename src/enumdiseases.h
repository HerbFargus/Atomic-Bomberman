#ifndef ENUMDISEASES_H
#define ENUMDISEASES_H

enum EnumDiseases { DSE_MOLASSES = 0,      // speed down
                    DSE_CRACK,             // speed up
                    DSE_CONSTIPATION,      // player can't drop bombs
                    DSE_POOPS,             // player drops all bombs he has got
                    DSE_SHORTFLAME,        // flame length = 1
                    DSE_CRACKPOOPS,        // CRACK + POOPS
                    DSE_SHORTFUZE,         // shorter fuze time
                    DSE_SWAP,              // two players swap
                    DSE_REVERSED,          // reversed controls
                    DSE_LEPROSY,           // Lepra ???
                    DSE_INVISIBLE,         // player is invisible
                    DSE_DUDS,              // player drops only duds
                    DSE_HYPERSWAP,         // all players swap
                    ///////////////////////////
                    DSE_NUMBER_OF
};

#endif // ENUMDISEASES_H
