#include "combat_system.h"
#include "../components/description_component.h"
#include "../components/equipment_component.h"
#include "../components/experience_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/health_component.h"
#include "../components/npc_component.h"
#include "../components/player_component.h"
#include "../components/sprite_component.h"
#include "../components/wieldable_component.h"
#include <iostream>
#include <sstream>

void CombatSystem::registerHandlers() {
    events()->subscribe<AttackEntityEvent>([&](const AttackEntityEvent& event) {
        this->handleAttack(event.attacker, event.defender);
    });
    events()->subscribe<KillEntityEvent>(
        [&](const KillEntityEvent& event) { this->killEntity(event.entity); });
}

void CombatSystem::handleAttack(EntityId attackerId, EntityId defenderId) {

    auto attacker = entities()->world().entity(attackerId);
    auto defender = entities()->world().entity(defenderId);
    auto l_attackerEquipment = attacker.get<EquipmentComponent>();
    unsigned int damage = 1;
    if (l_attackerEquipment && l_attackerEquipment->rightHandWieldable != 0) {
        EntityId l_weapon = l_attackerEquipment->rightHandWieldable;
        auto l_wield =
            entities()->world().entity(l_weapon).get<WieldableComponent>();
        damage = l_wield->baseDamage;
    }

    if (!defender.has<HealthComponent>()) {
        // Invincible?
        return;
    }
    updateLog(attackerId, defenderId, damage);

    GraphicsEffectComponent effect = GraphicsEffectComponent();
    effect.type = EFFECT_CHANGE_COLOR;
    effect.duration = 15;
    effect.new_color = Color(RED);
    defender.set<GraphicsEffectComponent>(effect);

    auto l_health = defender.get_mut<HealthComponent>();
    if (damage < l_health->health) {
        l_health->health -= damage;
        events()->fire<UpdateExperienceEvent>(attackerId, 100);
    } else {
        // killEntity(defenderId);
        events()->fire<KillEntityEvent>(defenderId);
        events()->fire<UpdateExperienceEvent>(attackerId, 500);
    }
}

void CombatSystem::killEntity(EntityId id) {
    auto entity = entities()->world().entity(id);

    const Location location = entities()->getLocation(id);
    if (id == entities()->world().lookup("player").id()) {
        events()->fire<RemoveEntityEvent>(id, location);
        return;
    }

    // Create the corpse if it's an NPC
    if (entity.has<NpcComponent>()) {
        EntityId corpseId = instantiatePrefab("corpse", location);
        auto corpse = entities()->world().entity(corpseId);
        corpse.get_mut<SpriteComponent>()->sprite =
            entity.get<SpriteComponent>()->sprite;
    }

    events()->fire<RemoveEntityEvent>(id, location);
}

void CombatSystem::updateLog(const EntityId& attackerId, const EntityId& target,
                             int damage) {
    std::stringstream str;
    auto l_attackerDesc =
        entities()->world().entity(attackerId).get<DescriptionComponent>();
    auto l_targetDesc =
        entities()->world().entity(target).get<DescriptionComponent>();

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

    if (attackerId == entities()->world().lookup("player").id()) {
        events()->fire<AddLogMessageEvent>(str.str());
    } else {
        events()->fire<AddLogMessageEvent>(str.str(), "warning");
    }
}
