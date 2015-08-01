#include "combat_system.h"
#include "health_component.h"
#include <iostream>

void CombatSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_ATTACK_ENTITY: {
            const AttackEntityEvent* l_event = dynamic_cast<const AttackEntityEvent*> (event);
            Entity* l_entity = m_engine->getEntities()->getEntity(l_event->entity);

            std::vector<EntityId> l_targets = findEntitiesToThe (l_event->direction, l_entity);
            std::vector<EntityId>::iterator iter = l_targets.begin();
            for (; iter != l_targets.end(); iter++) {
                HealthComponent* l_health = m_engine->getEntities()->getHealths()->get(*iter);
                if (l_health) {
                    m_engine->getEntities()->destroyEntity (*iter);
                    break;
                }
            }
        } break;
        default:break;
    }
}
