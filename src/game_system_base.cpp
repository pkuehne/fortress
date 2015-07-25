#include "game_system_base.h"
#include <iostream>

std::vector<Entity*> GameSystemBase::findEntitiesAt (unsigned int x, unsigned int y)
{
    return findEntitiesNear (x, y, 0);
}

std::vector<Entity*> GameSystemBase::findEntitiesNear (unsigned int x, unsigned int y, unsigned radius)
{
    std::vector<Entity*> l_entities;

    std::map<Entity*, SpriteComponent>& l_sprites = m_engine->getEntities()->getSprites()->getAll();
    std::map<Entity*, SpriteComponent>::iterator it = l_sprites.begin();
    for (; it != l_sprites.end(); it++) {
        if (it->second.xPos >= x - radius &&
            it->second.xPos <= x + radius &&
            it->second.yPos >= y - radius &&
            it->second.yPos <= y + radius) {
            l_entities.push_back (it->first);
        }
    }

    return l_entities;

}

std::vector<Entity*> GameSystemBase::findEntitiesToThe (DIRECTION a_direction, Entity* a_entity)
{
    std::vector<Entity*> l_entities;

    SpriteComponent* l_sprite = m_engine->getEntities()->getSprites()->get (a_entity);
    if (!l_sprite) return l_entities;
    unsigned int newX = l_sprite->xPos;
    unsigned int newY = l_sprite->yPos;
    switch (a_direction) {
        case Direction::North:  newY--; break;
        case Direction::South:  newY++; break;
        case Direction::West:   newX--; break;
        case Direction::East:   newX++; break;
        default: return l_entities;
    }

    return findEntitiesAt (newX, newY);
}
