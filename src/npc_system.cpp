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

        // Check if player is nearby
        DIRECTION dir = getPlayerDirectionIfNearby (l_entity);
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
