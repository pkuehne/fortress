#include "fov_algorithm.h"
#include "../components/collider_component.h"
#include "../components/description_component.h"
#include "../core/entity.h"
#include "../core/game_engine.h"
#include <iostream>

void FovAlgorithm::calculateFov() {
    EntityId player = m_engine->state()->player();
    Location playerLoc = m_engine->state()->location(player);

    if (player == 0)
        return;

    m_engine->state()->tile(playerLoc).lastVisited() = m_engine->getTurn();

    int x = 0;
    int y = 0;
    unsigned int sightMax = 10;
    for (unsigned int oct = 0; oct < 8; oct++) {
        ShadowLine line;
        bool fullShadow = false;
        for (unsigned int row = 1; row < sightMax; row++) {
            for (unsigned int col = 0; col <= row; col++) {
                bool visible = false;
                Shadow projection(0, 0);
                if (!fullShadow) {
                    projection = projectTile(row, col);
                    visible = !line.isInShadow(projection);
                }
                transformOctant(row, col, oct, y, x);
                y += playerLoc.y;
                x += playerLoc.x;
                Location loc(x, y, playerLoc.z, playerLoc.area);
                Tile& tile = m_engine->state()->tile(loc);
                if (m_engine->state()->isValidTile(loc) && visible) {
                    bool blocked = tile.blocked();
                    tile.lastVisited() = m_engine->getTurn();
                    for (const EntityId entity :
                         m_engine->state()->tile(loc).entities()) {
                        if (m_engine->state()
                                ->components()
                                ->get<ColliderComponent>(entity)) {
                            blocked = true;
                            break;
                        }
                    }
                    if (blocked) {
                        line.addShadow(projection);
                        fullShadow = line.isInFullShadow();
                    }
                }
            }
        }
    }
}

void FovAlgorithm::transformOctant(unsigned int row, unsigned int col,
                                   unsigned int octant, int& outY, int& outX) {
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

Shadow FovAlgorithm::projectTile(double row, double col) {
    double topLeft = col / (row + 2);
    double bottomRight = (col + 1) / (row + 1);
    return Shadow(topLeft, bottomRight);
}

bool Shadow::contains(const Shadow& other) const {
    return start - 0.00 <= other.start && end + 0.00 >= other.end;
}

bool ShadowLine::isInShadow(const Shadow& projection) {
    for (Shadow shadow : m_shadows) {
        if (shadow.contains(projection))
            return true;
    }
    return false;
}

bool ShadowLine::isInFullShadow() {
    if (m_shadows.size() == 1 && m_shadows[1].start == 0.0 &&
        m_shadows[1].end == 1.0) {
        return true;
    }
    return false;
}

void ShadowLine::addShadow(Shadow shadow) {
    unsigned int index = 0;
    auto iter = m_shadows.begin();
    for (; index < m_shadows.size(); index++, iter++) {
        if (m_shadows[index].start >= shadow.start) {
            break;
        }
    }

    Shadow* prev = nullptr;
    if (index > 0 && m_shadows[index - 1].end > shadow.start) {
        prev = &(m_shadows[index - 1]);
    }

    Shadow* next = nullptr;
    if (index < m_shadows.size() && m_shadows[index].start < shadow.end) {
        next = &(m_shadows[index]);
    }

    if (next != nullptr) {
        if (prev != nullptr) {
            prev->end = next->end;
            m_shadows.erase(iter);
        } else {
            next->start = shadow.start;
        }
    } else {
        if (prev != nullptr) {
            prev->end = shadow.end;
        } else {
            m_shadows.insert(iter, shadow);
        }
    }
}
