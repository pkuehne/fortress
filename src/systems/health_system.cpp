#include "health_system.h"
#include "health_component.h"
#include <glog/logging.h>

void HealthSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_ATTACK_ENTITY: 
            {
                //const AttackEntityEvent* l_event = static_cast<const AttackEntityEvent*> (event);
            }
            break;
        default:
            break;
    }
}

void HealthSystem::update()
{
    if (getEngine()->isPlayerTurn()) return;
    for (EntityId entity : getEngine()->getEntities()->get()) {
        HealthComponent* health = getEngine()->getComponents()->get<HealthComponent> (entity);
        if (health == nullptr) continue;
        
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
