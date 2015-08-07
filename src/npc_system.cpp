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
        EntityId l_entity = iter->first;
        NpcComponent* l_npc = getEngineRef()->getEntities()->getNpcs()->get (l_entity);
        if (l_npc == 0) continue;

        DIRECTION dir = Direction::None;
        // Check if player is attackable
        dir = getPlayerDirectionIfAttackable (iter->first);
        if (dir != Direction::None) {
            AttackEntityEvent* l_event = new AttackEntityEvent;
            l_event->entity = iter->first;
            l_event->direction = dir;
            getEngineRef()->raiseEvent (l_event);
        }

        // Check if player is nearby
        dir = getPlayerDirectionIfNearby (iter->first);
        if (dir == Direction::None) {
            dir = getRandomDirection();
        }
        MoveEntityEvent* l_event = new MoveEntityEvent();
        l_event->entity = iter->first;
        l_event->direction = dir;
        getEngineRef()->raiseEvent (l_event);
    }
    getEngineRef()->swapTurn();
}

DIRECTION NpcSystem::getRandomDirection () {
    return rand () % Direction::NorthEast;
}

DIRECTION NpcSystem::getPlayerDirectionIfNearby (EntityId enemy)
{
    EntityId player = getEngineRef()->getEntities()->getPlayer();
    LocationComponent* playerLoc = getEngineRef()->getEntities()->getLocations()->get (player);
    LocationComponent* enemyLoc = getEngineRef()->getEntities()->getLocations()->get (enemy);

    int xDiff = playerLoc->x - enemyLoc->x;
    int yDiff = playerLoc->y - enemyLoc->y;
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

DIRECTION NpcSystem::getPlayerDirectionIfAttackable (EntityId entity) {

    std::vector<EntityId> l_entities;
    EntityId player = getEngineRef()->getEntities()->getPlayer();

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
