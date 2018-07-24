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
    GameState* state = m_engine->state();
    EquipmentComponent* l_attackerEquipment =
        state->components()->get<EquipmentComponent>(attacker);
    unsigned int damage = 1;
    if (l_attackerEquipment && l_attackerEquipment->rightHandWieldable != 0) {
        EntityId l_weapon = l_attackerEquipment->rightHandWieldable;
        WieldableComponent* l_wield =
            m_engine->state()->components()->get<WieldableComponent>(l_weapon);
        damage = l_wield->baseDamage;
    }

    HealthComponent* l_health =
        m_engine->state()->components()->get<HealthComponent>(defender);
    if (!l_health) {
        // Invincible?
        return;
    }
    updateLog(attacker, defender, damage);

    GraphicsEffectComponent* effect =
        state->components()->make<GraphicsEffectComponent>(defender);
    effect->type = EFFECT_CHANGE_COLOR;
    effect->duration = 15;
    effect->new_color = Color(RED);

    if (damage < l_health->health) {
        l_health->health -= damage;
    } else {
        killEntity(defender);
    }
}

void CombatSystem::killEntity(EntityId id) {
    GameState* state = m_engine->state();
    const Location location = state->location(id);

    // Create the corpse
    EntityId corpse = state->prefabs().create("corpse", location);
    state->components()->get<SpriteComponent>(corpse)->sprite =
        state->components()->get<SpriteComponent>(id)->sprite;

    // Drop the equipment
    EquipmentComponent* equipment =
        state->components()->get<EquipmentComponent>(id);
    if (equipment) {
        equipment->carriedEquipment.push_back(equipment->headWearable);
        equipment->carriedEquipment.push_back(equipment->faceWearable);
        equipment->carriedEquipment.push_back(equipment->chestWearable);
        equipment->carriedEquipment.push_back(equipment->armsWearable);
        equipment->carriedEquipment.push_back(equipment->handsWearable);
        equipment->carriedEquipment.push_back(equipment->legsWearable);
        equipment->carriedEquipment.push_back(equipment->feetWearable);
        equipment->carriedEquipment.push_back(equipment->rightHandWieldable);
        equipment->carriedEquipment.push_back(equipment->leftHandWieldable);
        equipment->carriedEquipment.push_back(equipment->armsWearable);

        for (auto entity : equipment->carriedEquipment) {
            state->entityManager()->setLocation(entity, location);
        }
    }
    state->entityManager()->destroyEntity(id);
}

void CombatSystem::updateLog(const EntityId& attacker, const EntityId& target,
                             int damage) {
    std::stringstream str;
    DescriptionComponent* l_attackerDesc =
        m_engine->state()->components()->get<DescriptionComponent>(attacker);
    DescriptionComponent* l_targetDesc =
        m_engine->state()->components()->get<DescriptionComponent>(target);

    if (l_attackerDesc != 0) {
        str << "The " << l_attackerDesc->title;
    } else {
        str << "Something";
    }

    str << " attacks ";

    if (l_targetDesc != 0) {
        str << "the " << l_targetDesc->title;
    } else {
        str << "something";
    }

    str << " and causes " << damage << " damage!";

    if (attacker == m_engine->state()->player()) {
        m_engine->state()->addMessage(MessageType::INFO, str.str());
    } else {
        m_engine->state()->addMessage(MessageType::WARN, str.str());
    }
}
