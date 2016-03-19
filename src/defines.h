// v0.1  by gm (created)
// v0.2  by gm (all #define replaced by static const ...)
// v0.3  by gm (MAX_MAPS added)
// v0.35 by gm (commentary added, EnumBlocks extended)
// v0.36 by gm (more BLOCKS_ added)
// v0.4  by gm (removed some entries, improved some enums)
// v0.41 by dh (new: EnumChoice)
// v0.5  by gm (enum*.h created to reduce compilation dependencies)

#ifndef DEFINES_H
#define DEFINES_H

// dependencies: Scheme
/**
 * number of tiles in one line of the field
 */
static const int FIELD_WIDTH =  15;


// dependencies: Scheme
/**
 * number of tiles in one column of the field
 */
static const int FIELD_HEIGHT =  11;


// dependencies: Scheme
/**
 * maximum number of players playing simultanously
 */
static const int  MAX_PLAYERS =  10;


#endif // DEFINES_H
