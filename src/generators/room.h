#pragma once
#include <functional>

typedef std::function<void(unsigned int x, unsigned int y)> WalkCallback;

/// @brief An abstract representation of a room with utility functions
class Room {
public:
    Room() = default;
    Room(unsigned int x, unsigned int y, unsigned int width,
         unsigned int height)
        : m_x(x), m_y(y), m_width(width), m_height(height) {}
    ~Room() = default;

    unsigned int getX() const { return m_x; }
    unsigned int getY() const { return m_y; }
    unsigned int getWidth() const { return m_width; }
    unsigned int getHeight() const { return m_height; }
    unsigned int getInnerWidth() const { return m_width < 2 ? 0 : m_width - 2; }
    unsigned int getInnerHeight() const {
        return m_height < 2 ? 0 : m_height - 2;
    }
    unsigned int getMidX() const { return m_x + m_width / 2; }
    unsigned int getMidY() const { return m_y + m_height / 2; }

    unsigned int getLeft() const { return m_x; }
    unsigned int getRight() const {
        return m_width < 1 ? 0 : m_x + m_width - 1;
    }
    unsigned int getTop() const { return m_y; }
    unsigned int getBottom() const {
        return m_height < 1 ? 0 : m_y + m_height - 1;
    }

    /// @brief Validates that the room fits onto the map
    /// @param[in] mapWidth The width of the map to check against
    /// @param[in] mapHeight The height of the map to check against
    bool isValid(unsigned int mapWidth, unsigned int mapHeight);

    /// @brief Is the selected point part of the room as a whole?
    /// @param[in] x The X coordinate
    /// @param[in] x The y coordinate
    bool isInRoom(unsigned int x, unsigned int y);

    /// @brief Is the selected point inside the walls of this room?
    /// @param[in] x The X coordinate
    /// @param[in] x The y coordinate
    bool isInterior(unsigned int x, unsigned int y);

    bool isWall(unsigned int x, unsigned int y) {
        return isInRoom(x, y) && !isInterior(x, y);
    }

    bool isTopLeftCorner(unsigned int x, unsigned int y) {
        return x == getLeft() && y == getTop();
    }
    bool isTopRightCorner(unsigned int x, unsigned int y) {
        return x == getRight() && y == getTop();
    }
    bool isBottomLeftCorner(unsigned int x, unsigned int y) {
        return x == getLeft() && y == getBottom();
    }
    bool isBottomRightCorner(unsigned int x, unsigned int y) {
        return x == getRight() && y == getBottom();
    }

    bool isCorner(unsigned int x, unsigned int y) {
        return isTopRightCorner(x, y) || isTopLeftCorner(x, y) ||
               isBottomRightCorner(x, y) || isBottomLeftCorner(x, y);
    }

    /// @brief checks whether this room intersects another room
    /// @param[in] other The other room to check against
    bool intersect(const Room& other);

    /// @brief checks whether this room intersects another room
    /// within a given number of tiles
    /// @param[in] other The other room to check against
    /// @param[in] distance The 'radius' to extend
    bool intersectWithin(const Room& other, unsigned int distance);

    /// @brief Execute callback function for each wall of the room
    /// @param[in] callback The callback to execute
    void walkWalls(WalkCallback callback);

    /// @brief Execute callback function for every cell within distance
    /// @param[in] callback The callback to execute
    /// @param[in] distance The distance around the room
    void walkWithin(WalkCallback callback, unsigned int distance);

private:
    unsigned int m_x = 0;
    unsigned int m_y = 0;
    unsigned int m_width = 0;
    unsigned int m_height = 0;
};
