#include "movement_system.h"
#include "event.h"
#include "game_engine.h"
#include "entity.h"
#include "game_over_window.h"
#include <iostream>
#include "stair_component.h"
#include "collider_component.h"

void MovementSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_MOVE_ENTITY: {
            const MoveEntityEvent* l_event = dynamic_cast<const MoveEntityEvent*> (event);
            EntityId l_entity = l_event->entity;
            Location l_oldLocation = m_engine->getEntities()->getLocation(l_entity);
            Location l_newLocation = l_event->newLocation;

            //Check if we're running into a collidable or stairs, etc
            {
                EntityHolder& l_targets = m_engine->getMap()->getTile(l_newLocation).entities;
                for (EntityId l_target : l_targets) {
                    if (m_engine->getComponents()->get<ColliderComponent> (l_target)) {
                        return; // Don't update position if it's a collidable
                    }
                    StairComponent* l_stair = m_engine->getComponents()->get<StairComponent> (l_target);
                    if (l_stair && l_stair->target && l_entity == m_engine->getEntities()->getPlayer()) {
                        /*unsigned int level = m_engine->getLevel();
                        level += l_stair->direction == STAIR_UP ? -1 : 1;
                        ChangeLevelEvent* l_event = new ChangeLevelEvent;
                        l_event->level = level;
                        l_event->direction = l_stair->direction;
                        m_engine->raiseEvent (l_event);
                        */
                        l_newLocation = m_engine->getEntities()->getLocation(l_stair->target);
                    }
                }
            }

            getEngine()->getEntities()->setLocation (l_event->entity, l_newLocation);
            ChangeLocationEvent* changeEvent = new ChangeLocationEvent();
            changeEvent->entity = l_event->entity;
            changeEvent->oldLocation = l_oldLocation;
            changeEvent->newLocation = l_newLocation;
            getEngine()->raiseEvent (changeEvent);
            break;
        }
        case EVENT_CHANGE_LEVEL: {
            const ChangeLevelEvent* l_event = dynamic_cast<const ChangeLevelEvent*> (event);
            unsigned int level = l_event->level;
            if (level == m_engine->getLevel()) break; //Weird, but OK

            if (level < 1 || level > m_engine->getMap()->getMapDepth()) break;

            STAIR dir = l_event->direction == STAIR_UP ? STAIR_DOWN : STAIR_UP;
            for (EntityId entity : getEngine()->getEntities()->get()) {
                StairComponent* l_stair = getEngine()->getComponents()->get<StairComponent>(entity);
                if (l_stair == nullptr) continue;
                Location l_stairLoc = m_engine->getEntities()->getLocation (entity);
                if (l_stair->direction == dir && l_stairLoc.z == level) {
                    Location oldLocation = m_engine->getEntities()->getLocation (m_engine->getEntities()->getPlayer());
                    m_engine->getEntities()->setLocation (m_engine->getEntities()->getPlayer(), l_stairLoc);
                    m_engine->setLevel (level);
                    ChangeLocationEvent* changeEvent = new ChangeLocationEvent();
                    changeEvent->entity = m_engine->getEntities()->getPlayer();
                    changeEvent->oldLocation = oldLocation;
                    changeEvent->newLocation = l_stairLoc;
                    getEngine()->raiseEvent (changeEvent);
                    break;
                }
            }
        }
        default: break;
    }
}
