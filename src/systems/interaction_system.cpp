#include "interaction_system.h"
#include "../components/collider_component.h"
#include "../components/openable_component.h"

void InteractionSystem::registerHandlers() {
    getEngine()->events()->subscribe<OpenEntityEvent>(
        [=](std::shared_ptr<OpenEntityEvent> event) {
            handleOpenEntityEvent(event);
        });
    getEngine()->events()->subscribe<CloseEntityEvent>(
        [=](std::shared_ptr<CloseEntityEvent> event) {
            handleCloseEntityEvent(event);
        });
}

void InteractionSystem::handleOpenEntityEvent(
    std::shared_ptr<OpenEntityEvent> event) {
    OpenableComponent* openable =
        m_engine->state()->components()->get<OpenableComponent>(event->entity);
    if (!openable) {
        return;
    }
    openable->open = true;

    m_engine->state()->components()->remove<ColliderComponent>(event->entity);
}

void InteractionSystem::handleCloseEntityEvent(
    std::shared_ptr<CloseEntityEvent> event) {
    OpenableComponent* openable =
        m_engine->state()->components()->get<OpenableComponent>(event->entity);
    if (!openable) {
        return;
    }
    openable->open = false;

    m_engine->state()->components()->make<ColliderComponent>(event->entity);
}