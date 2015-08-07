#include "sprite_system.h"
#include "gameengine.h"
#include "event.h"
#include "sprite_component.h"
#include <iostream>

void SpriteSystem::handleEvent (const Event* event) {
    switch (event->getType()) {
        case EVENT_ADD_ENTITY: {
            const AddEntityEvent* l_event = dynamic_cast<const AddEntityEvent*> (event);
            Entity* l_entity = m_engine->getEntities()->getEntity (l_event->entity);
            if (!l_entity) break;
            if (l_entity->getName() == "Wall") {
                handleAddWallEvent (l_event->entity);
            }
            break;
        }
        default: break;
    }
}

void SpriteSystem::handleAddWallEvent (EntityId a_entity) {
    updateWallSprite (a_entity);

    SpriteComponent* l_sprite = m_engine->getEntities()->getSprites()->get (a_entity);
    if (!l_sprite) return;

    EntityId left   = findWallEntity (l_sprite->xPos-1, l_sprite->yPos);
    EntityId up     = findWallEntity (l_sprite->xPos, l_sprite->yPos-1);
    EntityId right  = findWallEntity (l_sprite->xPos+1, l_sprite->yPos);
    EntityId down   = findWallEntity (l_sprite->xPos, l_sprite->yPos+1);

    if (left)   updateWallSprite (left);
    if (up)     updateWallSprite (up);
    if (right)  updateWallSprite (right);
    if (down)   updateWallSprite (down);
}

void SpriteSystem::updateWallSprite (EntityId a_entity) {
    SpriteComponent* l_sprite = m_engine->getEntities()->getSprites()->get (a_entity);
    if (!l_sprite) return;

    EntityId left   = findWallEntity (l_sprite->xPos-1, l_sprite->yPos);
    EntityId up     = findWallEntity (l_sprite->xPos, l_sprite->yPos-1);
    EntityId right  = findWallEntity (l_sprite->xPos+1, l_sprite->yPos);
    EntityId down   = findWallEntity (l_sprite->xPos, l_sprite->yPos+1);

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

EntityId SpriteSystem::findWallEntity (unsigned int x, unsigned int y) {
    std::map<EntityId, SpriteComponent>& l_sprites = m_engine->getEntities()->getSprites()->getAll();
    std::map<EntityId, SpriteComponent>::iterator iter = l_sprites.begin();
    for (; iter != l_sprites.end(); iter++) {
        EntityId l_entity = iter->first;
        DescriptionComponent* l_desc = m_engine->getEntities()->getDescriptions()->get (l_entity);
        if (iter->second.xPos == x &&
            iter->second.yPos == y &&
            l_desc->title == "Wall") {
            return l_entity;
        }
    }
    return 0;
}
