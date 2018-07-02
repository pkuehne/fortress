#include "interaction_system.h"
#include "../components/collider_component.h"
#include "../components/openable_component.h"

void InteractionSystem::update() {}

void InteractionSystem::handleEvent(const Event* event) {
    switch (event->getType()) {
        case EVENT_OPEN_ENTITY: {
            std::cout << "Opening: !" << std::endl;
            const OpenEntityEvent* l_event =
                dynamic_cast<const OpenEntityEvent*>(event);
            handleOpenEntityEvent(l_event);
            break;
        }
        case EVENT_CLOSE_ENTITY: {
            const CloseEntityEvent* l_event =
                dynamic_cast<const CloseEntityEvent*>(event);
            handleCloseEntityEvent(l_event);
            break;
        }
        default:
            break;
    }
}

void InteractionSystem::handleOpenEntityEvent(const OpenEntityEvent* event) {
    OpenableComponent* openable =
        m_engine->state()->components()->get<OpenableComponent>(event->entity);
    if (!openable) {
        std::cout << "is not openable!" << std::endl;
        return;
    }
    openable->open = true;

    m_engine->state()->components()->remove<ColliderComponent>(event->entity);
}

void InteractionSystem::handleCloseEntityEvent(const CloseEntityEvent* event) {
    OpenableComponent* openable =
        m_engine->state()->components()->get<OpenableComponent>(event->entity);
    if (!openable) {
        return;
    }
    openable->open = false;

    m_engine->state()->components()->make<ColliderComponent>(event->entity);
}