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
            Entity* l_entity = m_engine->getEntities()->getEntity(l_event->entity);
            SpriteComponent* l_sprite = m_engine->getEntities()->getSprites()->get (l_entity->getId());
            if (!l_sprite) return;
            unsigned int newX = l_sprite->xPos;
            unsigned int newY = l_sprite->yPos;
            switch (l_event->direction) {
                case Direction::North:  newY--; break;
                case Direction::South:  newY++; break;
                case Direction::West:   newX--; break;
                case Direction::East:   newX++; break;
                default: return;
            }

            //Check if we're running into a collidable or something
            std::map<EntityId, SpriteComponent>& l_sprites = m_engine->getEntities()->getSprites()->getAll();
            std::map<EntityId, SpriteComponent>::iterator it = l_sprites.begin();
            for (; it != l_sprites.end(); it++) {
                // There is an entity here
                if (it->second.xPos == newX && it->second.yPos == newY) {
                    // Check if it's a collidable
                    if (m_engine->getEntities()->getColliders()->get (it->first)) return;
                }

            }
            l_sprite->xPos = newX;
            l_sprite->yPos = newY;
            break;
        }
        default: break;
    }
}
