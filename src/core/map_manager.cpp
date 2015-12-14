#include "map_manager.h"

void MapManager::resetMap (unsigned int area, unsigned int width, unsigned int height, unsigned int depth)
{
	if (width == 0 || height == 0 || depth == 0) {
		LOG(ERROR) << "Cannot reset map with 0 values" << std::endl;
		exit (1);
	}
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
}

bool MapManager::isValidTile (unsigned int x, unsigned int y, unsigned int z)
{
    bool xValid = (x>=0 && x<m_mapWidth);
    bool yValid = (y>=0 && y<m_mapHeight);
    bool zValid = (z>=0 && z<m_mapDepth);
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
    return (z * m_mapHeight * m_mapWidth) + (y * m_mapHeight) + x;
}

void MapManager::index2map (unsigned int index, unsigned int& x, unsigned int& y, unsigned int& z)
{
    x = index % m_mapWidth;
    y = (index - x) / m_mapWidth % m_mapHeight;
    z = (index - (y * m_mapWidth) + x) / (m_mapHeight * m_mapWidth);
}
void MapManager::index2map (unsigned int index, Location& location)
{
    location.area = getArea();
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
            for (EntityId id : m_engine->getMap()->getTile (xx, yy, location.z).entities()) {
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
    //exit (1);
}
