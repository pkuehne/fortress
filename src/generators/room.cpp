#include "room.h"

/// This function is expected to reciprocal. i.e. if A intersects B,
/// then B intersects A
bool Room::intersect(const Room& other) {
    if (other.getLeft() > getRight() || getLeft() > other.getRight()) {
        return false;
    }
    if (other.getTop() > getBottom() || getTop() > other.getBottom()) {
        return false;
    }
    return true;
}

/// The function will execute the callback exactly once for each wall,
/// regardless of whether this is a standard wall or a corner
/// @note The callback is not guaranteed to execute in any particular order
void Room::walkWalls(
    std::function<void(unsigned int x, unsigned int y)> callback) {
    for (unsigned int xx = getLeft(); xx <= getRight(); xx++) {
        callback(xx, getTop());
        callback(xx, getBottom());
    }
    // Don't walk the Top and Bottom again
    for (unsigned int yy = getTop() + 1; yy < getBottom(); yy++) {
        callback(getLeft(), yy);
        callback(getRight(), yy);
    }
}
