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
            LocationComponent* l_location = m_engine->getEntities()->getLocations()->get (l_entity);
            if (!l_location) return;
            unsigned int newX = l_location->x;
            unsigned int newY = l_location->y;
            switch (l_event->direction) {
                case Direction::North:  newY--; break;
                case Direction::South:  newY++; break;
                case Direction::West:   newX--; break;
                case Direction::East:   newX++; break;
                default: return;
            }

            //Check if we're running into a collidable or stairs, etc
            {
                std::map<EntityId, LocationComponent>& l_locations = m_engine->getEntities()->getLocations()->getAll();
                std::map<EntityId, LocationComponent>::iterator it = l_locations.begin();
                for (; it != l_locations.end(); it++) {
                    // There is an entity here
                    if (it->second.x == newX && it->second.y == newY && it->second.z == m_engine->getLevel()) {
                        // Check if it's a collidable
                        if (m_engine->getEntities()->getColliders()->get (it->first)) {
                            return; // Don't update position if it's a collidable
                        }
                        // Check if it's a stair
                        StairComponent* l_stair = m_engine->getEntities()->getStairs()->get (it->first);
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
            }

            l_location->x = newX;
            l_location->y = newY;
            break;
        }
        case EVENT_CHANGE_LEVEL: {
            const ChangeLevelEvent* l_event = dynamic_cast<const ChangeLevelEvent*> (event);
            unsigned int level = l_event->level;
            if (level == m_engine->getLevel()) break; //Weird, but OK

            if (level < 1) break;
            if (level > m_engine->getMaxLevel()) {
                GameOverWindow* l_win = new GameOverWindow();
                l_win->initialise (m_engine, m_engine);
                m_engine->getWindows()->pushWindow (l_win);
                break;
            }

            LocationComponent* l_location = m_engine->getEntities()->getLocations()->get (m_engine->getEntities()->getPlayer());
            std::map<EntityId, StairComponent>& l_stairs = m_engine->getEntities()->getStairs()->getAll();
            std::map<EntityId, StairComponent>::iterator iter = l_stairs.begin();
            STAIR dir = l_event->direction == STAIR_UP ? STAIR_DOWN : STAIR_UP;
            for (; iter != l_stairs.end(); iter++) {
                LocationComponent* l_stairLoc = m_engine->getEntities()->getLocations()->get (iter->first);
                if (iter->second.direction == dir && l_stairLoc->z == level) {
                    l_location->x = l_stairLoc->x;
                    l_location->y = l_stairLoc->y;
                    l_location->z = l_stairLoc->z;
                }
            }
            m_engine->setLevel (level);
        }
        default: break;
    }
}
