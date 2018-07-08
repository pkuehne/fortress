#pragma once

#include "location.h"
#include "tile.h"
#include <vector>

class AreaInfo {
public:
    AreaInfo() {}

    void setSize(unsigned int width, unsigned int height, unsigned int depth);
    unsigned int getHeight() const { return m_height; }
    unsigned int getWidth() const { return m_width; }
    unsigned int getDepth() const { return m_depth; }

    Tile& getTile(const Location& loc);

    void setTiles(const std::vector<Tile>& tiles) { m_tiles = tiles; }
    const std::vector<Tile>& getTiles() const { return m_tiles; }

private:
    unsigned int m_height = 0;
    unsigned int m_width = 0;
    unsigned int m_depth = 0;
    std::vector<Tile> m_tiles;
};
