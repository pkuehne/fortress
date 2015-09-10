#include "movement_system.h"
#include "event.h"
#include "gameengine.h"
#include "entity.h"
#include "game_over_window.h"
#include <iostream>

void MovementSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_MOVE_ENTITY: {
            const MoveEntityEvent* l_event = dynamic_cast<const MoveEntityEvent*> (event);
            EntityId l_entity = l_event->entity;
            Location l_location = m_engine->getEntities()->getLocation(l_entity);
            switch (l_event->direction) {
                case Direction::North:  l_location.y--; break;
                case Direction::South:  l_location.y++; break;
                case Direction::West:   l_location.x--; break;
                case Direction::East:   l_location.x++; break;
                default: return;
            }

            //Check if we're running into a collidable or stairs, etc
            {
                EntityHolder& l_targets = m_engine->getTile(l_location).entities;
                for (EntityId l_target : l_targets) {
                    if (m_engine->getEntities()->getColliders()->get (l_target)) {
                        return; // Don't update position if it's a collidable
                    }
                    StairComponent* l_stair = m_engine->getEntities()->getStairs()->get (l_target);
                    if (l_stair && l_entity == m_engine->getEntities()->getPlayer()) {
                        unsigned int level = m_engine->getLevel();
                        level += l_stair->direction == STAIR_UP ? -1 : 1;
                        ChangeLevelEvent* l_event = new ChangeLevelEvent;
                        l_event->level = level;
                        l_event->direction = l_stair->direction;
                        m_engine->raiseEvent (l_event);
                    }

                }
            }

            getEngine()->getEntities()->setLocation (l_event->entity, l_location);
            break;
        }
        case EVENT_CHANGE_LEVEL: {
            const ChangeLevelEvent* l_event = dynamic_cast<const ChangeLevelEvent*> (event);
            unsigned int level = l_event->level;
            if (level == m_engine->getLevel()) break; //Weird, but OK

            if (level < 1 || level > m_engine->getMaxLevel()) break;

            std::map<EntityId, StairComponent>& l_stairs = m_engine->getEntities()->getStairs()->getAll();
            std::map<EntityId, StairComponent>::iterator iter = l_stairs.begin();
            STAIR dir = l_event->direction == STAIR_UP ? STAIR_DOWN : STAIR_UP;
            for (; iter != l_stairs.end(); iter++) {
                Location l_stairLoc = m_engine->getEntities()->getLocation (iter->first);
                if (iter->second.direction == dir && l_stairLoc.z == level) {
                    m_engine->getEntities()->setLocation (m_engine->getEntities()->getPlayer(), l_stairLoc);
                }
            }
            m_engine->setLevel (level);
        }
        default: break;
    }
}
