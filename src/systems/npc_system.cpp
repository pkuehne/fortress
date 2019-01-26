#include "npc_system.h"
#include "../algos/algorithm.h"
#include "../algos/los_algorithm.h"
#include "../components/collider_component.h"
#include "../components/description_component.h"
#include "../components/npc_component.h"
#include "../core/game_engine.h"
#include <cmath>
#include <glog/logging.h>
#include <iostream>

int getPathCost(const Location& location, void* customData);
unsigned int findNeighbours4(const Location& location, Location* neighbours,
                             void* customData);
unsigned int getDistance(const Location& start, const Location& end,
                         void* customData = nullptr);

bool canSeeTarget(GameEngine* engine, EntityId entity, NpcComponent* npc);
bool canAttackTarget(GameEngine* engine, EntityId entity, NpcComponent* npc);
bool canMoveTo(GameEngine* engine, Location& location);

EntityId findNearestVisibleMatching(GameState* state, const Location& location,
                                    unsigned int radius, std::string name);

void setPathToTarget(GameEngine* engine, EntityId entity, EntityId target,
                     NpcComponent* npc);

NpcSystem::NpcSystem() {
    createHumanStateMachine();
    createDogStateMachine();
}

void NpcSystem::createHumanStateMachine() {
    StateMachine human;

    State NoneState;
    Transition NoneToIdle;
    NoneToIdle.condition = [](GameEngine* g, EntityId e, NpcComponent* n) {
        return true;
    };
    NoneToIdle.endState = "Idle";
    NoneState.transitions.push_back(NoneToIdle);
    human[""] = NoneState;

    State IdleState;
    Transition IdleToSeeking;
    IdleToSeeking.condition = [](GameEngine* g, EntityId e, NpcComponent* n) {
        return true;
    };
    IdleToSeeking.endState = "Seeking";
    IdleState.transitions.push_back(IdleToSeeking);
    human["Idle"] = IdleState;

    State SeekingState;
    Transition SeekingToMoving;
    SeekingToMoving.condition = [](GameEngine* g, EntityId e, NpcComponent* n) {
        return n->target != 0;
    };
    SeekingToMoving.endState = "Moving";
    SeekingState.transitions.push_back(SeekingToMoving);
    SeekingState.onUpdate = [](GameEngine* g, EntityId e, NpcComponent* n) {
        n->target = findNearestVisibleMatching(
            g->state(), g->state()->location(e), n->losDistance,
            n->attribs["seek_target"]);
    };
    human["Seeking"] = SeekingState;

    State MovingState;
    Transition MovingToAttacking;
    MovingToAttacking.condition = canAttackTarget;
    MovingToAttacking.endState = "Attacking";
    MovingState.transitions.push_back(MovingToAttacking);
    MovingState.onUpdate = [](GameEngine* g, EntityId e, NpcComponent* n) {
        setPathToTarget(g, e, n->target, n);
        if (!n->path.empty()) {
            g->events()->raise(
                std::make_shared<MoveEntityEvent>(e, n->path[0]));
            n->path.erase(n->path.begin());
        }
    };
    human["Moving"] = MovingState;

    State AttackingState;
    Transition AttackingNotPossible;
    AttackingNotPossible.condition = [](GameEngine* g, EntityId e,
                                        NpcComponent* n) {
        return !canAttackTarget(g, e, n);
    };
    AttackingNotPossible.endState = "Seeking";
    AttackingState.transitions.push_back(AttackingNotPossible);
    AttackingState.onUpdate = [](GameEngine* g, EntityId e, NpcComponent* n) {
        g->events()->raise(std::make_shared<AttackEntityEvent>(e, n->target));
    };
    AttackingState.onLeave = [](GameEngine* g, EntityId e, NpcComponent* n) {
        n->target = 0;
    };
    human["Attacking"] = AttackingState;
    m_stateMachines["human"] = human;
}

void NpcSystem::createDogStateMachine() {
    StateMachine dog;

    State NoneState;
    Transition NoneToIdle;
    NoneToIdle.condition = [](GameEngine* g, EntityId e, NpcComponent* n) {
        return true;
    };
    NoneToIdle.endState = "Idle";
    NoneState.transitions.push_back(NoneToIdle);
    dog[""] = NoneState;

    State IdleState;
    Transition IdleToSeeking;
    IdleToSeeking.condition = [](GameEngine* g, EntityId e, NpcComponent* n) {
        // When human is too far away - 5 tiles
        return 0 == findNearestVisibleMatching(g->state(),
                                               g->state()->location(e), 3,
                                               n->attribs["seek_target"]);
        ;
    };
    IdleToSeeking.endState = "Seeking";
    IdleState.transitions.push_back(IdleToSeeking);
    dog["Idle"] = IdleState;

    State SeekingState;
    Transition SeekingToMoving;
    SeekingToMoving.condition = [](GameEngine* g, EntityId e, NpcComponent* n) {
        return true;
    };
    SeekingToMoving.endState = "Moving";
    SeekingState.transitions.push_back(SeekingToMoving);
    SeekingState.onUpdate = [](GameEngine* g, EntityId e, NpcComponent* n) {
        n->target = findNearestVisibleMatching(
            g->state(), g->state()->location(e), n->losDistance,
            n->attribs["seek_target"]);
    };
    dog["Seeking"] = SeekingState;

    State MovingState;
    Transition MovingToIdle;
    MovingToIdle.condition = [](GameEngine* g, EntityId e, NpcComponent* n) {
        // When human is too far away - x tiles
        return 0 != findNearestVisibleMatching(g->state(),
                                               g->state()->location(e), 3,
                                               n->attribs["seek_target"]);
        ;
    };
    MovingToIdle.endState = "Idle";
    MovingState.transitions.push_back(MovingToIdle);
    MovingState.onUpdate = [](GameEngine* g, EntityId e, NpcComponent* n) {
        setPathToTarget(g, e, n->target, n);
        if (!n->path.empty()) {
            g->events()->raise(
                std::make_shared<MoveEntityEvent>(e, n->path[0]));
            n->path.erase(n->path.begin());
        }
    };
    dog["Moving"] = MovingState;

    m_stateMachines["dog"] = dog;
}

bool canSeeTarget(GameEngine* engine, EntityId entity, NpcComponent* npc) {
    LosAlgorithm los;
    los.initialise(engine);

    return (los.hasLos(engine->state()->location(npc->target),
                       engine->state()->location(entity)));
}

bool canAttackTarget(GameEngine* engine, EntityId entity, NpcComponent* npc) {
    EntityHolder l_entities;
    Location location = engine->state()->location(entity);
    l_entities = engine->state()->map()->findEntitiesNear(location, 1);
    for (EntityId iter : l_entities) {
        LOG(INFO) << "Potential: " << iter << " v " << npc->target << std::endl;
        if (iter == npc->target) {
            Location oLoc = engine->state()->location(iter);
            if (location.x != oLoc.x && location.y != oLoc.y)
                continue;
            return true;
        }
    }
    return false;
}

void NpcSystem::onTurn() {
    const EntityHolder& entities = getEngine()->state()->entities();
    for (EntityId entity : entities) {
        NpcComponent* npc =
            getEngine()->state()->components()->get<NpcComponent>(entity);
        if (npc == 0)
            continue;

        State currentState = m_stateMachines[npc->stateMachine][npc->state];
        for (Transition& transition : currentState.transitions) {
            if (transition.condition(getEngine(), entity, npc)) {
                LOG(INFO) << "Changing state from <" << npc->state << "> to <"
                          << transition.endState << "> for " << entity
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
    }
}

int getPathCost(const Location& location, void* customData) {
    GameEngine* l_engine = static_cast<GameEngine*>(customData);
    Tile& tile = l_engine->state()->tile(location);

    for (EntityId entity : tile.entities()) {
        if (entity == l_engine->state()->player())
            continue;
        if (l_engine->state()->components()->get<ColliderComponent>(entity))
            return 99;
    }
    return 1;
}

unsigned int findNeighbours4(const Location& location, Location* neighbours,
                             void* customData) {
    GameEngine* l_engine = static_cast<GameEngine*>(customData);

    unsigned int count = 0;
    Location neighbour = location;
    int xAdj[] = {-1, 1, 0, 0};
    int yAdj[] = {0, 0, -1, 1};

    for (unsigned int ii = 0; ii < 4; ii++) {
        neighbour = location;
        neighbour.x += xAdj[ii];
        neighbour.y += yAdj[ii];
        if (l_engine->state()->map()->isValidTile(neighbour)) {
            if (getPathCost(neighbour, l_engine) > 0)
                neighbours[count++] = neighbour;
        }
    }

    return count;
}

unsigned int getDistance(const Location& start, const Location& end,
                         void* customData) {
    int xdist = start.x - end.x;
    int ydist = start.y - end.y;
    return (abs(xdist) + abs(ydist));
}

bool canMoveTo(GameEngine* engine, Location& location) {
    const EntityHolder& l_targets = engine->state()->tile(location).entities();
    for (EntityId l_target : l_targets) {
        if (engine->state()->components()->get<ColliderComponent>(l_target)) {
            return false;
        }
    }
    return true;
}

EntityId findNearestVisibleMatching(GameState* state, const Location& location,
                                    unsigned int radius, std::string name) {
    EntityId retval = 0;
    unsigned int minDist = 1000.0;
    EntityHolder entities = state->map()->findEntitiesNear(location, radius);
    for (EntityId entity : entities) {
        unsigned int dist = getDistance(location, state->location(entity));
        auto* desc = state->components()->get<DescriptionComponent>(entity);
        if (desc == 0)
            continue;
        if (desc->title == name && dist < minDist) {
            retval = entity;
            minDist = dist;
        }
    }
    return retval;
}

void setPathToTarget(GameEngine* engine, EntityId entity, EntityId target,
                     NpcComponent* npc) {
    Algorithm algo;
    algo.setCustomData(engine);
    algo.setCostFunction(getPathCost);
    algo.setDistanceFunction(getDistance);
    algo.setNeighbourFunction(findNeighbours4);
    algo.setNumNeighbours(4);

    PathVector l_path;
    algo.findPath(engine->state()->location(entity),
                  engine->state()->location(target), l_path);

    if (l_path.empty()) {
        return;
    }

    // Reset path
    npc->path.clear();
    for (unsigned int ii = 0; ii < l_path.size(); ii++) {
        npc->path.push_back(l_path[ii]);
        // std::cout << "Step " << ii << ": " << tempLoc << std::endl;
    }
}
