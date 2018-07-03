#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

#include "../core/game_system_base.h"

class MovementSystem : public GameSystemBase {
public:
    virtual ~MovementSystem() {}
    void handleMoveEntityEvent(const MoveEntityEvent* event);

private:
};

#endif
