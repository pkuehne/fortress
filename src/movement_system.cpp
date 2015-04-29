#include "movement_system.h"
#include "event.h"
#include "gameengine.h"
#include "entity.h"
#include <iostream>

void MovementSystem::handleEvent (const Event* event)
{
    GameEngine* l_engine = GameEngine::getEngine();

    switch (event->getType()) {
        case EVENT_MOVE_ENTITY: {
            const MoveEntityEvent* l_event = dynamic_cast<const MoveEntityEvent*> (event);
            Entity* l_entity = l_event->entity;
            SpriteComponent* l_sprite = l_engine->getEntities().getSprites().get (l_entity);
            if (!l_sprite) return;
            unsigned int newX = l_sprite->xPos;
            unsigned int newY = l_sprite->yPos;
            switch (l_event->direction) {
                case MoveEntityEvent::UP:    newY--; break;
                case MoveEntityEvent::DOWN:  newY++; break;
                case MoveEntityEvent::LEFT:  newX--; break;
                case MoveEntityEvent::RIGHT: newX++; break;
                default: return;
            }
            std::map<Entity*, SpriteComponent>& l_sprites = l_engine->getEntities().getSprites().getAll();
            std::map<Entity*, SpriteComponent>::iterator it = l_sprites.begin();
            for (; it != l_sprites.end(); it++) {
                if (it->second.xPos == newX && it->second.yPos == newY) {
                    if (l_engine->getEntities().getColliders().get (it->first)) return;
                }

            }
            l_sprite->xPos = newX;
            l_sprite->yPos = newY;
            break;
        }
        default: break;
    }
}
