#include "interaction_system.h"
#include "../components/collider_component.h"
#include "../components/openable_component.h"

void InteractionSystem::handleOpenEntityEvent(const OpenEntityEvent* event) {
    OpenableComponent* openable =
        m_engine->state()->components()->get<OpenableComponent>(event->entity);
    if (!openable) {
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