#include "combat_system.h"
#include "health_component.h"
#include <iostream>
#include <sstream>
#include "equipment_component.h"
#include "wieldable_component.h"
#include "health_component.h"
#include "sprite_component.h"
#include "description_component.h"
#include "graphics_effect_component.h"

void CombatSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_ATTACK_ENTITY: 
            {
                const AttackEntityEvent* l_event = static_cast<const AttackEntityEvent*> (event);
                handleAttack (l_event->attacker, l_event->defender);
            }
            break;
        default:
            break;
    }
}

void CombatSystem::handleAttack (EntityId attacker, EntityId defender) 
{
    EquipmentComponent* l_attackerEquipment = m_engine->getComponents()->get<EquipmentComponent>(attacker);
    unsigned int damage = 1;
    if (l_attackerEquipment && l_attackerEquipment->rightHandWieldable != 0) {
        EntityId l_weapon = l_attackerEquipment->rightHandWieldable;
        damage = m_engine->getComponents()->get<WieldableComponent>(l_weapon)->baseDamage;
    }

    HealthComponent* l_health = m_engine->getComponents()->get<HealthComponent>(defender);
    if (!l_health) {
        // Invincible?
        return;
    }
    updateLog (attacker, defender, damage);

    GraphicsEffectComponent* effect = 
        getEngine()->getComponents()->make<GraphicsEffectComponent>(defender);
    effect->type = EFFECT_CHANGE_COLOR;
    effect->duration = 15;
    effect->new_color = Color (RED);

    if (damage < l_health->health) {
        l_health->health -= damage;
    } else {
        if (defender == getEngine()->getEntities()->getPlayer()) {
            m_engine->getEntities()->destroyEntity (defender);
        } else {
            Location l_targetLoc = m_engine->getEntities()->getLocation (defender);
            SpriteComponent* l_sprite = m_engine->getComponents()->get<SpriteComponent> (defender);
            getEngine()->getEntities()->createCorpsePrefab(l_targetLoc, l_sprite->sprite);
            getEngine()->getEntities()->destroyEntity (defender);
        }
    }
}

void CombatSystem::updateLog (const EntityId& attacker, const EntityId& target, int damage)
{
    std::stringstream str;
    DescriptionComponent* l_attackerDesc = m_engine->getComponents()->get<DescriptionComponent> (attacker);
    DescriptionComponent* l_targetDesc = m_engine->getComponents()->get<DescriptionComponent> (target);

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
