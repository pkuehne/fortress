#include "health_system.h"
#include "../components/health_component.h"
#include <spdlog/spdlog.h>

void HealthSystem::onTurn() {
    for (EntityId entity : entities()->all()) {
        HealthComponent* health = components()->get<HealthComponent>(entity);
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
