#include "movement_system.h"
#include "event.h"
#include "gameengine.h"
#include "entity.h"
#include <iostream>

void MovementSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_MOVE_ENTITY: {
            const MoveEntityEvent* l_event = dynamic_cast<const MoveEntityEvent*> (event);
            EntityId l_entity =l_event->entity;
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

            //Check if we're running into a collidable or something
            std::map<EntityId, LocationComponent>& l_locations = m_engine->getEntities()->getLocations()->getAll();
            std::map<EntityId, LocationComponent>::iterator it = l_locations.begin();
            for (; it != l_locations.end(); it++) {
                // There is an entity here
                if (it->second.x == newX && it->second.y == newY && it->second.z == m_engine->getLevel()) {
                    // Check if it's a collidable
                    if (m_engine->getEntities()->getColliders()->get (it->first)) return;
                }

            }
            l_location->x = newX;
            l_location->y = newY;
            break;
        }
        default: break;
    }
}
