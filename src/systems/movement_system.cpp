#include "movement_system.h"
#include "event.h"
#include "game_engine.h"
#include "entity.h"
#include "game_over_window.h"
#include <iostream>
#include "stair_component.h"
#include "collider_component.h"
#include "graphics_effect_component.h"

void MovementSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_MOVE_ENTITY: {
            const MoveEntityEvent* l_event = static_cast<const MoveEntityEvent*> (event);
            EntityId l_entity = l_event->entity;
            Location l_oldLocation = m_engine->state()->location(l_entity);
            Location l_newLocation = l_event->newLocation;

            //Check if we're running into a collidable or stairs, etc
            {
                const EntityHolder& l_targets = m_engine->state()->tile(l_newLocation).entities();
                for (EntityId l_target : l_targets) {
                    if (m_engine->state()->components()->get<ColliderComponent> (l_target)) {
						GraphicsEffectComponent* effect = 
                                                    getEngine()->state()->components()->make<GraphicsEffectComponent>(l_entity);
						effect->type = EFFECT_BLINK_FAST;
						effect->duration = 10;
						return; // Don't update position if it's a collidable
                    }
                    StairComponent* l_stair = m_engine->state()->components()->get<StairComponent> (l_target);
                    if (l_stair && l_stair->target && l_entity == m_engine->state()->player()) {
                        l_newLocation = m_engine->state()->location(l_stair->target);
                    }
                }
            }

            getEngine()->state()->entityManager()->setLocation (l_event->entity, l_newLocation);
            ChangeLocationEvent* changeEvent = new ChangeLocationEvent();
            changeEvent->entity = l_event->entity;
            changeEvent->oldLocation = l_oldLocation;
            changeEvent->newLocation = l_newLocation;
            getEngine()->raiseEvent (changeEvent);
            break;
        }
        default: break;
    }
}
