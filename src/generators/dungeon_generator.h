#ifndef GENERATOR_H
#define GENERATOR_H

#include "generator_interface.h"
#include <vector>

class Location;

class DungeonGenerator : public GeneratorInterface {
public:
    DungeonGenerator() = default;
    virtual ~DungeonGenerator() = default;

    bool generate();
    void reset();
    unsigned int& numberOfRooms() { return m_roomTarget; }
    unsigned int& maxDepth() { return m_maxDepth; }
    unsigned int& upStairTarget() { return m_upStairTarget; }
    unsigned int& downStairTarget() { return m_downStairTarget; }
    unsigned int& upStairLink() { return m_upStairLink; }
    unsigned int& downStairLink() { return m_downStairLink; }
    bool& createBoss() { return m_createBoss; }

private:
    struct Room {
        unsigned int x;
        unsigned int y;
        unsigned int width;
        unsigned int height;
        unsigned int midX;
        unsigned int midY;
        unsigned int index;
    };

private:
    void createEntitiesFromMap();
    void createEntity(const Location& location);
    void connectStairs();
    bool generateRoom();
    bool generateLevel();
    void connectRooms(Room& start, Room& end);
    void placeUpStair();
    void placeDownStair();
    void placeOrcs();
    void placeItems();
    void placeItem(const Location& location);
    unsigned char wallSprite(unsigned int x, unsigned int y);
    bool validateRoom(unsigned int width, unsigned int height,
                      unsigned int left, unsigned int top);

private:
    unsigned int m_roomTarget = 1;
    unsigned int m_startRoom = 0;
    unsigned int m_level = 1;
    unsigned int m_maxDepth = 1;
    unsigned int m_upStairTarget = 0;
    unsigned int m_downStairTarget = 0;
    unsigned int m_upStairLink = 0;
    unsigned int m_downStairLink = 0;
    unsigned int m_prevDownStair = 0;
    unsigned int m_downStair = 0;
    unsigned int m_upStair = 0;
    std::vector<Room> m_rooms;
    bool m_createBoss = false;
};

#endif
