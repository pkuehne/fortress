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
    LOG(INFO) << "Calling HealthSystem::update" << std::endl;
    if (getEngine()->isPlayerTurn()) return;
    LOG(INFO) << "Not player turn" << std::endl;
    for (EntityId entity : getEngine()->getEntities()->get()) {
        HealthComponent* health = getEngine()->getComponents()->get<HealthComponent> (entity);
        LOG(INFO) << "Getting HealthComponent for " << entity << std::endl;
        if (health == nullptr) continue;
        
        LOG(INFO) << "Incrementing thirst and hunger steps" << std::endl;
        if (++health->thirstStep >= health->thirstRate) {
            health->thirstStep = 0;
            health->thirst++;
            LOG(INFO) << "Incrementing thirst" << std::endl;
        }
        if (++health->hungerStep >= health->hungerRate) {
            health->hungerStep = 0;
            health->hunger++;
            LOG(INFO) << "Incrementing hunger" << std::endl;
        }
    }

}
