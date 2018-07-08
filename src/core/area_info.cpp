#include "area_info.h"

void AreaInfo::setSize(unsigned int width, unsigned int height,
                       unsigned int depth) {
    m_height = height;
    m_width = width;
    m_depth = depth;
    m_tiles.resize(width * height * depth);
}

Tile& AreaInfo::getTile(const Location& loc) {
    size_t index = (loc.z * m_height * m_width) + (loc.y * m_height) + loc.x;
    return m_tiles[index];
}
