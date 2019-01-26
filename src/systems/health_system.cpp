#include "health_system.h"
#include "../components/health_component.h"
#include <glog/logging.h>

void HealthSystem::onTurn() {
    for (EntityId entity : getEngine()->state()->entities()) {
        HealthComponent* health =
            getEngine()->state()->components()->get<HealthComponent>(entity);
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
