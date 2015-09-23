#include "npc_system.h"
#include "npc_component.h"
#include <cstdlib>

void NpcSystem::handleEvent (const Event* event)
{

}

void NpcSystem::update ()
{
    if (getEngine()->isPlayerTurn()) return;

    for (EntityId l_entity = 1; l_entity < getEngine()->getEntities()->getMaxId(); l_entity++) {
        NpcComponent* l_npc = getEngine()->getComponents()->get<NpcComponent> (l_entity);
        Location l_loc = getEngine()->getEntities()->getLocation(l_entity);
        if (l_npc == 0) continue;
        if (l_loc.z != getEngine()->getLevel()) continue;

        DIRECTION dir = Direction::None;
        // Check if player is attackable
        dir = getPlayerDirectionIfAttackable (l_entity);
        if (dir != Direction::None) {
            AttackEntityEvent* l_event = new AttackEntityEvent;
            l_event->entity = l_entity;
            l_event->direction = dir;
            getEngine()->raiseEvent (l_event);
        }

        // Check if player is nearby
        dir = getPlayerDirectionIfNearby (l_entity);
        if (dir == Direction::None) {
            dir = getRandomDirection();
        }
        MoveEntityEvent* l_event = new MoveEntityEvent();
        l_event->entity = l_entity;
        l_event->newLocation = l_loc;
        getEngine()->raiseEvent (l_event);
    }
    getEngine()->swapTurn();
}

DIRECTION NpcSystem::getRandomDirection () {
    return rand () % Direction::NorthEast;
}

DIRECTION NpcSystem::getPlayerDirectionIfNearby (EntityId enemy)
{
    EntityId player = getEngine()->getEntities()->getPlayer();
    Location playerLoc = getEngine()->getEntities()->getLocation(player);
    Location enemyLoc = getEngine()->getEntities()->getLocation(enemy);

    int xDiff = playerLoc.x - enemyLoc.x;
    int yDiff = playerLoc.y - enemyLoc.y;
    if ((xDiff > -5 && xDiff < 5) &&
        (yDiff > -5 && yDiff < 5) &&
        (enemyLoc.z == getEngine()->getLevel())) {
        if (abs(xDiff) > abs(yDiff)) {
            // Move horizontally first
            if (xDiff > 0) return Direction::East;
            return Direction::West;
        } else {
            // Move vertically first
            if (yDiff > 0) return Direction::South;
            return Direction::North;
        }
    }

    return Direction::None;
}

DIRECTION NpcSystem::getPlayerDirectionIfAttackable (EntityId entity) {

    EntityHolder l_entities;
    EntityId player = getEngine()->getEntities()->getPlayer();

    l_entities = getEngine()->getEntities()->findEntitiesToThe (Direction::North, entity);
    for (EntityId entity : l_entities) {
        if (entity == player) return Direction::North;
    }

    l_entities = getEngine()->getEntities()->findEntitiesToThe (Direction::East, entity);
    for (EntityId entity : l_entities) {
            if (entity == player) return Direction::East;
    }

    l_entities = getEngine()->getEntities()->findEntitiesToThe (Direction::South, entity);
    for (EntityId entity : l_entities) {
            if (entity == player) return Direction::South;
    }

    l_entities = getEngine()->getEntities()->findEntitiesToThe (Direction::West, entity);
    for (EntityId entity : l_entities) {
            if (entity == player) return Direction::West;
    }

    return Direction::None;
}

bool NpcSystem::canAttackPlayer (const Location& location)
{
    EntityId player = getEngine()->getEntities()->getPlayer();
    EntityHolder l_entities;

    l_entities = getEngine()->getMap()->findEntitiesNear (location, 1);
    for (EntityId entity : l_entities) {
        if (entity == player) return true;
    }
    return false;
}
