#include "tile.h"

Tile::Tile()
:   m_symbol(' ')
,   m_x (0)
,   m_y (0)
,   m_type (TILE_PLAIN)
{

}

Tile::Tile (char symbol, int x, int y)
: m_symbol (symbol)
, m_x (x)
, m_y (y)
, m_type (TILE_PLAIN)
{

}

Tile::~Tile()
{

}

int Tile::getCost() const {
    switch (m_type) {
        case TILE_PLAIN: return 1;
        case TILE_FORD:  return 1;
        case TILE_HILL:  return 2;
        case TILE_WATER: return 3;
        case TILE_MARSH: return 5;
        case TILE_ROAD:  return 0;
        case TILE_MOUNT: return 9;
    }
    return 1;
}


char Tile::getSymbol () const {
    if (m_type == TILE_MOUNT)   return 'M';
    if (m_type == TILE_WATER)   return '=';
    if (m_type == TILE_HILL)    return '^';
    if (m_type == TILE_MARSH)   return '#';
    if (m_type == TILE_ROAD)    return '-';
    return ' ';
}
