#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>

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

enum {
    TAB = 9,
    ESC = 27,
    MAX = 999
};


typedef enum {
    STAIR_UP    = 0,
    STAIR_DOWN  = 1
} STAIR;

struct Location {
    unsigned int x      = 0;
    unsigned int y      = 0;
    unsigned int z      = 0;
    unsigned int area   = 0;
    bool operator== (const Location& rhs) { return (rhs.area == area && rhs.x == x && rhs.y == y && rhs.z == z); }
};
    std::ostream& operator<< (std::ostream& out, const Location& loc);

namespace Utility {
    unsigned int randBetween (unsigned int start, unsigned int end);
    bool randChance (unsigned int percentage);
};

#endif