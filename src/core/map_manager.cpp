#include "map_manager.h"
#include "location.h"
#include <glog/logging.h>

unsigned int MapManager::createArea (   unsigned int width,
                                        unsigned int height,
                                        unsigned int depth,
                                        unsigned int area)
{
    if (width == 0 || height == 0 || depth == 0) {
        LOG(ERROR) << "Cannot reset map with 0 values" << std::endl;
        exit (1);
    }

    if (area == 0) area = ++m_maxAreaId;
    if (area > m_maxAreaId) m_maxAreaId = area;

    auto existing = m_areas.find (area);
    if (existing != m_areas.end()) m_areas.erase (existing);

    MapInfo info;
    info.areaId = area;
    info.mapData = new Tile[width*height*depth];
    info.height = height;
    info.width  = width;
    info.depth  = depth;

    m_areas[info.areaId] = info;
    setArea (area);
    LOG(INFO) << "Created area " << info.areaId << std::endl;

    return area;
}

bool MapManager::isValidTile (const Location& loc)
{
    if (!loc.area) {
        LOG(ERROR) << "Called isValidTile with zero area" << std::endl;
    }
    bool xValid = (loc.x<m_mapWidth);
    bool yValid = (loc.y<m_mapHeight);
    bool zValid = (loc.z<m_mapDepth);
    return ( xValid && yValid && zValid );
}

unsigned int MapManager::loc2index (const Location& loc)
{
    return (loc.z * m_mapHeight * m_mapWidth) + (loc.y * m_mapHeight) + loc.x;
}

EntityHolder MapManager::findEntitiesAt (const Location& location)
{
    return findEntitiesNear (location, 0);
}

EntityHolder MapManager::findEntitiesNear (const Location& location, unsigned radius)
{
    EntityHolder l_entities;

    int startx = location.x - radius;
    int starty = location.y - radius;
    int endx = location.x + radius;
    int endy = location.y + radius;

    for (int yy = starty; yy <= endy; yy++) {
        for (int xx = startx; xx <= endx; xx++) {
            Location loc(xx, yy, location.z, location.area);
            if (!isValidTile(loc)) continue;
            for (EntityId id : getTile (loc).entities()) {
                l_entities.insert (id);
            }
        }
    }
    return l_entities;
}

void MapManager::setArea (unsigned int area)
{
    //std::cout << "Setting area to " << area << std::endl;
    m_currentArea   = area;
    m_map           = nullptr;
    m_mapHeight     = 0;
    m_mapWidth      = 0;
    m_mapDepth      = 0;

    auto info = m_areas.find (area);
    if (info != m_areas.end()) {
        m_map       = info->second.mapData;
        m_mapHeight = info->second.height;
        m_mapWidth  = info->second.width;
        m_mapDepth  = info->second.depth;
        return;
    }

    LOG (ERROR) << "Could not set area " << area << " because it doesn't exist!" << std::endl;
    throw int(1);
}

Location MapManager::location (const Location& loc, Direction dir)
{
    Location retval (loc);
    switch (dir) {
        case Direction::North:
            retval.y--;
            break;
        case Direction::South:
            retval.y++;
            break;
        case Direction::East:
            retval.x++;
            break;
        case Direction::West:
            retval.x--;
            break;
        default:
            break;
    };

    if (!isValidTile (retval)) {
        return loc; // Don't return a bad location
    }
    return retval;
}
