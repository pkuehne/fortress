#include "combat_system.h"
#include "health_component.h"
#include <iostream>
#include <sstream>

void CombatSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_ATTACK_ENTITY: {
            const AttackEntityEvent* l_event = dynamic_cast<const AttackEntityEvent*> (event);
            EntityId attacker = l_event->entity;
            EquipmentComponent* l_attackerEquipment = m_engine->getEntities()->getEquipments()->get(attacker);
            int damage = 1;
            if (l_attackerEquipment && l_attackerEquipment->rightHandWieldable != 0) {
                EntityId l_weapon = l_attackerEquipment->rightHandWieldable;
                damage = m_engine->getEntities()->getWieldables()->get(l_weapon)->baseDamage;
            }
            EntityHolder l_targets = m_engine->getEntities()->findEntitiesToThe (l_event->direction, l_event->entity);
            for (EntityId l_target : l_targets) {
                HealthComponent* l_health = m_engine->getEntities()->getHealths()->get(l_target);
                if (l_health) {
                    l_health->health -= damage;
                    updateLog (attacker, l_target, damage);
                    if (l_health->health < 1) {
                        m_engine->getEntities()->destroyEntity (l_target);
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
