#pragma once

#include <climits>
#include <ostream>

class Location {
public:
    Location() {}
    Location(unsigned int i_x, unsigned int i_y, unsigned int i_z,
             unsigned int i_area = 0)
        : x(i_x), y(i_y), z(i_z), area(i_area) {}
    bool operator==(const Location& rhs) const;
    bool operator!=(const Location& rhs) const;
    bool operator<(const Location& rhs) const;
    Location& operator=(const Location& rhs);
    bool isValid() const {
        return (x != UINT_MAX && y != UINT_MAX && z != UINT_MAX);
    }

public:
    unsigned int x = UINT_MAX;
    unsigned int y = UINT_MAX;
    unsigned int z = UINT_MAX;
    unsigned int area = 0;
};

std::ostream& operator<<(std::ostream& out, const Location& loc);

