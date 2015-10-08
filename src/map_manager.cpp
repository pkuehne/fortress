#include "map_manager.h"

void MapManager::resetMap (unsigned int width, unsigned int height, unsigned int depth)
{
    std::cout << "Resetting Area " << m_currentArea << std::endl;

    auto existing = m_areas.begin ();
    for (; existing != m_areas.end(); existing++) {
        if (existing->areaId == m_currentArea) {
            if (existing->mapData) delete[] existing->mapData;
            m_areas.erase(existing);
            break;
        }
    }

    MapInfo info;
    info.areaId = m_currentArea;
    info.mapData = new Tile[width*height*depth];
    info.height = height;
    info.width  = width;
    info.depth  = depth;

    m_areas.push_back (info);
    setArea (m_currentArea);
}

bool MapManager::isValidTile (unsigned int x, unsigned int y, unsigned int z)
{
    bool xValid = (x>=0 && x<m_mapWidth);
    bool yValid = (y>=0 && y<m_mapHeight);
    bool zValid = (z>0 && z<=m_mapDepth);
    return ( xValid && yValid && zValid );
}

bool MapManager::isValidTile (unsigned int index)
{
    return (index > 0 && index < sizeof (m_map));
}

bool MapManager::isValidTile (Location& location)
{
    return isValidTile (location.x, location.y, location.z);
}

int MapManager::map2index (unsigned int x, unsigned int y, unsigned int z)
{
    return ((z - 1) * m_mapHeight * m_mapWidth) + (y * m_mapHeight) + x;
}

void MapManager::index2map (unsigned int index, unsigned int& x, unsigned int& y, unsigned int& z)
{
    x = index % m_mapWidth;
    y = (index - x) / m_mapWidth % m_mapHeight;
    z = (index - (y * m_mapWidth) + x) / (m_mapHeight * m_mapWidth) + 1;
}
void MapManager::index2map (unsigned int index, Location& location)
{
    return index2map (index, location.x, location.y, location.z);
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
            for (EntityId id : m_engine->getMap()->getTile (xx, yy, m_engine->getLevel()).entities) {
                l_entities.insert (id);
            }
        }
    }
    return l_entities;
}

void MapManager::setArea (unsigned int area)
{
    std::cout << "Setting area " << area << std::endl;

    m_currentArea   = area;
    m_map           = nullptr;
    m_mapHeight     = 0;
    m_mapWidth      = 0;
    m_mapDepth      = 0;

    for (MapInfo info : m_areas) {
        if (info.areaId == area) {
            std::cout << "Found area!" << std::endl;
            m_map       = info.mapData;
            m_mapHeight = info.height;
            m_mapWidth  = info.width;
            m_mapDepth  = info.depth;
        }
    }
    std::cout << "Setting area done" << std::endl;
}
