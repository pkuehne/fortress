#include "health_system.h"
#include "../components/health_component.h"
#include <spdlog/spdlog.h>

void HealthSystem::onTurn() {
    for (EntityId entityId : entities()->all()) {
        auto entity = entities()->world().entity(entityId);
        HealthComponent* health = entity.get_mut<HealthComponent>();
        if (health == nullptr)
            continue;

        if (++health->thirstStep >= health->thirstRate) {
            health->thirstStep = 0;
            health->thirst++;
        }
        if (++health->hungerStep >= health->hungerRate) {
            health->hungerStep = 0;
            health->hunger++;
        }
    }
}
