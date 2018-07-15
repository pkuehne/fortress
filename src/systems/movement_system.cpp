#include "movement_system.h"
#include "../components/collider_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/connector_component.h"
#include "../core/entity.h"
#include "../core/event.h"
#include "../core/game_engine.h"
#include "../windows/game_over_window.h"
#include <iostream>

void MovementSystem::handleMoveEntityEvent(const MoveEntityEvent* event) {
    EntityId l_entity = event->entity;
    Location l_oldLocation = m_engine->state()->location(l_entity);
    Location l_newLocation = event->newLocation;

    if (!m_engine->state()->isValidTile(l_newLocation)) {
        GraphicsEffectComponent* effect =
            getEngine()->state()->components()->make<GraphicsEffectComponent>(
                l_entity);
        effect->type = EFFECT_BLINK_FAST;
        effect->duration = 10;
        return; // Don't update position if it's not valid
    }

    // Check if we're running into a collidable or stairs, etc
    {
        Tile& tile = m_engine->state()->tile(l_newLocation);
        const EntityHolder& l_targets = tile.entities();

        bool blocked = tile.blocked();
        for (EntityId l_target : l_targets) {
            if (m_engine->state()->components()->get<ColliderComponent>(
                    l_target)) {
                blocked = true;
            }
            ConnectorComponent* l_stair =
                m_engine->state()->components()->get<ConnectorComponent>(l_target);
            if (l_stair && l_stair->target &&
                l_entity == m_engine->state()->player()) {
                l_newLocation = m_engine->state()->location(l_stair->target);
            }
        }
        if (blocked) {
            GraphicsEffectComponent* effect =
                getEngine()
                    ->state()
                    ->components()
                    ->make<GraphicsEffectComponent>(l_entity);
            effect->type = EFFECT_BLINK_FAST;
            effect->duration = 10;
            return; // Don't update position if it's a collidable
        }
    }

    getEngine()->state()->entityManager()->setLocation(event->entity,
                                                       l_newLocation);
    ChangeLocationEvent* changeEvent = new ChangeLocationEvent();
    changeEvent->entity = event->entity;
    changeEvent->oldLocation = l_oldLocation;
    changeEvent->newLocation = l_newLocation;
    getEngine()->raiseEvent(changeEvent);
}