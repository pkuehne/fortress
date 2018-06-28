#include "consumable_system.h"
#include "../components/consumable_component.h"
#include "../components/health_component.h"

void updateHealth(ConsumableComponent* consumable, HealthComponent* health)
{
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

void ConsumableSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_CONSUME_ITEM: {
            const ConsumeItemEvent* l_event = static_cast<const ConsumeItemEvent*> (event);

            ConsumableComponent* consumable = getEngine()->state()->components()->get<ConsumableComponent> (l_event->item);
            HealthComponent* health = getEngine()->state()->components()->get<HealthComponent> (l_event->entity);

            // Validate
            if (!consumable) {
                LOG(ERROR) << "Consume event on non-consumable item: " << l_event->item << " !" << std::endl;
                return;
            }

            // Check whether this has a health impact
            updateHealth(consumable, health);
            
            getEngine()->state()->entityManager()->destroyEntity (l_event->item);
            break;
        }
        default: break;
    }
}
