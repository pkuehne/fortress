#include "combat_system.h"
#include "../components/description_component.h"
#include "../components/equipment_component.h"
#include "../components/experience_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/health_component.h"
#include "../components/sprite_component.h"
#include "../components/wieldable_component.h"
#include <iostream>
#include <sstream>

void CombatSystem::registerHandlers() {
    events()->subscribe<AttackEntityEvent>(
        [=](std::shared_ptr<AttackEntityEvent> event) {
            handleAttack(event->attacker, event->defender);
        });
}

void CombatSystem::handleAttack(EntityId attacker, EntityId defender) {
    EquipmentComponent* l_attackerEquipment =
        components()->get<EquipmentComponent>(attacker);
    unsigned int damage = 1;
    if (l_attackerEquipment && l_attackerEquipment->rightHandWieldable != 0) {
        EntityId l_weapon = l_attackerEquipment->rightHandWieldable;
        WieldableComponent* l_wield =
            components()->get<WieldableComponent>(l_weapon);
        damage = l_wield->baseDamage;
    }

    HealthComponent* l_health = components()->get<HealthComponent>(defender);
    if (!l_health) {
        // Invincible?
        return;
    }
    updateLog(attacker, defender, damage);

    GraphicsEffectComponent* effect =
        components()->make<GraphicsEffectComponent>(defender);
    effect->type = EFFECT_CHANGE_COLOR;
    effect->duration = 15;
    effect->new_color = Color(RED);

    if (damage < l_health->health) {
        l_health->health -= damage;
        events()->raise(std::make_shared<UpdateExperienceEvent>(attacker, 100));
    } else {
        killEntity(defender);
        events()->raise(std::make_shared<UpdateExperienceEvent>(attacker, 500));
    }
}

void CombatSystem::killEntity(EntityId id) {
    const Location location = state()->location(id);
    if (id == entities()->getPlayer()) {
        events()->raise(std::make_shared<RemoveEntityEvent>(id, location));
        return;
    }

    // Create the corpse
    EntityId corpse = state()->createEntity(location);
    events()->raise(std::make_shared<InstantiatePrefabEvent>(corpse, "corpse"));
    components()->make<SpriteComponent>(corpse)->sprite =
        components()->get<SpriteComponent>(id)->sprite;

    // Drop the equipment
    EquipmentComponent* equipment = components()->get<EquipmentComponent>(id);
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
            entities()->setLocation(entity, location);
        }
    }
    entities()->destroyEntity(id);
}

void CombatSystem::updateLog(const EntityId& attacker, const EntityId& target,
                             int damage) {
    std::stringstream str;
    DescriptionComponent* l_attackerDesc =
        components()->get<DescriptionComponent>(attacker);
    DescriptionComponent* l_targetDesc =
        components()->get<DescriptionComponent>(target);

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

    if (attacker == entities()->getPlayer()) {
        events()->raise(std::make_shared<AddLogMessageEvent>(str.str()));
    } else {
        events()->raise(
            std::make_shared<AddLogMessageEvent>(str.str(), "warning"));
    }
}
