#include "npc_system.h"
#include "npc_component.h"
#include "los_algorithm.h"
#include "algorithm.h"
#include "collider_component.h"
#include <iostream>

unsigned int getPathCost (unsigned int index, void* customData);
unsigned int findNeighbours4 (unsigned int index, unsigned int* neighbours, void* customData);
unsigned int getDistance (unsigned int start, unsigned int end, void* customData);

bool canSeeTarget (GameEngineInterface* engine, EntityId entity, NpcComponent* npc);
bool canAttackTarget (GameEngineInterface* engine, EntityId entity, NpcComponent* npc);

NpcSystem::NpcSystem()
{
    TransitionMap orcs;

    Transition NoneToIdle;
    NoneToIdle.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){ return true; };
    NoneToIdle.endState = NpcState::Idle;
    orcs[NpcState::None].push_back(NoneToIdle);

    Transition IdleToSearching;
    IdleToSearching.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){ return true; };
    IdleToSearching.endState = NpcState::Searching;
    orcs[NpcState::Idle].push_back(IdleToSearching);

    Transition SearchingToHunting;
    SearchingToHunting.condition = canSeeTarget;
    SearchingToHunting.endState = NpcState::Hunting;
    orcs[NpcState::Searching].push_back(SearchingToHunting);
    
    Transition HuntingToAttacking;
    HuntingToAttacking.condition = canAttackTarget;
    HuntingToAttacking.endState = NpcState::Attacking;
    orcs[NpcState::Hunting].push_back(HuntingToAttacking);

    Transition HuntingToSearching;
    HuntingToSearching.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){ 
        return !canSeeTarget (g,e,n); 
    };
    HuntingToSearching.endState = NpcState::Searching;
    orcs[NpcState::Hunting].push_back(HuntingToSearching);

    Transition HuntingNoPath;
    HuntingNoPath.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){return n->path.empty();};
    HuntingNoPath.endState = NpcState::Searching;
    orcs[NpcState::Hunting].push_back(HuntingNoPath);

    Transition AttackingNotPossible;
    AttackingNotPossible.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){
        return !canAttackTarget(g,e,n);
    };
    AttackingNotPossible.endState = NpcState::Hunting;
    orcs[NpcState::Attacking].push_back(AttackingNotPossible);

    m_stateMachine[0] = orcs;
}

void NpcSystem::changeState (EntityId entity, NpcComponent* npc)
{
    switch (npc->state) {
        case NpcState::Hunting:
            // Move towards
            setPathToTarget (entity, npc->target, npc);
            if (!npc->path.empty()) {
                moveTowards (entity, npc->path[0]);
                npc->path.erase(npc->path.begin());
            }
            break;
        case NpcState::Attacking:
            {
                AttackEntityEvent* l_event = new AttackEntityEvent;
                l_event->attacker = entity;
                l_event->defender = npc->target;
                getEngine()->raiseEvent (l_event);
                break;
            }
        case NpcState::Searching:
            npc->target = getEngine()->getEntities()->getPlayer();
            // Walk around
            break;
        case NpcState::Idle:
            // Nothing to do
            break;
        case NpcState::None:
            // Entry state
            break;
        default:
            LOG(ERROR) << "Invalid state detected: " << (int)npc->state << std::endl;
            break;
    };
}

bool canSeeTarget (GameEngineInterface* engine, EntityId entity, NpcComponent* npc)
{
    LosAlgorithm los;
    los.initialise (engine);

    return (los.hasLos(
        engine->getEntities()->getLocation (npc->target),
        engine->getEntities()->getLocation (entity)));
}

bool canAttackTarget (GameEngineInterface* engine, EntityId entity, NpcComponent* npc)
{
    EntityHolder l_entities;
    Location location = engine->getEntities()->getLocation (entity);
    l_entities = engine->getMap()->findEntitiesNear (location, 1);
    for (EntityId iter : l_entities) {
        if (iter == npc->target) {
            Location oLoc = engine->getEntities()->getLocation (iter);
            if (location.x != oLoc.x && location.y != oLoc.y) continue;
            return true;
        }
    }
    return false;
}

void NpcSystem::setPathToTarget (EntityId entity, EntityId target, NpcComponent* npc)
{
    Algorithm algo;
    algo.setCustomData (getEngine());
    algo.setCostFunction (getPathCost);
    algo.setDistanceFunction (getDistance);
    algo.setNeighbourFunction (findNeighbours4);
    algo.setNumNeighbours (4);

    unsigned int startIndex = getEngine()->getMap()->map2index (
            getEngine()->getEntities()->getLocation (entity));
    unsigned int endIndex = getEngine()->getMap()->map2index (
            getEngine()->getEntities()->getLocation (target));

    PathVector l_path;
    //std::cout << "Path from " << enemyLoc << " to " << playerLoc << std::endl;
    algo.findPath (startIndex, endIndex, l_path);

    if (l_path.empty()) {
        return;
    }

    // Reset path
    npc->path.clear();
    for (unsigned int ii = 0; ii < l_path.size(); ii++) {
        Location tempLoc;
        m_engine->getMap()->index2map(l_path[ii], tempLoc);
        npc->path.push_back (tempLoc);
        //std::cout << "Step " << ii << ": " << tempLoc << std::endl;
    }
}

void NpcSystem::moveTowards (EntityId entity, const Location& location)
{
    MoveEntityEvent* l_event = new MoveEntityEvent();
    l_event->entity = entity;
    l_event->newLocation = location;
    getEngine()->raiseEvent (l_event);
}

void NpcSystem::handleEvent (const Event* event)
{

}

void NpcSystem::update ()
{
    if (getEngine()->isPlayerTurn()) return;
    for (EntityId entity : getEngine()->getEntities()->get()) {
        NpcComponent* npc = getEngine()->getComponents()->get<NpcComponent> (entity);
        if (npc == 0) continue;
        
        TransitionMap& transitions = m_stateMachine[npc->stateMachine];
        for (Transition& transition : transitions[npc->state]) {
            if (transition.condition (getEngine(), entity, npc)) {
                LOG(INFO) << "Changing state from " << (int) npc->state 
                    << " to " << (int) transition.endState 
                    << " for " << entity
                    << std::endl;
                npc->state = transition.endState;
                break;
            }
        }
        // handleCurrentState (entity, npc);
        changeState (entity, npc);
    }
    getEngine()->swapTurn();
}
/*
void NpcSystem::update ()
{
    if (getEngine()->isPlayerTurn()) return;

    for (EntityId l_entity : getEngine()->getEntities()->get()) {
        NpcComponent* l_npc = getEngine()->getComponents()->get<NpcComponent> (l_entity);
        Location l_loc = getEngine()->getEntities()->getLocation(l_entity);

        EntityId player = getEngine()->getEntities()->getPlayer();
        Location playerLoc = getEngine()->getEntities()->getLocation(player);

        if (l_npc == 0) continue;
        if (l_loc.z != playerLoc.z) continue;

        // Check if player is attackable
        if (canAttackPlayer (l_loc)) {
            AttackEntityEvent* l_event = new AttackEntityEvent;
            l_event->attacker = l_entity;
            l_event->defender = getEngine()->getEntities()->getPlayer();;
            getEngine()->raiseEvent (l_event);
        }

        // Check if player is nearby
        Location newLoc = getPlayerDirectionIfNearby (l_entity);
        if (l_npc->path.size()) {
            newLoc = l_npc->path[0]; l_npc->path.erase(l_npc->path.begin());
            //std::cout << "Have path, going to " << newLoc << std::endl;
        } else {
            newLoc = getRandomDirection(l_loc);
        }
        MoveEntityEvent* l_event = new MoveEntityEvent();
        l_event->entity = l_entity;
        l_event->newLocation = newLoc;
        getEngine()->raiseEvent (l_event);
    }
    getEngine()->swapTurn();
}*/

/*
Location NpcSystem::getRandomDirection (const Location& oldLocation) {
    DIRECTION dir = Utility::randBetween (Direction::None, Direction::West);
    Location newLocation = oldLocation;
    switch (dir) {
        case Direction::North: newLocation.y--; break;
        case Direction::West: newLocation.x--;  break;
        case Direction::South: newLocation.y++; break;
        case Direction::East: newLocation.x++;  break;
    }
    return newLocation;
}
*/

/*
Location NpcSystem::getPlayerDirectionIfNearby (EntityId npc)
{
    EntityId player = getEngine()->getEntities()->getPlayer();
    Location playerLoc = getEngine()->getEntities()->getLocation(player);

    Location enemyLoc = getEngine()->getEntities()->getLocation (npc);
    NpcComponent* enemyNpc = getEngine()->getComponents()->get<NpcComponent> (npc);
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
        //std::cout << "Path from " << enemyLoc << " to " << playerLoc << std::endl;
        algo.findPath (startIndex, endIndex, l_path);

        if (l_path.size()) {
            enemyNpc->path.clear();
            for (unsigned int ii = 0; ii < l_path.size(); ii++) {
                Location tempLoc;
                m_engine->getMap()->index2map(l_path[ii], tempLoc);
                enemyNpc->path.push_back (tempLoc);
                //std::cout << "Step " << ii << ": " << tempLoc << std::endl;

            }
            m_engine->getMap()->index2map(l_path[0], newLoc);
        }
        //std::cout << "Moving from " << enemyLoc << " to " << newLoc << std::endl;
        return newLoc;
    }
    return enemyLoc;
}
*/

/*
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
*/

unsigned int getPathCost (unsigned int index, void* customData)
{
    GameEngineInterface* l_engine = static_cast<GameEngineInterface*> (customData);
    Tile& tile = l_engine->getMap()->getTile(index);

    for (EntityId entity : tile.entities()) {
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
    //std::cout << "Finding neighbours of " << loc << std::endl;

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
