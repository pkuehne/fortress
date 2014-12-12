#include "map.h"
#include "tile.h"

const int Map::xAdj[] = {1, 0, -1, 0};
const int Map::yAdj[] = {0, 1, 0, -1};
//const int Map::xAdj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
//const int Map::yAdj[] = {1, 1, 1, 0, 0, -1, -1, -1};
const int Map::dir = sizeof(xAdj) / sizeof(xAdj[0]);

Map::Map ()
: m_tiles (0)
{
    TILE type = TILE_PLAIN;
    m_tiles = new Tile[MAP_WIDTH * MAP_HEIGHT];
    for (int hh = 1; hh <= MAP_HEIGHT; hh++)
    {
        for (int ww = 1; ww <= MAP_WIDTH; ww++)
        {
            if (hh == 1 || hh == MAP_HEIGHT ||
                ww == 1 || ww == MAP_WIDTH) {
                type = TILE_WATER;
            } else {
                type = TILE_PLAIN;
            }
            Tile l_tile (type, ww, hh);
            
            if (((hh == 5 || hh == 9) && (ww > 5 && ww < 13)) ||
                ((ww == 6 || ww == 12) && (hh > 4 && hh < 10)))
            {
                if (!(ww == 9 && hh == 5))
                    l_tile.setConstruction (CON_WALL);
            }


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

void Map::getNeighbours (int index, int neighbours[4]) const
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
        neighbours[ii] = newi;
    }
}
