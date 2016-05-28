#ifndef UTILITY_H
#define UTILITY_H


enum class Direction {
    None        = 0,
    North       = 1,
    East        = 2,
    South       = 3,
    West        = 4,
    NorthEast   = 5,
    SouthEast   = 6,
    SouthWest   = 7,
    NorthWest   = 8
};

enum {
    KEY_TAB 	    = 1,
    KEY_ESC 	    = 2,
    KEY_ENTER	    = 3,
    KEY_UP	    = 4,
    KEY_DOWN	    = 5,
    KEY_RIGHT	    = 6,
    KEY_LEFT	    = 7,
    KEY_BACKSPACE   = 8,
    KEY_MAX = 63
};


typedef enum {
    STAIR_UP    = 0,
    STAIR_DOWN  = 1
} STAIR;

namespace Utility {
    unsigned int randBetween (unsigned int start, unsigned int end);
    bool randChance (unsigned int percentage);
};

#endif
