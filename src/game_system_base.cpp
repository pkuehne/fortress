#include "game_system_base.h"

std::vector<Entity*> GameSystemBase::findEntitiesAt (unsigned int x, unsigned int y)
{
    std::vector<Entity*> l_entities;

    std::map<Entity*, SpriteComponent>& l_sprites = m_engine->getEntities()->getSprites()->getAll();
    std::map<Entity*, SpriteComponent>::iterator it = l_sprites.begin();
    for (; it != l_sprites.end(); it++) {
        if (it->second.xPos == x && it->second.yPos == y) {
            l_entities.push_back (it->first);
        }

    }

    return l_entities;
}


std::vector<Entity*> GameSystemBase::findEntitiesToThe (MoveEntityEvent::DIRECTION a_direction, Entity* a_entity)
{
    std::vector<Entity*> l_entities;

    SpriteComponent* l_sprite = m_engine->getEntities()->getSprites()->get (a_entity);
    if (!l_sprite) return l_entities;
    unsigned int newX = l_sprite->xPos;
    unsigned int newY = l_sprite->yPos;
    switch (a_direction) {
        case MoveEntityEvent::UP:    newY--; break;
        case MoveEntityEvent::DOWN:  newY++; break;
        case MoveEntityEvent::LEFT:  newX--; break;
        case MoveEntityEvent::RIGHT: newX++; break;
        default: return l_entities;
    }

    return findEntitiesAt (newX, newY);
}
