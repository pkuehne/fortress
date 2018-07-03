#include "combat_system.h"
#include "../components/description_component.h"
#include "../components/equipment_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/health_component.h"
#include "../components/sprite_component.h"
#include "../components/wieldable_component.h"
#include "../core/prefab_builder.h"
#include <iostream>
#include <sstream>

void CombatSystem::handleAttackEntityEvent(const AttackEntityEvent* event) {
    handleAttack(event->attacker, event->defender);
}

void CombatSystem::handleAttack(EntityId attacker, EntityId defender) {
    EquipmentComponent* l_attackerEquipment =
        m_engine->state()->components()->get<EquipmentComponent>(attacker);
    unsigned int damage = 1;
    if (l_attackerEquipment && l_attackerEquipment->rightHandWieldable != 0) {
        EntityId l_weapon = l_attackerEquipment->rightHandWieldable;
        damage = m_engine->state()
                     ->components()
                     ->get<WieldableComponent>(l_weapon)
                     ->baseDamage;
    }

    HealthComponent* l_health =
        m_engine->state()->components()->get<HealthComponent>(defender);
    if (!l_health) {
        // Invincible?
        return;
    }
    updateLog(attacker, defender, damage);

    GraphicsEffectComponent* effect =
        getEngine()->state()->components()->make<GraphicsEffectComponent>(
            defender);
    effect->type = EFFECT_CHANGE_COLOR;
    effect->duration = 15;
    effect->new_color = Color(RED);

    if (damage < l_health->health) {
        l_health->health -= damage;
    } else {
        if (defender == getEngine()->state()->player()) {
            m_engine->state()->entityManager()->destroyEntity(defender);
        } else {
            PrefabBuilder prefabs(m_engine->state());
            Location l_targetLoc = m_engine->state()->location(defender);
            SpriteComponent* l_sprite =
                m_engine->state()->components()->get<SpriteComponent>(defender);
            prefabs.createCorpsePrefab(l_targetLoc, l_sprite->sprite);
            getEngine()->state()->entityManager()->destroyEntity(defender);
        }
    }
}

void CombatSystem::updateLog(const EntityId& attacker, const EntityId& target,
                             int damage) {
    std::stringstream str;
    DescriptionComponent* l_attackerDesc =
        m_engine->state()->components()->get<DescriptionComponent>(attacker);
    DescriptionComponent* l_targetDesc =
        m_engine->state()->components()->get<DescriptionComponent>(target);

    if (attacker == m_engine->state()->player()) {
        str << "You";
    } else if (l_attackerDesc != 0) {
        str << "The " << l_attackerDesc->title;
    } else {
        str << "Something";
    }

    if (attacker == m_engine->state()->player()) {
        str << " attack";
    } else {
        str << " attacks";
    }

    if (target == m_engine->state()->player()) {
        str << " you";
    } else if (l_targetDesc != 0) {
        str << " the " << l_targetDesc->title;
    } else {
        str << " something";
    }

    if (attacker == m_engine->state()->player()) {
        str << " and cause";
    } else {
        str << " and causes";
    }

    str << " " << damage << " damage!";

    if (attacker == m_engine->state()->player()) {
        m_engine->state()->addMessage(INFO, str.str());
    } else {
        m_engine->state()->addMessage(WARN, str.str());
    }
}
