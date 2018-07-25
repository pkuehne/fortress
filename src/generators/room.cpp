#include "room.h"

bool Room::isValid(unsigned int mapWidth, unsigned int mapHeight) {
    return getRight() < mapWidth && getBottom() < mapHeight;
}

bool Room::isInRoom(unsigned int x, unsigned int y) {
    return x >= getLeft() && x <= getRight() && y >= getTop() &&
           y <= getBottom();
}

bool Room::isInterior(unsigned int x, unsigned int y) {
    return x > getLeft() && x < getRight() && y > getTop() && y < getBottom();
}

/// This function is expected to reciprocal. i.e. if A intersects B,
/// then B intersects A
bool Room::intersect(const Room& other) { return intersectWithin(other, 0); }

/// This function is expected to reciprocal. i.e. if A intersects B,
/// then B intersects A.
/// The distance is a radius by which the current room effectively grows.
/// To simulate an exclusion zone for both rooms, double the distance when
/// calling.
bool Room::intersectWithin(const Room& other, unsigned int distance) {
    if (other.getLeft() > getRight() + distance ||
        getLeft() > other.getRight() + distance) {
        return false;
    }
    if (other.getTop() > getBottom() + distance ||
        getTop() > other.getBottom() + distance) {
        return false;
    }
    return true;
}

/// The function will execute the callback exactly once for each wall,
/// regardless of whether this is a standard wall or a corner
/// @note The callback is not guaranteed to execute in any particular order
void Room::walkWalls(WalkCallback callback) {
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

/// The function will execute the callback exactly once for each cell
/// that is within distance from the room, including every cell of the room
/// itself.
/// @note The callback is not guaranteed to execute in any particular order
void Room::walkWithin(WalkCallback callback, unsigned int distance) {
    unsigned int top = getTop() > distance ? getTop() - distance : 0;
    unsigned int left = getLeft() > distance ? getLeft() - distance : 0;

    for (unsigned int yy = top; yy <= getBottom() + distance; yy++) {
        for (unsigned int xx = left; xx <= getRight() + distance; xx++) {
            callback(xx, yy);
        }
    }
}
