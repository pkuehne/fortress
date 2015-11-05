#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

#include "game_system_base.h"

class MovementSystem : public GameSystemBase {
public:
    virtual ~MovementSystem() { }
    virtual void handleEvent (const Event* event);

private:

};

#endif
