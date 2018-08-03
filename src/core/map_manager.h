#pragma once

#include "area_info.h"
#include "entity.h"
#include "location.h"
#include "tile.h"
#include "utility.h"
#include <map>

typedef std::map<unsigned int, AreaInfo> AreaMap;

class MapManager {
public:
    MapManager() = default;
    virtual ~MapManager() = default;

    bool isValidTile(const Location& location);
    Tile& getTile(const Location& location) {
        return m_areas[location.area].getTile(location);
    }

    /// @brief Creates a new Area with the given dimensions
    /// @details Provide an area ID when loading from file, leave it when
    /// creating
    // @param[in]   width   The map width
    // @param[in]   height  The map height
    // @param[in]   depth   The map depth
    // @param[in]   area    (optional) The AreaId to create
    // @return The ID for this area
    virtual unsigned int createArea(unsigned int width, unsigned int height,
                                    unsigned int depth);

    /// @brief Adds the given area to the map with the specified ID
    /// @param[in] area The area to add
    /// @param[in] id The id to assign to the area
    /// @return The ID for this area (0 on failure)
    virtual unsigned int addArea(const AreaInfo& area, unsigned int id = 0);

    AreaMap& getAreas() { return m_areas; }

    Location location(const Location&, Direction direction);
    EntityHolder findEntitiesAt(const Location& location);
    EntityHolder findEntitiesNear(const Location& location,
                                  unsigned int radius);

private:
    unsigned int m_maxAreaId = 0;
    AreaMap m_areas;
};
