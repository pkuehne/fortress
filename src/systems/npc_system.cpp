#include "npc_system.h"
#include "../algos/algorithm.h"
#include "../algos/los_algorithm.h"
#include "../components/collider_component.h"
#include "../components/description_component.h"
#include "../components/npc_component.h"
#include "../components/player_component.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <spdlog/spdlog.h>

namespace {
auto getDistance = [](const Location& start, const Location& end, void* c = 0) {
    int xdist = start.x - end.x;
    int ydist = start.y - end.y;
    return (abs(xdist) + abs(ydist));
};

} // namespace

NpcSystem::NpcSystem() {
    createHumanStateMachine();
    createDogStateMachine();
}

void NpcSystem::createHumanStateMachine() {
    StateMachine human;

    State NoneState;
    Transition NoneToIdle;
    NoneToIdle.condition = [&](EntityId e, NpcComponent* n) { return true; };
    NoneToIdle.endState = "Idle";
    NoneState.transitions.push_back(NoneToIdle);
    human[""] = NoneState;

    State IdleState;
    Transition IdleToSeeking;
    IdleToSeeking.condition = [&](EntityId e, NpcComponent* n) { return true; };
    IdleToSeeking.endState = "Seeking";
    IdleState.transitions.push_back(IdleToSeeking);
    human["Idle"] = IdleState;

    State SeekingState;
    Transition SeekingToMoving;
    SeekingToMoving.condition = [&](EntityId e, NpcComponent* n) {
        return n->target != 0;
    };
    SeekingToMoving.endState = "Moving";
    SeekingState.transitions.push_back(SeekingToMoving);
    SeekingState.onUpdate = [&](EntityId e, NpcComponent* n) {
        n->target = findNearestVisibleMatching(entities()->getLocation(e),
                                               n->losDistance,
                                               n->attribs["seek_target"]);
    };
    human["Seeking"] = SeekingState;

    State MovingState;
    Transition MovingToAttacking;
    MovingToAttacking.condition = [&](EntityId e, NpcComponent* n) {
        return canAttackTarget(e, n);
    };
    MovingToAttacking.endState = "Attacking";
    MovingState.transitions.push_back(MovingToAttacking);
    MovingState.onUpdate = [&](EntityId e, NpcComponent* n) {
        setPathToTarget(e, n->target, n);
        if (!n->path.empty()) {
            events()->fire<MoveEntityEvent>(e, n->path[0]);
            n->path.erase(n->path.begin());
        }
    };
    human["Moving"] = MovingState;

    State AttackingState;
    Transition AttackingNotPossible;
    AttackingNotPossible.condition = [&](EntityId e, NpcComponent* n) {
        return !canAttackTarget(e, n);
    };
    AttackingNotPossible.endState = "Seeking";
    AttackingState.transitions.push_back(AttackingNotPossible);
    AttackingState.onUpdate = [&](EntityId e, NpcComponent* n) {
        events()->fire<AttackEntityEvent>(e, n->target);
    };
    AttackingState.onLeave = [&](EntityId e, NpcComponent* n) {
        n->target = 0;
    };
    human["Attacking"] = AttackingState;
    m_stateMachines["human"] = human;
}

void NpcSystem::createDogStateMachine() {
    StateMachine dog;

    State NoneState;
    Transition NoneToIdle;
    NoneToIdle.condition = [](EntityId e, NpcComponent* n) { return true; };
    NoneToIdle.endState = "Idle";
    NoneState.transitions.push_back(NoneToIdle);
    dog[""] = NoneState;

    State IdleState;
    Transition IdleToSeeking;
    IdleToSeeking.condition = [&](EntityId e, NpcComponent* n) {
        // When human is too far away - 5 tiles
        return 0 == findNearestVisibleMatching(entities()->getLocation(e), 3,
                                               n->attribs["seek_target"]);
        ;
    };
    IdleToSeeking.endState = "Seeking";
    IdleState.transitions.push_back(IdleToSeeking);
    dog["Idle"] = IdleState;

    State SeekingState;
    Transition SeekingToMoving;
    SeekingToMoving.condition = [](EntityId e, NpcComponent* n) {
        return true;
    };
    SeekingToMoving.endState = "Moving";
    SeekingState.transitions.push_back(SeekingToMoving);
    SeekingState.onUpdate = [&](EntityId e, NpcComponent* n) {
        n->target = findNearestVisibleMatching(entities()->getLocation(e),
                                               n->losDistance,
                                               n->attribs["seek_target"]);
    };
    dog["Seeking"] = SeekingState;

    State MovingState;
    Transition MovingToIdle;
    MovingToIdle.condition = [&](EntityId e, NpcComponent* n) {
        // When human is too far away - x tiles
        return 0 != findNearestVisibleMatching(entities()->getLocation(e), 3,
                                               n->attribs["seek_target"]);
        ;
    };
    MovingToIdle.endState = "Idle";
    MovingState.transitions.push_back(MovingToIdle);
    MovingState.onUpdate = [&](EntityId e, NpcComponent* n) {
        setPathToTarget(e, n->target, n);
        if (!n->path.empty()) {
            events()->fire<MoveEntityEvent>(e, n->path[0]);
            n->path.erase(n->path.begin());
        }
    };
    dog["Moving"] = MovingState;

    m_stateMachines["dog"] = dog;
}

void NpcSystem::onTurn() {
    for (EntityId entity : entities()->all()) {
        NpcComponent* npc = components()->get<NpcComponent>(entity);
        if (npc == 0)
            continue;

        State currentState = m_stateMachines[npc->stateMachine][npc->state];
        for (Transition& transition : currentState.transitions) {
            if (transition.condition(entity, npc)) {
                spdlog::info("Chainging state from <{}> to <{}> for {}",
                             npc->state, transition.endState, entity);
                if (currentState.onLeave) {
                    currentState.onLeave(entity, npc);
                }
                npc->state = transition.endState;
                currentState = m_stateMachines[npc->stateMachine][npc->state];
                if (currentState.onEntry) {
                    currentState.onEntry(entity, npc);
                }
                break;
            }
        }
        if (currentState.onUpdate) {
            currentState.onUpdate(entity, npc);
        }
    }
}

EntityId NpcSystem::findNearestVisibleMatching(const Location& location,
                                               unsigned int radius,
                                               const std::string& name) {
    EntityId retval = 0;
    unsigned int minDist = 1000.0;
    EntityHolder entities = map()->findEntitiesNear(location, radius);
    for (EntityId entity : entities) {
        unsigned int dist =
            getDistance(location, this->entities()->getLocation(entity));
        auto* desc = components()->get<DescriptionComponent>(entity);
        if (desc == 0)
            continue;
        if (desc->title == name && dist < minDist) {
            retval = entity;
            minDist = dist;
        }
    }
    return retval;
}

void NpcSystem::setPathToTarget(EntityId entity, EntityId target,
                                NpcComponent* npc) {
    auto getPathCost = [&](const Location& location, void* c) {
        auto player = components()->getUnique<PlayerComponent>();

        for (EntityId entity : map()->getTile(location).entities()) {
            if (entity == player.id) {
                continue;
            }
            if (components()->get<ColliderComponent>(entity)) {
                return 99;
            }
        }
        return 1;
    };
    auto findNeighbours4 = [&](const Location& location, Location* neighbours,
                               void* c) {
        unsigned int count = 0;
        Location neighbour = location;
        int xAdj[] = {-1, 1, 0, 0};
        int yAdj[] = {0, 0, -1, 1};

        for (unsigned int ii = 0; ii < 4; ii++) {
            neighbour = location;
            neighbour.x += xAdj[ii];
            neighbour.y += yAdj[ii];
            if (map()->isValidTile(neighbour)) {
                if (getPathCost(neighbour, 0) > 0)
                    neighbours[count++] = neighbour;
            }
        }
        return count;
    };

    Algorithm algo;
    algo.setCostFunction(getPathCost);
    algo.setDistanceFunction(getDistance);
    algo.setNeighbourFunction(findNeighbours4);
    algo.setNumNeighbours(4);

    PathVector l_path;
    algo.findPath(entities()->getLocation(entity),
                  entities()->getLocation(target), l_path);

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

bool NpcSystem::canAttackTarget(EntityId entity, NpcComponent* npc) {
    Location location = entities()->getLocation(entity);
    EntityHolder entitiesNear = map()->findEntitiesNear(location, 1);

    auto entityInReach = [&](EntityId id) {
        // Check it's the target that's in reach
        if (id != npc->target) {
            return false;
        }
        // Check it's not at a diagonal
        Location oLoc = entities()->getLocation(id);
        return !(location.x != oLoc.x && location.y != oLoc.y);
    };

    return entitiesNear.end() != std::find_if(entitiesNear.begin(),
                                              entitiesNear.end(),
                                              entityInReach);
}