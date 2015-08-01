#include "npc_system.h"
#include <cstdlib>

void NpcSystem::handleEvent (const Event* event)
{

}

void NpcSystem::update ()
{
    if (getEngineRef()->isPlayerTurn()) return;
    std::map<EntityId, SpriteComponent>& l_sprites = getEngineRef()->getEntities()->getSprites()->getAll();
    std::map<EntityId, SpriteComponent>::iterator iter = l_sprites.begin();

    for (; iter != l_sprites.end(); iter++) {
        Entity* l_entity = getEngineRef()->getEntities()->getEntity (iter->first);
        if (!l_entity->hasTag (MONSTER)) continue;

        DIRECTION dir = Direction::None;
        // Check if player is attackable
        dir = getPlayerDirectionIfAttackable (l_entity);
        if (dir != Direction::None) {
            AttackEntityEvent* l_event = new AttackEntityEvent;
            l_event->entity = l_entity->getId();
            l_event->direction = dir;
            getEngineRef()->raiseEvent (l_event);
        }

        // Check if player is nearby
        dir = getPlayerDirectionIfNearby (l_entity);
        if (dir == Direction::None) {
            dir = getRandomDirection();
        }
        MoveEntityEvent* l_event = new MoveEntityEvent();
        l_event->entity = l_entity->getId();
        l_event->direction = dir;
        getEngineRef()->raiseEvent (l_event);
    }
    getEngineRef()->swapTurn();
}

DIRECTION NpcSystem::getRandomDirection () {
    return rand () % Direction::NorthEast;
}

DIRECTION NpcSystem::getPlayerDirectionIfNearby (Entity* enemy)
{
    Entity* player = getEngineRef()->getEntities()->getPlayer();
    SpriteComponent* playerSprite = getEngineRef()->getEntities()->getSprites()->get (player->getId());
    SpriteComponent* enemySprite = getEngineRef()->getEntities()->getSprites()->get (enemy->getId());

    int xDiff = playerSprite->xPos - enemySprite->xPos;
    int yDiff = playerSprite->yPos - enemySprite->yPos;
    if ((xDiff > -5 && xDiff < 5) &&
        (yDiff > -5 && yDiff < 5)) {
        if (abs(xDiff) > abs(yDiff)) {
            // Move horizontally first
            if (xDiff > 0) return Direction::East;
            return Direction::West;
        } else {
            // Move vertically first
            if (xDiff > 0) return Direction::South;
            return Direction::North;
        }
    }

    return Direction::None;
}

DIRECTION NpcSystem::getPlayerDirectionIfAttackable (Entity* entity) {

    std::vector<EntityId> l_entities;
    EntityId player = getEngineRef()->getEntities()->getPlayer()->getId();

    l_entities = getEngineRef()->getEntities()->findEntitiesToThe (Direction::North, entity);
    for (size_t ii = 0; ii < l_entities.size(); ii++) {
        if (l_entities[ii] == player) return Direction::North;
    }

    l_entities = getEngineRef()->getEntities()->findEntitiesToThe (Direction::East, entity);
    for (size_t ii = 0; ii < l_entities.size(); ii++) {
        if (l_entities[ii] == player) return Direction::East;
    }

    l_entities = getEngineRef()->getEntities()->findEntitiesToThe (Direction::South, entity);
    for (size_t ii = 0; ii < l_entities.size(); ii++) {
        if (l_entities[ii] == player) return Direction::South;
    }

    l_entities = getEngineRef()->getEntities()->findEntitiesToThe (Direction::West, entity);
    for (size_t ii = 0; ii < l_entities.size(); ii++) {
        if (l_entities[ii] == player) return Direction::West;
    }

    return Direction::None;
}
