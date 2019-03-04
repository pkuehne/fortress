#include "interaction_system.h"
#include "../components/collider_component.h"
#include "../components/openable_component.h"

void InteractionSystem::registerHandlers() {
    events()->subscribe<OpenEntityEvent>(
        [=](std::shared_ptr<OpenEntityEvent> event) {
            handleOpenEntityEvent(event);
        });
    events()->subscribe<CloseEntityEvent>(
        [=](std::shared_ptr<CloseEntityEvent> event) {
            handleCloseEntityEvent(event);
        });
}

void InteractionSystem::handleOpenEntityEvent(
    std::shared_ptr<OpenEntityEvent> event) {
    OpenableComponent* openable =
        components()->get<OpenableComponent>(event->entity);
    if (!openable) {
        return;
    }
    if (openable->locked) {
        return;
    }
    openable->open = true;

    components()->remove<ColliderComponent>(event->entity);
}

void InteractionSystem::handleCloseEntityEvent(
    std::shared_ptr<CloseEntityEvent> event) {
    OpenableComponent* openable =
        components()->get<OpenableComponent>(event->entity);
    if (!openable) {
        return;
    }
    openable->open = false;

    components()->make<ColliderComponent>(event->entity);
}