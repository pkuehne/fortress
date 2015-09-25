#include "npc_system.h"
#include "npc_component.h"
#include "los_algorithm.h"
#include "algorithm.h"
#include "collider_component.h"
#include <iostream>

unsigned int getPathCost (unsigned int index, void* customData);
unsigned int findNeighbours4 (unsigned int index, unsigned int* neighbours, void* customData);
unsigned int getDistance (unsigned int start, unsigned int end, void* customData);

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

    LosAlgorithm los;
    los.initialise (getEngine());

    int xDiff = playerLoc.x - enemyLoc.x;
    int yDiff = playerLoc.y - enemyLoc.y;
    if (abs(xDiff) > 10 || abs(yDiff) > 10) return enemyLoc;
    if (los.hasLos(enemyLoc, playerLoc)) {
        //std::cout << "Orc can see player!" << std::endl;

        Algorithm algo;
        algo.setCustomData (getEngine());
        algo.setCostFunction (getPathCost);
        algo.setDistanceFunction (getDistance);
        algo.setNeighbourFunction (findNeighbours4);
        algo.setNumNeighbours (4);

        unsigned int startIndex = getEngine()->getMap()->map2index (enemyLoc);
        unsigned int endIndex = getEngine()->getMap()->map2index (playerLoc);

        PathVector l_path;
        //std::cout << "Path from " << startIndex << " to " << endIndex << std::endl;
        algo.findPath (startIndex, endIndex, l_path);

        if (l_path.size()) {
            for (unsigned int ii = 0; ii < l_path.size(); ii++) {
                //std::cout << "Step " << ii << ": " << l_path[ii] << std::endl;
            }
            m_engine->getMap()->index2map(l_path[0], newLoc);
        }
        //std::cout << "Moving from " << enemyLoc << " to " << newLoc << std::endl;
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

unsigned int getPathCost (unsigned int index, void* customData)
{
    GameEngineInterface* l_engine = static_cast<GameEngineInterface*> (customData);
    Tile& tile = l_engine->getMap()->getTile(index);

    for (EntityId entity : tile.entities) {
        if (entity == l_engine->getEntities()->getPlayer()) continue;
        if (l_engine->getComponents()->get<ColliderComponent>(entity)) return -999;
    }
    return 1;
}

unsigned int findNeighbours4 (unsigned int index, unsigned int* neighbours, void* customData)
{
    GameEngineInterface* l_engine = static_cast<GameEngineInterface*> (customData);

    unsigned int count = 0;
    unsigned int step = 0;
    Location loc;
    l_engine->getMap()->index2map (index, loc);
    if (l_engine->getMap()->isValidTile (loc.x-1, loc.y, loc.z)) {
        step = l_engine->getMap()->map2index (loc.x-1, loc.y, loc.z);
        if (getPathCost (step, l_engine) == 1)
            neighbours[count++] = step;
    }
    if (l_engine->getMap()->isValidTile (loc.x+1, loc.y, loc.z)) {
        step = l_engine->getMap()->map2index (loc.x+1, loc.y, loc.z);
        if (getPathCost (step, l_engine) == 1)
            neighbours[count++] = step;
    }
    if (l_engine->getMap()->isValidTile (loc.x, loc.y-1, loc.z)) {
        step = l_engine->getMap()->map2index (loc.x, loc.y-1, loc.z);
        if (getPathCost (step, l_engine) == 1)
            neighbours[count++] = step;
    }
    if (l_engine->getMap()->isValidTile (loc.x, loc.y+1, loc.z)) {
        step = l_engine->getMap()->map2index (loc.x, loc.y+1, loc.z);
        if (getPathCost (step, l_engine) == 1)
            neighbours[count++] = step;
    }
    //std::cout << "Returning " << count << " neighbours "<< std::endl;
    return count;
}

unsigned int getDistance (unsigned int start, unsigned int end, void* customData)
{
    GameEngineInterface* l_engine = static_cast<GameEngineInterface*> (customData);

    unsigned int distance = 0;
    Location startLoc;
    Location endLoc;
    l_engine->getMap()->index2map (start, startLoc);
    l_engine->getMap()->index2map (end, endLoc);
    distance = (abs (startLoc.x - endLoc.x) + abs(startLoc.y - endLoc.y));

    return distance;
}
