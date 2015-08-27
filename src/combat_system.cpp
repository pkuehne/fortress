#include "combat_system.h"
#include "health_component.h"
#include <iostream>
#include <sstream>

void CombatSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_ATTACK_ENTITY: {
            const AttackEntityEvent* l_event = dynamic_cast<const AttackEntityEvent*> (event);

            std::vector<EntityId> l_targets = m_engine->getEntities()->findEntitiesToThe (l_event->direction, l_event->entity);
            std::vector<EntityId>::iterator iter = l_targets.begin();
            for (; iter != l_targets.end(); iter++) {
                HealthComponent* l_health = m_engine->getEntities()->getHealths()->get(*iter);
                if (l_health) {
                    l_health->health--;
                    updateLog (l_event->entity, *iter, 1);
                    if (l_health->health < 1) {
                        m_engine->getEntities()->destroyEntity (*iter);
                    }
                    break;
                }
            }
        } break;
        default:break;
    }
}

void CombatSystem::updateLog (const EntityId& attacker, const EntityId& target, int damage)
{
    std::stringstream str;
    DescriptionComponent* l_attackerDesc = m_engine->getEntities()->getDescriptions()->get (attacker);
    DescriptionComponent* l_targetDesc = m_engine->getEntities()->getDescriptions()->get (target);

    if (attacker == m_engine->getEntities()->getPlayer()) {
        str << "You";
    } else if (l_attackerDesc != 0) {
        str << "The " << l_attackerDesc->title;
    } else {
        str << "Something";
    }

    if (attacker == m_engine->getEntities()->getPlayer()) {
        str << " attack";
    } else {
        str << " attacks";
    }

    if (target == m_engine->getEntities()->getPlayer()) {
        str << " you";
    } else if (l_targetDesc != 0) {
        str << " the " << l_targetDesc->title;
    } else {
        str << " something";
    }

    if (attacker == m_engine->getEntities()->getPlayer()) {
        str << " and cause";
    } else {
        str << " and causes";
    }

    str << " " << damage << " damage!";

    if (attacker == m_engine->getEntities()->getPlayer()) {
        m_engine->addMessage (INFO, str.str());
    } else {
        m_engine->addMessage (WARN, str.str());
    }


}
