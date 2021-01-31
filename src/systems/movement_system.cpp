#include "movement_system.h"
#include "../components/collider_component.h"
#include "../components/connector_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/logmessage_component.h"
#include "../components/player_component.h"
#include "../core/entity.h"
#include "../core/event.h"
#include "../windows/game_over_window.h"
#include <glog/logging.h>
#include <iostream>

void MovementSystem::registerHandlers() {
    events()->subscribe<MoveEntityEvent>(
        [=](std::shared_ptr<MoveEntityEvent> event) {
            handleMoveEntityEvent(event);
        });
    events()->subscribe<ChangeLocationEvent>([&](auto event) {
        if (this->map()->isValidTile(event->oldLocation)) {
            this->map()
                ->getTile(event->oldLocation)
                .removeEntity(event->entity);
        }
        if (this->map()->isValidTile(event->newLocation)) {
            this->map()->getTile(event->newLocation).addEntity(event->entity);
        }
    });
    events()->subscribe<RemoveEntityEvent>([&](auto event) {
        if (!this->map()->isValidTile(event->location)) {
            LOG(ERROR) << "Attempted to remove " << event->entity
                       << " at illegal location " << event->location
                       << std::endl;
            return;
        }
        this->map()->getTile(event->location).removeEntity(event->entity);
    });
    events()->subscribe<AddEntityEvent>([&](auto event) {
        if (!this->map()->isValidTile(event->location)) {
            return;
        }
        this->map()->getTile(event->location).addEntity(event->entity);
    });
}

void MovementSystem::handleMoveEntityEvent(
    std::shared_ptr<MoveEntityEvent> event) {
    EntityId l_entity = event->entity;
    Location l_oldLocation = entities()->getLocation(l_entity);
    Location l_newLocation = event->newLocation;

    if (!map()->isValidTile(l_newLocation)) {
        GraphicsEffectComponent* effect =
            components()->make<GraphicsEffectComponent>(l_entity);
        effect->type = EFFECT_BLINK_FAST;
        effect->duration = 10;
        return; // Don't update position if it's not valid
    }

    // Check if we're running into a collidable or stairs, etc
    {
        Tile& tile = map()->getTile(l_newLocation);
        const EntityHolder& l_targets = tile.entities();
        auto player = components()->getUnique<PlayerComponent>();

        bool blocked = tile.blocked();
        for (EntityId l_target : l_targets) {
            if (components()->get<ColliderComponent>(l_target)) {
                blocked = true;
            }
            ConnectorComponent* l_stair =
                components()->get<ConnectorComponent>(l_target);
            if (l_stair && l_stair->target && l_entity == player.id) {
                l_newLocation = entities()->getLocation(l_stair->target);
            }
        }
        if (blocked) {
            GraphicsEffectComponent* effect =
                components()->make<GraphicsEffectComponent>(l_entity);
            effect->type = EFFECT_BLINK_FAST;
            effect->duration = 10;
            return; // Don't update position if it's a collidable
        }
    }

    entities()->setLocation(event->entity, l_newLocation);
    events()->fire(std::make_shared<ChangeLocationEvent>(
        event->entity, l_oldLocation, l_newLocation));
}