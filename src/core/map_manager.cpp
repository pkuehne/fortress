#include "map_manager.h"
#include "location.h"
#include <glog/logging.h>

unsigned int MapManager::createArea(unsigned int width, unsigned int height,
                                    unsigned int depth, unsigned int area) {
    if (width == 0 || height == 0 || depth == 0) {
        LOG(ERROR) << "Cannot reset map with 0 values" << std::endl;
        exit(1);
    }

    if (area == 0)
        area = ++m_maxAreaId;
    if (area > m_maxAreaId)
        m_maxAreaId = area;

    auto existing = m_areas.find(area);
    if (existing != m_areas.end())
        m_areas.erase(existing);

    AreaInfo info;
    info.setSize(width, height, depth);

    m_areas[area] = info;
    setArea(area);
    LOG(INFO) << "Created area " << area << std::endl;

    return area;
}

bool MapManager::isValidTile(const Location& loc) {
    if (!loc.area) {
        LOG(ERROR) << "Called isValidTile with zero area" << std::endl;
    }
    bool xValid = (loc.x < m_areas[m_currentArea].getWidth());
    bool yValid = (loc.y < m_areas[m_currentArea].getHeight());
    bool zValid = (loc.z < m_areas[m_currentArea].getDepth());
    return (xValid && yValid && zValid);
}

EntityHolder MapManager::findEntitiesAt(const Location& location) {
    return findEntitiesNear(location, 0);
}

EntityHolder MapManager::findEntitiesNear(const Location& location,
                                          unsigned radius) {
    EntityHolder l_entities;

    int startx = location.x - radius;
    int starty = location.y - radius;
    int endx = location.x + radius;
    int endy = location.y + radius;

    for (int yy = starty; yy <= endy; yy++) {
        for (int xx = startx; xx <= endx; xx++) {
            Location loc(xx, yy, location.z, location.area);
            if (!isValidTile(loc))
                continue;
            for (EntityId id : getTile(loc).entities()) {
                l_entities.insert(id);
            }
        }
    }
    return l_entities;
}

void MapManager::setArea(unsigned int area) {
    // std::cout << "Setting area to " << area << std::endl;
    auto info = m_areas.find(area);
    if (info == m_areas.end()) {
        LOG(ERROR) << "Could not set area " << area
                   << " because it doesn't exist!" << std::endl;
        throw std::string("Invalid area set!");
    }
    m_currentArea = area;
}

Location MapManager::location(const Location& loc, Direction dir) {
    Location retval(loc);
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

    if (!isValidTile(retval)) {
        return loc; // Don't return a bad location
    }
    return retval;
}
