#include "sprite_system.h"
#include "gameengine.h"
#include "event.h"
#include "sprite_component.h"
#include <iostream>

void SpriteSystem::handleEvent (const Event* event) {
    switch (event->getType()) {
        case EVENT_MOVE_ENTITY: {
            const MoveEntityEvent* l_event = dynamic_cast<const MoveEntityEvent*> (event);
            Entity* l_entity = l_event->entity;
            SpriteComponent* l_sprite = m_engine->getEntities()->getSprites().get (l_entity);
            if (!l_sprite) return;
            break;
        }
        case EVENT_ADD_ENTITY: {
            const AddEntityEvent* l_event = dynamic_cast<const AddEntityEvent*> (event);
            Entity* l_entity = l_event->entity;
            if (l_entity->getName() != "Wall") break;

            updateWallSprite (l_entity);

            SpriteComponent* l_sprite = m_engine->getEntities()->getSprites().get (l_entity);
            Entity* left    = findWallEntity (l_sprite->xPos-1, l_sprite->yPos);
            Entity* up      = findWallEntity (l_sprite->xPos, l_sprite->yPos-1);
            Entity* right   = findWallEntity (l_sprite->xPos+1, l_sprite->yPos);
            Entity* down    = findWallEntity (l_sprite->xPos, l_sprite->yPos+1);

            if (left)   updateWallSprite (left);
            if (up)     updateWallSprite (up);
            if (right)  updateWallSprite (right);
            if (down)   updateWallSprite (down);

            break;
        }
        default: break;
    }

}

void SpriteSystem::updateWallSprite (Entity* a_entity) {
    SpriteComponent* l_sprite = m_engine->getEntities()->getSprites().get (a_entity);

    Entity* left    = findWallEntity (l_sprite->xPos-1, l_sprite->yPos);
    Entity* up      = findWallEntity (l_sprite->xPos, l_sprite->yPos-1);
    Entity* right   = findWallEntity (l_sprite->xPos+1, l_sprite->yPos);
    Entity* down    = findWallEntity (l_sprite->xPos, l_sprite->yPos+1);

    int sprite_key = 0;
    if (left)   sprite_key |= 8;
    if (up)     sprite_key |= 4;
    if (right)  sprite_key |= 2;
    if (down)   sprite_key |= 1;

    switch (sprite_key) {
        case  0: l_sprite->sprite = 206; break;
        case  1: l_sprite->sprite = 210; break;
        case  2: l_sprite->sprite = 198; break;
        case  3: l_sprite->sprite = 201; break;
        case  4: l_sprite->sprite = 208; break;
        case  5: l_sprite->sprite = 186; break;
        case  6: l_sprite->sprite = 200; break;
        case  7: l_sprite->sprite = 204; break;
        case  8: l_sprite->sprite = 181; break;
        case  9: l_sprite->sprite = 187; break;
        case 10: l_sprite->sprite = 205; break;
        case 11: l_sprite->sprite = 203; break;
        case 12: l_sprite->sprite = 188; break;
        case 13: l_sprite->sprite = 185; break;
        case 14: l_sprite->sprite = 202; break;
        case 15: l_sprite->sprite = 206; break;
    }

}

Entity* SpriteSystem::findWallEntity (unsigned int x, unsigned int y) {
    std::map<Entity*, SpriteComponent>& l_sprites = m_engine->getEntities()->getSprites().getAll();
    std::map<Entity*, SpriteComponent>::iterator iter = l_sprites.begin();
    for (; iter != l_sprites.end(); iter++) {
        if (iter->second.xPos == x &&
            iter->second.yPos == y &&
            iter->second.sprite > 180 &&
            iter->second.sprite < 211) {
            return iter->first;
        }
    }
    return 0;
}
