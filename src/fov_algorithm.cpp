#include "fov_algorithm.h"

void FovAlgorithm::calculateFov ()
{
    EntityId player = m_engine->getEntities()->getPlayer();
    Location playerLoc = m_engine->getEntities()->getLocation (player);

    m_engine->getMap()->getTile (playerLoc).lastVisited = m_engine->getTurn();

    int x = 0;
    int y = 0;
    unsigned int sightMax = 10;
    for (unsigned int oct = 0; oct < 8; oct++) {
        ShadowLine line;
        for (unsigned int row = 1; row < sightMax; row++) {
            for (unsigned int col = 0; col <= row; col++) {
                Shadow projection = projectTile (row, col);
                transformOctant (row, col, oct, y, x);
                y += playerLoc.y;
                x += playerLoc.x;
                if (m_engine->getMap()->isValidTile (x, y, m_engine->getLevel()) && !line.isInShadow (projection)) {
                    m_engine->getMap()->getTile (x, y, m_engine->getLevel()).lastVisited = m_engine->getTurn();
                }
            }
        }
    }



}

void FovAlgorithm::transformOctant (unsigned int row, unsigned int col, unsigned int octant, int& outY, int& outX)
{
    if (octant == 0) {
        outX = col;
        outY = -row;
    }
    if (octant == 1) {
        outX = row;
        outY = -col;
    }
    if (octant == 2) {
        outX = row;
        outY = col;
    }
    if (octant == 3) {
        outX = col;
        outY = row;
    }
    if (octant == 4) {
        outX = -col;
        outY = row;
    }
    if (octant == 5) {
        outX = -row;
        outY = col;
    }
    if (octant == 6) {
        outX = -row;
        outY = -col;
    }
    if (octant == 7) {
        outX = -col;
        outY = -row;
    }

}

Shadow FovAlgorithm::projectTile (double row, double col) {
  double topLeft = col / (row + 2);
  double bottomRight = (col + 1) / (row + 1);
  return Shadow(topLeft, bottomRight);
}

bool Shadow::contains (const Shadow& other) const
{
    return start <= other.start && end >= other.end;
}

bool ShadowLine::isInShadow (const Shadow& projection)
{
    for (Shadow shadow : m_shadows) {
        if (shadow.contains (projection)) return true;
    }
    return false;
}
