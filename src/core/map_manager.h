#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "map_manager_interface.h"
#include <map>

class Location;

struct MapInfo {
    unsigned int    areaId;
    Tile*           mapData;
    unsigned int    height;
    unsigned int    width;
    unsigned int    depth;
    friend bool operator< (const MapInfo& lhs, const MapInfo& rhs) { return lhs.areaId < rhs.areaId; }
};


class MapManager : public MapManagerInterface {
private:
    unsigned int loc2index (const Location& loc);
public:

    bool isValidTile (const Location& location);
    Tile& getTile (const Location& location) { return m_map[loc2index(location)]; }

    unsigned int getMapHeight() { return m_mapHeight; }
    unsigned int getMapWidth() { return m_mapWidth; }
    unsigned int getMapDepth () { return m_mapDepth; }

    virtual void resetMap (unsigned int area, unsigned int width, unsigned int height, unsigned int depth);

    unsigned int getArea () { return m_currentArea; }
    void setArea (unsigned int area);
    unsigned int getAreas() { return m_areas.size(); }

    Location location (const Location&, Direction direction);
    EntityHolder findEntitiesAt (const Location& location);
    EntityHolder findEntitiesNear (const Location& location, unsigned int radius);

private:
    unsigned int            m_mapWidth;
    unsigned int            m_mapHeight;
    unsigned int            m_mapDepth;
    Tile*                   m_map;
    unsigned int            m_currentArea;
    std::map<unsigned int, MapInfo> m_areas;
};

#endif
