#ifndef ENUMBLOCKS_H
#define ENUMBLOCKS_H

// dependencies: Scheme
/**
 * types of blocks
 */
enum EnumBlocks { BLOCK_BLANK = 0,     // no block
                  BLOCK_BREAKABLE,     // breakable brick
                  BLOCK_SOLID,         // solid brick
                  BLOCK_EXTRA,         // map extra
                  BLOCK_POWERUP,       // powerup
                  BLOCK_BOMB,          // pulsating bomb
                  BLOCK_FLAME          // flame

};

#endif // ENUMBLOCKS_H
