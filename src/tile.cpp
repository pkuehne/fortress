#include "tile.h"

Tile::Tile()
: m_x (0)
, m_y (0)
, m_background (TILE_PLAIN)
, m_construction (CON_EMPTY)
, m_unit (0)
{

}

Tile::Tile (TILE bg, int x, int y)
: m_x (x)
, m_y (y) 
, m_background (bg)
, m_construction (CON_EMPTY)
, m_unit (0)
{

}

Tile::~Tile()
{

}

