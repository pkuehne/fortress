#include "movement_system.h"
#include "../components/collider_component.h"
#include "../components/connector_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/logmessage_component.h"
#include "../components/player_component.h"
#include "../core/entity.h"
#include "../core/event.h"
#include "../windows/game_over_window.h"
#include <iostream>
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

void MovementSystem::registerHandlers() {
    events()->subscribe<MoveEntityEvent>(
        [=](auto event) { handleMoveEntityEvent(event); });
    events()->subscribe<ChangeLocationEvent>([&](auto event) {
        if (this->map()->isValidTile(event.oldLocation)) {
            this->map()->getTile(event.oldLocation).removeEntity(event.entity);
        }
        if (this->map()->isValidTile(event.newLocation)) {
            this->map()->getTile(event.newLocation).addEntity(event.entity);
        }
    });
    events()->subscribe<RemoveEntityEvent>([&](auto event) {
        if (!this->map()->isValidTile(event.location)) {
            spdlog::error("Attempted to remove {} at illegal location {}",
                          event.entity, event.location);
            return;
        }
        this->map()->getTile(event.location).removeEntity(event.entity);
    });
    events()->subscribe<AddEntityEvent>([&](auto event) {
        if (!this->map()->isValidTile(event.location)) {
            return;
        }
        this->map()->getTile(event.location).addEntity(event.entity);
    });
}

void MovementSystem::handleMoveEntityEvent(const MoveEntityEvent& event) {
    EntityId l_entity = event.entity;
    Location l_oldLocation = entities()->getLocation(l_entity);
    Location l_newLocation = event.newLocation;
    auto entity = entities()->world().entity(event.entity);

    if (!map()->isValidTile(l_newLocation)) {
        GraphicsEffectComponent effect = GraphicsEffectComponent();
        effect.type = EFFECT_BLINK_FAST;
        effect.duration = 10;
        entity.set<GraphicsEffectComponent>(effect);
        return; // Don't update position if it's not valid
    }

    // Check if we're running into a collidable or stairs, etc
    {
        Tile& tile = map()->getTile(l_newLocation);
        const EntityHolder& l_targets = tile.entities();
        auto player = entities()->world().lookup("player");

        bool blocked = tile.blocked();
        for (EntityId l_target : l_targets) {
            auto entity = entities()->world().entity(l_target);

            if (entity.has<ColliderComponent>()) {
                blocked = true;
            }
            if (entity.has<ConnectorComponent>()) {
                auto l_stair = entity.get<ConnectorComponent>();
                if (l_stair->target && l_entity == player.id()) {
                    l_newLocation = entities()->getLocation(l_stair->target);
                }
            }
        }
        if (blocked) {
            GraphicsEffectComponent effect = GraphicsEffectComponent();
            effect.type = EFFECT_BLINK_FAST;
            effect.duration = 10;
            entity.set<GraphicsEffectComponent>(effect);
            return; // Don't update position if it's a collidable
        }
    }

    entities()->setLocation(event.entity, l_newLocation);
    events()->fire<ChangeLocationEvent>(event.entity, l_oldLocation,
                                        l_newLocation);
}
