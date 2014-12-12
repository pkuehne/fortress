#include "tile.h"

Tile::Tile()
:   m_x (0)
,   m_y (0)
,   m_background (TILE_PLAIN)
,   m_construction (CON_EMPTY)
{

}

Tile::Tile (TILE bg, int x, int y)
: m_x (x)
, m_y (y) 
, m_background (bg)
, m_construction (CON_EMPTY)
{

}

Tile::~Tile()
{

}

int Tile::getCost() const {
    switch (m_background) {
        case TILE_PLAIN: return 1;
        case TILE_WATER: return 3;
        case TILE_MAX: return 9999999;
    }
    return 1;
}

int Tile::getUnitPathCost() const {
    if (m_construction != CON_EMPTY) return -1;    
    if (m_background == TILE_PLAIN) return 1;
    if (m_background == TILE_WATER) return 3;
    return -1;
}
