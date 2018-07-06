#include "location.h"

bool Location::operator==(const Location& rhs) const {
    return (rhs.area == area && rhs.x == x && rhs.y == y && rhs.z == z);
}

bool Location::operator!=(const Location& rhs) const { return !(*this == rhs); }

bool Location::operator<(const Location& rhs) const {
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
Location& Location::operator=(const Location& rhs) {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    area = rhs.area;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Location& loc) {
    out << "(" << loc.area << ":" << loc.x << "," << loc.y << "," << loc.z
        << ")";
    return out;
}
