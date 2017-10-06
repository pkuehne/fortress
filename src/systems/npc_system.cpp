#include "npc_system.h"
#include "npc_component.h"
#include "los_algorithm.h"
#include "algorithm.h"
#include "collider_component.h"
#include "description_component.h"
#include <iostream>
#include <cmath>

int getPathCost (const Location& location, void* customData);
unsigned int findNeighbours4 (  const Location& location,
        Location* neighbours,
        void* customData);
unsigned int getDistance (const Location& start, const Location& end, void* customData);

bool canSeeTarget (GameEngineInterface* engine, EntityId entity, NpcComponent* npc);
bool canAttackTarget (GameEngineInterface* engine, EntityId entity, NpcComponent* npc);
bool canMoveTo (GameEngineInterface* engine, Location& location);

EntityId findNearestVisibleMatching(GameState* state,
        const Location& location,
        unsigned int radius,
        std::string name);

NpcSystem::NpcSystem()
{
    StateMachine monster;

    State NoneState;
    Transition NoneToIdle;
    NoneToIdle.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){ return true; };
    NoneToIdle.endState = "Idle";

    NoneState.transitions.push_back(NoneToIdle);
    monster[""] = NoneState;

    State IdleState;
    Transition IdleToSearching;
    IdleToSearching.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){ return true; };
    IdleToSearching.endState = "Searching";
    IdleState.transitions.push_back(IdleToSearching);
    monster["Idle"] = IdleState;

    State SearchingState;
    Transition SearchingToHunting;
    SearchingToHunting.condition = canSeeTarget;
    SearchingToHunting.endState = "Hunting";
    SearchingState.transitions.push_back(SearchingToHunting);
    monster["Searching"] = SearchingState;

    State HuntingState;
    Transition HuntingToAttacking;
    HuntingToAttacking.condition = canAttackTarget;
    HuntingToAttacking.endState = "Attacking";
    HuntingState.transitions.push_back(HuntingToAttacking);

    Transition HuntingToSearching;
    HuntingToSearching.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){
        return n->path.empty() && !canSeeTarget (g,e,n);
    };
    HuntingToSearching.endState = "Searching";
    HuntingState.transitions.push_back(HuntingToSearching);

    Transition HuntingNoPath;
    HuntingNoPath.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){return n->path.empty();};
    HuntingNoPath.endState = "Searching";
    HuntingState.transitions.push_back(HuntingNoPath);
    monster["Hunting"] = HuntingState;

    State AttackingState;
    Transition AttackingNotPossible;
    AttackingNotPossible.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){
        return !canAttackTarget(g,e,n);
    };
    AttackingNotPossible.endState = "Hunting";
    AttackingState.transitions.push_back(AttackingNotPossible);
    monster["Attacking"] = AttackingState;

    m_stateMachines["monster"] = monster;

    // Humans
    StateMachine human;
    human[""] = NoneState;

    Transition IdleToSeeking;
    IdleToSeeking.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){return true;};
    IdleToSeeking.endState = "Seeking";
    IdleState.transitions.clear();
    IdleState.transitions.push_back(IdleToSeeking);
    human["Idle"] = IdleState;

    State SeekingState;
    Transition SeekingToMoving;
    SeekingToMoving.condition = [](GameEngineInterface* g, EntityId e, NpcComponent* n){return n->target != 0;};
    SeekingToMoving.endState = "Moving";
    SeekingState.transitions.push_back(SeekingToMoving);
    human["Seeking"] = SeekingState;

    State MovingState;
    Transition MovingToAttacking;
    MovingToAttacking.condition = canAttackTarget;
    MovingToAttacking.endState = "Attacking";
    MovingState.transitions.push_back(MovingToAttacking);
    human["Moving"] = MovingState;

    human["Attacking"] = AttackingState;
    m_stateMachines["human"] = human;
}

void NpcSystem::changeState (EntityId entity, NpcComponent* npc)
{
    if (npc->state == "") {
        // Entry state
    }
    if (npc->state == "Hunting")
    {
        // Move towards
        setPathToTarget (entity, npc->target, npc);
        if (!npc->path.empty()) {
            moveTowards (entity, npc->path[0]);
            npc->path.erase(npc->path.begin());
        }
    }
    if (npc->state == "Attacking")
    {
        AttackEntityEvent* l_event = new AttackEntityEvent;
        l_event->attacker = entity;
        l_event->defender = npc->target;
        getEngine()->raiseEvent (l_event);
    }
    if (npc->state == "Searching")
    {
        npc->target = getEngine()->state()->player();
        // Walk around
    }
    if (npc->state == "Wandering")
    {
        //Todo: Remove, kept for reference purpose
        LOG(INFO) << "Wandering around" << std::endl;
        Location oldLoc = getEngine()->state()->location(entity);
        Location newLoc = getEngine()->state()->location(oldLoc,
                npc->lastDirection);
        unsigned int c = 0;
        while (c++ < 30 && (newLoc == oldLoc ||
                    !canMoveTo(getEngine(), newLoc))) {
            npc->lastDirection = static_cast<Direction>(
                    Utility::randBetween (1, 4));
            newLoc = getEngine()->state()->location(oldLoc,
                    npc->lastDirection);
        }

        moveTowards (entity, newLoc);
    }
    if (npc->state == "Seeking")
    {
        npc->target = findNearestVisibleMatching(
                getEngine()->state(),
                getEngine()->state()->location(entity),
                npc->losDistance,
                npc->attribs["seek_target"]);
    }
    if (npc->state == "Moving")
    {
        // Move towards
        setPathToTarget (entity, npc->target, npc);
        if (!npc->path.empty()) {
            moveTowards (entity, npc->path[0]);
            npc->path.erase(npc->path.begin());
        }
    }
}

bool canSeeTarget (GameEngineInterface* engine, EntityId entity, NpcComponent* npc)
{
    LosAlgorithm los;
    los.initialise (engine);

    return (los.hasLos(
                engine->state()->location(npc->target),
                engine->state()->location(entity)));
}

// Todo: Rename to "Completed move" or similar
bool canAttackTarget (GameEngineInterface* engine, EntityId entity, NpcComponent* npc)
{
    EntityHolder l_entities;
    Location location = engine->state()->location(entity);
    l_entities = engine->state()->map()->findEntitiesNear (location, 1);
    for (EntityId iter : l_entities) {
        if (iter == npc->target) {
            Location oLoc = engine->state()->location(iter);
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
    algo.findPath ( getEngine()->state()->location(entity),
            getEngine()->state()->location(target),
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
    const EntityHolder& entities = getEngine()->state()->entities();
    for (EntityId entity : entities) {
        NpcComponent* npc =
            getEngine()->state()->components()->get<NpcComponent> (entity);
        if (npc == 0) continue;

        State currentState = m_stateMachines[npc->stateMachine][npc->state];
        TransitionList& transitions = currentState.transitions;
        for (Transition& transition : transitions) {
            if (transition.condition (getEngine(), entity, npc)) {
                LOG(INFO) << "Changing state from <" << npc->state
                    << "> to <" << transition.endState
                    << "> for " << entity
                    << std::endl;
                if (currentState.onLeave) {
                    currentState.onLeave(getEngine(), entity, npc);
                }
                npc->state = transition.endState;
                currentState = m_stateMachines[npc->stateMachine][npc->state];
                if (currentState.onEntry) {
                    currentState.onEntry(getEngine(), entity, npc);
                }
                break;
            }
        }
        if (currentState.onUpdate) {
            currentState.onUpdate(getEngine(), entity, npc);
        }
        changeState (entity, npc);
    }
}

int getPathCost (const Location& location, void* customData)
{
    GameEngineInterface* l_engine = static_cast<GameEngineInterface*> (customData);
    Tile& tile = l_engine->state()->tile(location);

    for (EntityId entity : tile.entities()) {
        if (entity == l_engine->state()->player()) continue;
        if (l_engine->state()->components()->get<ColliderComponent>(entity)) return -999;
    }
    return 1;
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
        if (l_engine->state()->map()->isValidTile (neighbour)) {
            if (getPathCost (neighbour, l_engine) > 0)
                neighbours[count++] = neighbour;
        }
    }

    //std::cout << "Returning " << count << " neighbours "<< std::endl;
    return count;
}

unsigned int getDistance (const Location& start, const Location& end, void* customData)
{
    return (abs (start.x - end.x) + abs(start.y - end.y));
}

bool canMoveTo (GameEngineInterface* engine, Location& location)
{
    const EntityHolder& l_targets = engine->state()->tile(location).entities();
    for (EntityId l_target : l_targets) {
        if (engine->state()->components()->get<ColliderComponent> (l_target)) {
            return false;
        }
    }
    return true;
}

EntityId findNearestVisibleMatching(GameState* state,
        const Location& location,
        unsigned int radius,
        std::string name)
{
    EntityId retval = 0;
    unsigned int minDist = 1000.0;
    EntityHolder entities = state->map()->findEntitiesNear(location, radius);
    for (EntityId entity : entities) {
        Location loc = state->location(entity);
        unsigned int dist = abs(loc.x-location.x)+abs(loc.y-location.y);
        auto* desc =
            state->components()->get<DescriptionComponent> (entity);
        if (desc == 0) continue;
        if (desc->title == name && dist < minDist) {
            retval = entity;
        }
    }
    return retval;
}

