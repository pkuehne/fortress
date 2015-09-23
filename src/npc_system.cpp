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

        // Check if player is attackable
        if (canAttackPlayer (l_loc)) {
            AttackEntityEvent* l_event = new AttackEntityEvent;
            l_event->attacker = l_entity;
            l_event->defender = getEngine()->getEntities()->getPlayer();;
            getEngine()->raiseEvent (l_event);
        }

        // Check if player is nearby
        Location newLoc = getPlayerDirectionIfNearby (l_loc);
        if (newLoc == l_loc) {
            newLoc = getRandomDirection(l_loc);
        }
        MoveEntityEvent* l_event = new MoveEntityEvent();
        l_event->entity = l_entity;
        l_event->newLocation = newLoc;
        getEngine()->raiseEvent (l_event);
    }
    getEngine()->swapTurn();
}

Location NpcSystem::getRandomDirection (const Location& oldLocation) {
    DIRECTION dir = rand () % Direction::NorthEast;
    Location newLocation = oldLocation;
    switch (dir) {
        case Direction::North: newLocation.y--; break;
        case Direction::West: newLocation.x--;  break;
        case Direction::South: newLocation.y++; break;
        case Direction::East: newLocation.x++;  break;
    }
    return newLocation;
}

Location NpcSystem::getPlayerDirectionIfNearby (const Location& enemyLoc)
{
    EntityId player = getEngine()->getEntities()->getPlayer();
    Location playerLoc = getEngine()->getEntities()->getLocation(player);
    Location newLoc = enemyLoc;

    int xDiff = playerLoc.x - enemyLoc.x;
    int yDiff = playerLoc.y - enemyLoc.y;
    if ((xDiff > -5 && xDiff < 5) &&
        (yDiff > -5 && yDiff < 5) &&
        (enemyLoc.z == getEngine()->getLevel())) {
        if (abs(xDiff) > abs(yDiff)) {
            // Move horizontally first
            if (xDiff > 0) {
                newLoc.x++;
            } else {
                newLoc.x--;
            }
        } else {
            // Move vertically first
            if (yDiff > 0) {
                newLoc.y++;
            } else {
                newLoc.y--;
            }
        }
        return newLoc;
    }

    return enemyLoc;
}

bool NpcSystem::canAttackPlayer (const Location& location)
{
    EntityId player = getEngine()->getEntities()->getPlayer();
    EntityHolder l_entities;

    l_entities = getEngine()->getMap()->findEntitiesNear (location, 1);
    for (EntityId entity : l_entities) {
        if (entity == player) {
            Location oLoc = getEngine()->getEntities()->getLocation (entity);
            if (location.x != oLoc.x && location.y != oLoc.y) continue;
            return true;
        }
    }
    return false;
}
