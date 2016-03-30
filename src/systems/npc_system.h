#ifndef NPC_SYSTEM_H
#define NPC_SYSTEM_H

#include "game_system_base.h"
#include "utility.h"
#include "npc_component.h"
#include <map>
#include <vector>

typedef bool (*ConditionFunc) (GameEngineInterface*, EntityId, NpcComponent*);
struct Transition {
    ConditionFunc   condition;
    NpcState        endState;
};

typedef std::map<NpcState, std::vector<Transition>> TransitionMap;
typedef std::map<unsigned int, TransitionMap> StateMachine;

class NpcSystem : public GameSystemBase {
public:
    NpcSystem();
    virtual void handleEvent (const Event* event);
    virtual void update ();
private:
    //Location getRandomDirection (const Location& oldLocation);
    //Location getPlayerDirectionIfNearby (EntityId npc);

    //bool canAttackPlayer(const Location& location);

    void changeState (EntityId entity, NpcComponent* npc);
    void setPathToTarget (EntityId entity, EntityId target, NpcComponent* npc);
    void moveTowards (EntityId entity, const Location& location);

    StateMachine m_stateMachine;
};


#endif
