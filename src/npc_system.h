#ifndef NPC_SYSTEM_H
#define NPC_SYSTEM_H

#include "game_system_base.h"

class NpcSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);
    virtual void update ();
private:
    MoveEntityEvent::DIRECTION getRandomDirection ();
};


#endif
