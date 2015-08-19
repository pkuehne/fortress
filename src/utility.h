#ifndef UTILITY_H
#define UTILITY_H

typedef unsigned short DIRECTION;
namespace Direction {
    const DIRECTION None        = 0;
    const DIRECTION North       = 1;
    const DIRECTION East        = 2;
    const DIRECTION South       = 3;
    const DIRECTION West        = 4;
    const DIRECTION NorthEast   = 5;
    const DIRECTION SouthEast   = 6;
    const DIRECTION SouthWest   = 7;
    const DIRECTION NorthWest   = 8;

}

typedef enum {
    STAIR_UP    = 0,
    STAIR_DOWN  = 1
} STAIR;

namespace Utility {
};

#endif
