#include "map_manager.h"

void MapManager::resetMap (unsigned int width, unsigned int height, unsigned int depth)
{
    m_mapWidth = width;
    m_mapHeight = height;
    m_mapDepth = depth;

    if (m_map) delete[] m_map;
    m_map = new Tile[m_mapWidth*m_mapHeight*m_mapDepth];

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
    x = index%m_mapWidth;
    y = (index-x)/m_mapHeight;
    z = (index-(y*m_mapWidth)+x) / (m_mapHeight*m_mapWidth) + 1;
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
