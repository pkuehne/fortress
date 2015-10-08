#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "map_manager_interface.h"
#include "game_engine_interface.h"
#include <vector>

struct MapInfo {
    unsigned int    areaId;
    Tile*           mapData;
    unsigned int    height;
    unsigned int    width;
    unsigned int    depth;
    friend bool operator< (const MapInfo& lhs, const MapInfo& rhs) { return lhs.areaId < rhs.areaId; }
};


class MapManager : public MapManagerInterface {
public:

    void initialise (GameEngineInterface* engine) { m_engine = engine; }
    Tile& getTile (unsigned int x, unsigned int y, unsigned int z) { return getTile (map2index (x, y, z)); }
    Tile& getTile (const Location& location) { return getTile (location.x, location.y, location.z); }
    Tile& getTile (unsigned int index) { return m_map[index]; }

    int map2index (unsigned int x, unsigned int y, unsigned int z);
    int map2index (const Location& location) { return map2index (location.x, location.y, location.z); }
    void index2map (unsigned int index, unsigned int& x, unsigned int& y, unsigned int& z);
    void index2map (unsigned int index, Location& location);

    bool isValidTile (Location& location);
    bool isValidTile (unsigned int x, unsigned int y, unsigned int z);
    bool isValidTile (unsigned int index);

    unsigned int getMapHeight() { return m_mapHeight; }
    unsigned int getMapWidth() { return m_mapWidth; }
    unsigned int getMapDepth () { return m_mapDepth; }

    virtual void resetMap (unsigned int width, unsigned int height, unsigned int depth);

    unsigned int getArea () { return m_currentArea; }
    void setArea (unsigned int area);

    EntityHolder findEntitiesAt (const Location& location);
    EntityHolder findEntitiesNear (const Location& location, unsigned int radius);

private:
    GameEngineInterface*    m_engine;
    unsigned int            m_mapWidth;
    unsigned int            m_mapHeight;
    unsigned int            m_mapDepth;
    Tile*                   m_map;
    unsigned int            m_currentArea;
    std::vector<MapInfo> m_areas;
};

#endif
