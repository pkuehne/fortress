#ifndef NPC_SYSTEM_H
#define NPC_SYSTEM_H

#include "game_system_base.h"
#include "utility.h"

class NpcSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);
    virtual void update ();
private:
    Location getRandomDirection (const Location& oldLocation);
    Location getPlayerDirectionIfNearby (EntityId npc);

    bool canAttackPlayer(const Location& location);
};


#endif
