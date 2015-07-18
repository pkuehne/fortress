#include "combat_system.h"
#include <iostream>

void CombatSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_ATTACK_ENTITY: {
            if (checkForEnemies (MoveEntityEvent::UP)) {
                return;
            }
            if (checkForEnemies (MoveEntityEvent::RIGHT)) {
                return;
            }
            if (checkForEnemies (MoveEntityEvent::DOWN)) {
                return;
            }
            if (checkForEnemies (MoveEntityEvent::LEFT)) {
                return;
            }
        } break;
        default:break;
    }
}


bool CombatSystem::checkForEnemies (MoveEntityEvent::DIRECTION dir)
{
    Entity* player = m_engine->getEntities()->getEntity ("Player");

    std::vector<Entity*> l_entities;
    l_entities = findEntitiesToThe (dir, player);

    for (unsigned int ii = 0; ii < l_entities.size(); ii++) {
        if (l_entities[ii]->getName() == std::string("Orc")) {
            m_engine->getEntities()->destroyEntity (l_entities[ii]->getName());
            return true;
        }
    }
    return false;
}
