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
        MoveEntityEvent* l_event = new MoveEntityEvent();
        l_event->entity = iter->first;
        l_event->direction = getRandomDirection();
        getEngineRef()->raiseEvent (l_event);
    }
    getEngineRef()->swapTurn();
}

MoveEntityEvent::DIRECTION NpcSystem::getRandomDirection () {
    unsigned int dir = rand () % 5;
    return static_cast<MoveEntityEvent::DIRECTION>(dir);
}
