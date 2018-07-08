#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "area_info.h"
#include "entity.h"
#include "location.h"
#include "tile.h"
#include "utility.h"
#include <map>

typedef std::map<unsigned int, AreaInfo> AreaMap;

class MapManager {
public:
    bool isValidTile(const Location& location);
    Tile& getTile(const Location& location) {
        return m_areas[location.area].getTile(location);
    }

    unsigned int getMapHeight() { return m_areas[m_currentArea].getHeight(); }
    unsigned int getMapWidth() { return m_areas[m_currentArea].getWidth(); }
    unsigned int getMapDepth() { return m_areas[m_currentArea].getDepth(); }

    /// @brief Creates a new Area with the given dimensions
    /// @details Provide an area ID when loading from file, leave it when
    /// creating
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
    unsigned int m_currentArea = 0;
    unsigned int m_maxAreaId = 0;
    AreaMap m_areas;
};

#endif
