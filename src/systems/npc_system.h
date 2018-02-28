#ifndef NPC_SYSTEM_H
#define NPC_SYSTEM_H

#include "../core/game_system_base.h"
#include "../core/utility.h"
#include "../components/npc_component.h"
#include <map>
#include <vector>

class GameEngine;

typedef bool (*ConditionFunc) (GameEngine*, EntityId, NpcComponent*);
typedef void (*ActionFunc) (GameEngine*, EntityId, NpcComponent*);

struct Transition {
    ConditionFunc   condition;
    std::string     endState;
};
typedef std::vector<Transition> TransitionList;

struct State {
    ActionFunc      onEntry     = nullptr;
    ActionFunc      onUpdate    = nullptr;
    ActionFunc      onLeave     = nullptr;
    TransitionList  transitions;
};

typedef std::map<std::string, State> StateMachine;

class NpcSystem : public GameSystemBase {
    public:
        NpcSystem();
        virtual void handleEvent (const Event* event);
        virtual void update ();

    private:
        void createHumanStateMachine();

        std::map<std::string, StateMachine> m_stateMachines;
};


#endif
