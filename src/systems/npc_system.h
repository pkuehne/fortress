#ifndef NPC_SYSTEM_H
#define NPC_SYSTEM_H

#include "game_system_base.h"
#include "utility.h"
#include "npc_component.h"

class NpcSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);
    virtual void update ();
private:
    Location getRandomDirection (const Location& oldLocation);
    Location getPlayerDirectionIfNearby (EntityId npc);

    bool canAttackPlayer(const Location& location);

    void changeState (EntityId entity, NpcComponent* npc);
    bool canSeeTarget (EntityId entity, EntityId target);
    bool canAttackTarget (EntityId entity, EntityId target);
    void setPathToTarget (EntityId entity, EntityId target, NpcComponent* npc);
    void moveTowards (EntityId entity, const Location& location);
};


#endif
