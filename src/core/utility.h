#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <climits>
#include <glog/logging.h>

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
    KEY_TAB 	= 1,
    KEY_ESC 	= 2,
    KEY_ENTER	= 3,
    KEY_UP		= 4,
    KEY_DOWN	= 5,
    KEY_RIGHT	= 6,
    KEY_LEFT	= 7,
    KEY_MAX = 63
};


typedef enum {
    STAIR_UP    = 0,
    STAIR_DOWN  = 1
} STAIR;

// TODO: break this out into proper class

struct Location {

    Location () {}
    Location (unsigned int i_x, unsigned int i_y, unsigned int i_z, unsigned int i_area = 0)
        : x (i_x), y (i_y), z (i_z), area (i_area) {}
    unsigned int x      = UINT_MAX;
    unsigned int y      = UINT_MAX;
    unsigned int z      = UINT_MAX;
    unsigned int area   = 0;
    bool operator== (const Location& rhs) { return (rhs.area == area && rhs.x == x && rhs.y == y && rhs.z == z); }
    bool operator!= (const Location& rhs) { return !(*this == rhs); }
    bool operator< (const Location& rhs) const { 
        if (area > rhs.area) {
            return false;
        } else if (area < rhs.area) {
            return true;
        }
        if (z > rhs.z) {
            return false;
        } else if (z < rhs.z) {
            return true;
        }
        if (y > rhs.y) {
            return false;
        } else if (y < rhs.y) {
            return true;
        }
        if (x > rhs.x) {
            return false;
        } else if (x < rhs.x) {
            return true;
        }
        return false;
    }
    void operator= (const Location& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        area = rhs.area;
    }
};
    std::ostream& operator<< (std::ostream& out, const Location& loc);

namespace Utility {
    unsigned int randBetween (unsigned int start, unsigned int end);
    bool randChance (unsigned int percentage);
};

#endif
