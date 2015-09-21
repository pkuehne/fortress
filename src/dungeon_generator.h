#ifndef GENERATOR_H
#define GENERATOR_H

#include "generator_interface.h"
#include <vector>

class DungeonGenerator : public GeneratorInterface {
public:
    void initialise (GameEngineInterface* a_engine) { m_engine = a_engine; }
    bool generate();

    unsigned int& mapHeight() { return m_mapHeight; }
    unsigned int& mapWidth() { return m_mapWidth; }
    unsigned int& numberOfRooms() { return m_roomTarget; }
    unsigned int& currentLevel() { return m_level; }

    unsigned char& getByCoordinate (unsigned int x, unsigned int y) { return getByIndex (CoordToIndex(x,y)); }
    unsigned char& getByIndex (unsigned int index) { return m_map[index]; }
    bool isValidIndex (unsigned int index) { return (index > 0 && index < sizeof (m_map)); }
    bool isValidCoordinate (unsigned int x, unsigned int y) { return (x>=0 && x<m_mapWidth && y>=0 && y<m_mapHeight); }
    int CoordToIndex (unsigned int x, unsigned int y) { return y * m_mapWidth + x; }
    void IndexToCoord (unsigned int index, unsigned int& x, unsigned int& y) { x = index%m_mapWidth; y = (index-x)/m_mapWidth; }

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
    void reset();
    void loadMap ();
    unsigned char wallSprite (unsigned int x, unsigned int y);

private:
    GameEngineInterface*    m_engine;
    unsigned int            m_mapHeight;
    unsigned int            m_mapWidth;
    unsigned int            m_roomTarget;
    unsigned char*          m_map;
    unsigned int            m_startRoom;
    unsigned int            m_level;
    std::vector<Room>       m_rooms;
};

#endif
