#ifndef ENUMPOWERUPS_H
#define ENUMPOWERUPS_H

// dependencies: Scheme, Powerups
/**
 * types of powerups
 * important: do not change the order of entries! New powerups must be added before PU_NUMBER_OF
 */
enum EnumPowerups { PU_BOMB = 0,
                    PU_FLAME,
                    PU_DISEASE,
                    PU_ABILITY_KICK,
                    PU_EXTRA_SPEED,
                    PU_ABLITY_PUNCH,
                    PU_ABILITY_GRAB,
                    PU_SPOOGER,
                    PU_GOLDFLAME,
                    PU_TRIGGER,
                    PU_JELLY,
                    PU_EBOLA,
                    PU_RANDOM,
                    ///////////////////////////////
                    PU_NUMBER_OF  // this value represents the number of powerups
};

#endif // ENUMPOWERUPS_H
