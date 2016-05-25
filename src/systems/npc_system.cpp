#include "npc_system.h"
#include "npc_component.h"
#include "los_algorithm.h"
#include "algorithm.h"
#include "collider_component.h"
#include <iostream>

/*
unsigned int getPathCost (unsigned int index, void* customData);
unsigned int findNeighbours4 (unsigned int index, unsigned int* neighbours, void* customData);
unsigned int getDistance (unsigned int start, unsigned int end, void* customData);
*/

unsigned int getPathCost (const Location& location, void* customData);
unsigned int findNeighbours4 (  const Location& location,
                                Location* neighbours,
                                void* customData);
unsigned int getDistance (const Location& start, const Location& end, void* customData);

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

    // Humans
    TransitionMap humans;
    humans[NpcState::None].push_back(NoneToIdle);

    Transition IdleToWandering;
    IdleToWandering.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){return true;};
    IdleToWandering.endState = NpcState::Wandering;
    humans[NpcState::Idle].push_back(IdleToWandering);

    m_stateMachine[1] = humans;
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
        case NpcState::Wandering:
            {
                LOG(INFO) << "Wandering around" << std::endl;
                Location oldLoc = getEngine()->getEntities()->getLocation (entity);
                Location newLoc = oldLoc;
                unsigned int c = 0;
                while (c++ < 30 && (newLoc == oldLoc || npc->lastDirection == Direction::None)) {
                    npc->lastDirection = static_cast<Direction>(Utility::randBetween (1, 4));
                    newLoc = getEngine()->getMap()->location(
                            getEngine()->getEntities()->getLocation (entity),
                            npc->lastDirection);
                }

                moveTowards (entity, newLoc);
            }
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

    PathVector l_path;
    //std::cout << "Path from " << enemyLoc << " to " << playerLoc << std::endl;
    algo.findPath ( getEngine()->getEntities()->getLocation (entity),
                    getEngine()->getEntities()->getLocation (target),
                    l_path);

    if (l_path.empty()) {
        return;
    }

    // Reset path
    npc->path.clear();
    for (unsigned int ii = 0; ii < l_path.size(); ii++) {
        npc->path.push_back (l_path[ii]);
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
}

// TODO: obsolete
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

unsigned int getPathCost (const Location& location, void* customData)
{
    GameEngineInterface* l_engine = static_cast<GameEngineInterface*> (customData);
    Tile& tile = l_engine->tile(location);

    for (EntityId entity : tile.entities()) {
        if (entity == l_engine->getEntities()->getPlayer()) continue;
        if (l_engine->getComponents()->get<ColliderComponent>(entity)) return -999;
    }
    return 1;

}

//TODO: obsolete
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

unsigned int findNeighbours4 (  const Location& location,
                                Location* neighbours,
                                void* customData)
{
    GameEngineInterface* l_engine = static_cast<GameEngineInterface*> (customData);

    unsigned int count = 0;
    Location neighbour = location;
    int xAdj[] = {-1, 1, 0, 0};
    int yAdj[] = {0, 0, -1, 1};

    for (unsigned int ii = 0; ii < 4; ii++) {
        neighbour = location;
        neighbour.x += xAdj[ii];
        neighbour.y += yAdj[ii];
        if (l_engine->getMap()->isValidTile (neighbour)) {
            if (getPathCost (neighbour, l_engine) > 0)
                neighbours[count++] = neighbour;
        }
    }

    //std::cout << "Returning " << count << " neighbours "<< std::endl;
    return count;
}


// TODO: Obsolete
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

unsigned int getDistance (const Location& start, const Location& end, void* customData)
{
    return (abs (start.x - end.x) + abs(start.y - end.y));
}
