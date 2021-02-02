#include "consumable_system.h"
#include "../components/consumable_component.h"
#include "../components/health_component.h"
#include <glog/logging.h>

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
    if (!components()->exists<ConsumableComponent>(event.item)) {
        LOG(ERROR) << "Consume event on non-consumable item: " << event.item
                   << " !" << std::endl;
        return;
    }

    ConsumableComponent* consumable =
        components()->get<ConsumableComponent>(event.item);
    HealthComponent* health = components()->get<HealthComponent>(event.entity);

    // Check whether this has a health impact
    updateHealth(consumable, health);

    // Remove after use
    const Location location = entities()->getLocation(event.item);
    events()->fire<RemoveEntityEvent>(event.item, location);
}
