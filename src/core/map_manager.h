#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "entity.h"
#include "tile.h"
#include "utility.h"
#include <map>

class Location;

struct MapInfo {
    unsigned int areaId;
    Tile* mapData;
    unsigned int height;
    unsigned int width;
    unsigned int depth;
    friend bool operator<(const MapInfo& lhs, const MapInfo& rhs) {
        return lhs.areaId < rhs.areaId;
    }
};

typedef std::map<unsigned int, MapInfo> AreaMap;

class MapManager {
private:
    unsigned int loc2index(const Location& loc);

public:
    bool isValidTile(const Location& location);
    Tile& getTile(const Location& location) {
        return m_map[loc2index(location)];
    }

    unsigned int getMapHeight() { return m_mapHeight; }
    unsigned int getMapWidth() { return m_mapWidth; }
    unsigned int getMapDepth() { return m_mapDepth; }

    /// @brief Creates a new Area with the given dimensions
    // @param[in]   width   The map width
    // @param[in]   height  The map height
    // @param[in]   depth   The map depth
    // @param[in]   area    (optional) The AreaId to create
    // @return The ID for this area
    virtual unsigned int createArea(unsigned int width, unsigned int height,
                                    unsigned int depth, unsigned int area = 0);

    unsigned int getArea() { return m_currentArea; }
    void setArea(unsigned int area);
    AreaMap& getAreas() { return m_areas; }

    Location location(const Location&, Direction direction);
    EntityHolder findEntitiesAt(const Location& location);
    EntityHolder findEntitiesNear(const Location& location,
                                  unsigned int radius);

private:
    unsigned int m_mapWidth = 0;
    unsigned int m_mapHeight = 0;
    unsigned int m_mapDepth = 0;
    Tile* m_map = nullptr;
    unsigned int m_currentArea = 0;
    unsigned int m_maxAreaId = 0;
    AreaMap m_areas;
};

#endif
