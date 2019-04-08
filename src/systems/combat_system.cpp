#include "combat_system.h"
#include "../components/description_component.h"
#include "../components/equipment_component.h"
#include "../components/experience_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/health_component.h"
#include "../components/player_component.h"
#include "../components/sprite_component.h"
#include "../components/wieldable_component.h"
#include <iostream>
#include <sstream>

void CombatSystem::registerHandlers() {
    events()->subscribe<AttackEntityEvent>(
        [&](std::shared_ptr<AttackEntityEvent> event) {
            this->handleAttack(event->attacker, event->defender);
        });
    events()->subscribe<KillEntityEvent>(
        [&](auto event) { this->killEntity(event->entity); });
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
        // killEntity(defender);
        events()->raise(std::make_shared<KillEntityEvent>(defender));
        events()->raise(std::make_shared<UpdateExperienceEvent>(attacker, 500));
    }
}

void CombatSystem::killEntity(EntityId id) {
    const Location location = entities()->getLocation(id);
    if (id == components()->getUnique<PlayerComponent>().id) {
        events()->raise(std::make_shared<RemoveEntityEvent>(id));
        return;
    }

    // Create the corpse
    EntityId corpse = instantiatePrefab("corpse", location);
    components()->make<SpriteComponent>(corpse)->sprite =
        components()->get<SpriteComponent>(id)->sprite;

    events()->raise(std::make_shared<RemoveEntityEvent>(id));
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

    if (attacker == components()->getUnique<PlayerComponent>().id) {
        events()->raise(std::make_shared<AddLogMessageEvent>(str.str()));
    } else {
        events()->raise(
            std::make_shared<AddLogMessageEvent>(str.str(), "warning"));
    }
}
