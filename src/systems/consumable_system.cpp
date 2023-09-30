#include "consumable_system.h"
#include "../components/consumable_component.h"
#include "../components/health_component.h"
#include <spdlog/spdlog.h>

void ConsumableSystem::registerHandlers() {
    events()->subscribe<ConsumeItemEvent>(
        [=](const ConsumeItemEvent& event) { handleConsumeItemEvent(event); });
}

void updateHealth(ConsumableComponent* consumable, HealthComponent* health) {
    if (!health) {
        return;
    }

    if (consumable->quenches == THIRST) {
        int result = health->thirst - consumable->quenchStrength;
        health->thirst = (result < 0) ? 0 : result;
    } else if (consumable->quenches == HUNGER) {
        int result = health->hunger - consumable->quenchStrength;
        health->hunger = (result < 0) ? 0 : result;
    }

    if (consumable->effect == HEALTH_EFFECT) {
        health->health += consumable->effectStrength;
    }
}

void ConsumableSystem::handleConsumeItemEvent(const ConsumeItemEvent& event) {
    // Validate
    auto item = entities()->world().entity(event.item);
    auto entity = entities()->world().entity(event.entity);

    if (!item.has<ConsumableComponent>()) {
        spdlog::error("Consume event on non-consumable item: {}!", event.item);
        return;
    }

    ConsumableComponent* consumable = item.get_mut<ConsumableComponent>();
    HealthComponent* health = entity.get_mut<HealthComponent>();

    // Check whether this has a health impact
    updateHealth(consumable, health);

    // Remove after use
    const Location location = entities()->getLocation(event.item);
    events()->fire<RemoveEntityEvent>(event.item, location);
}
