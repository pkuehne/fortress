#ifndef GENERATOR_H
#define GENERATOR_H

#include "generator_interface.h"
#include <vector>

class DungeonGenerator : public GeneratorInterface {
public:
    bool generate();
    void reset();
    unsigned int& numberOfRooms() { return m_roomTarget; }
    unsigned int& currentLevel() { return m_level; }
    unsigned int& upStairTarget() { return m_upStairTarget; }
    unsigned int& downStairTarget() { return m_downStairTarget; }
    unsigned int& upStairLink() { return m_upStairLink; }
    unsigned int& downStairLink() { return m_downStairLink; }

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
    bool generateRoom ();
    void connectRooms (Room& start, Room& end);
    void placeUpStair();
    void placeDownStair();
    void placeOrcs();
    void loadMap ();
    unsigned char wallSprite (unsigned int x, unsigned int y);

private:
    unsigned int            m_roomTarget;
    unsigned int            m_startRoom;
    unsigned int            m_level;
    unsigned int            m_upStairTarget;
    unsigned int            m_downStairTarget;
    unsigned int            m_upStairLink;
    unsigned int            m_downStairLink;
    std::vector<Room>       m_rooms;
};

#endif
