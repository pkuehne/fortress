#include "objectives_system.h"

void ObjectivesSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_REMOVE_ENTITY: {
            const RemoveEntityEvent* l_event = dynamic_cast<const RemoveEntityEvent*> (event);
            if (l_event->entity == getEngineRef()->getEntities()->getPlayer()->getId()) {
                std::cout << "You lose!" << std::endl;
            }
            break;
        }
        default: break;
    }
}
