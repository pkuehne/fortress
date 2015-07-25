#include "combat_system.h"
#include <iostream>

void CombatSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_ATTACK_ENTITY: {
            if (checkForEnemies (Direction::North)) {
                return;
            }
            if (checkForEnemies (Direction::East)) {
                return;
            }
            if (checkForEnemies (Direction::South)) {
                return;
            }
            if (checkForEnemies (Direction::West)) {
                return;
            }
        } break;
        default:break;
    }
}


bool CombatSystem::checkForEnemies (DIRECTION dir)
{
    Entity* player = m_engine->getEntities()->getPlayer();

    std::vector<Entity*> l_entities;
    l_entities = findEntitiesToThe (dir, player);

    for (unsigned int ii = 0; ii < l_entities.size(); ii++) {
        if (l_entities[ii]->hasTag (MONSTER)) {
            m_engine->getEntities()->destroyEntity (l_entities[ii]->getId());
            return true;
        }
    }
    return false;
}
