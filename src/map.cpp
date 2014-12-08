#include "map.h"

const int Map::xAdj[] = {1, 0, -1, 0};
const int Map::yAdj[] = {0, 1, 0, -1};
//const int Map::xAdj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
//const int Map::yAdj[] = {1, 1, 1, 0, 0, -1, -1, -1};
const int Map::dir = sizeof(xAdj) / sizeof(xAdj[0]);

Map::Map ()
: m_tiles (0)
{
    m_tiles = new Tile[MAP_WIDTH * MAP_HEIGHT];
    for (int hh = 1; hh <= MAP_HEIGHT; hh++)
    {
        for (int ww = 1; ww <= MAP_WIDTH; ww++)
        {
            Tile l_tile (46, ww, hh);
            m_tiles[getIndex (ww, hh)] = l_tile;
        }
    }
}

Map::~Map()
{
    //delete[] m_tiles;
}

int Map::getIndex (int x, int y)
{
    return ((y - 1) * MAP_WIDTH) + (x - 1);
}

Tile& Map::getTile (int x, int y) 
{
    return m_tiles[getIndex(x, y)];
}

Tile& Map::getTile (int index) 
{
    return m_tiles[index];
}

const Tile& Map::getTile (int x, int y) const
{
    return m_tiles[getIndex(x, y)];
}

const Tile& Map::getTile (int index) const
{
    return m_tiles[index];
}

void Map::getNeighbours (int index, int neighbours[4]) 
{
    int x = m_tiles[index].getX();
    int y = m_tiles[index].getY();

    for (int ii = 0; ii < Map::getDirections(); ii++) {
        neighbours[ii] = -1; // Initialize
        int newx = x + Map::getxAdj(ii);
        int newy = y + Map::getyAdj(ii);
        int newi = getIndex (newx, newy);

        // Check boundaries
        if (newx > MAP_WIDTH || newx < 1 ||
            newy > MAP_HEIGHT || newy < 1) {
            continue;
        }
        if (m_tiles[newi].isBlocked()) {
            continue;
        }
        neighbours[ii] = newi;
    }
}
