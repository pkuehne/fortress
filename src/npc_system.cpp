#include "npc_system.h"
#include <cstdlib>

void NpcSystem::handleEvent (const Event* event)
{

}

void NpcSystem::update ()
{
    if (getEngineRef()->isPlayerTurn()) return;
    std::map<Entity*, SpriteComponent>& l_sprites = getEngineRef()->getEntities()->getSprites()->getAll();
    std::map<Entity*, SpriteComponent>::iterator iter = l_sprites.begin();

    for (; iter != l_sprites.end(); iter++) {
        if (!iter->first->hasTag (MONSTER)) continue;

        // Check if player is nearby
        MoveEntityEvent::DIRECTION dir = getPlayerDirectionIfNearby (iter->first);
        if (dir == MoveEntityEvent::NONE) {
            dir = getRandomDirection();
        }
        MoveEntityEvent* l_event = new MoveEntityEvent();
        l_event->entity = iter->first->getId();
        l_event->direction = dir;
        getEngineRef()->raiseEvent (l_event);
    }
    getEngineRef()->swapTurn();
}

MoveEntityEvent::DIRECTION NpcSystem::getRandomDirection () {
    unsigned int dir = rand () % 5;
    return static_cast<MoveEntityEvent::DIRECTION>(dir);
}

MoveEntityEvent::DIRECTION NpcSystem::getPlayerDirectionIfNearby (Entity* enemy)
{
    Entity* player = getEngineRef()->getEntities()->getPlayer();
    SpriteComponent* playerSprite = getEngineRef()->getEntities()->getSprites()->get (player);
    SpriteComponent* enemySprite = getEngineRef()->getEntities()->getSprites()->get (enemy);

    int xDiff = playerSprite->xPos - enemySprite->xPos;
    int yDiff = playerSprite->yPos - enemySprite->yPos;
    //std::cout << "Diff - Enemy:" << enemy->getId() << " x= " << xDiff << " y= " << yDiff << std::endl;
    if ((xDiff > -5 && xDiff < 5) &&
        (yDiff > -5 && yDiff < 5)) {
        if (abs(xDiff) > abs(yDiff)) {
            // Move horizontally first
            if (xDiff > 0) return MoveEntityEvent::RIGHT;
            return MoveEntityEvent::LEFT;
        } else {
            // Move vertically first
            if (xDiff > 0) return MoveEntityEvent::DOWN;
            return MoveEntityEvent::UP;
        }
    }

    return MoveEntityEvent::NONE;
}
