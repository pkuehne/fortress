#ifndef __MOVEMENT_SYSTEM_H__
#define __MOVEMENT_SYSTEM_H__

#include "base_system.h"

class MovementSystem : public BaseSystem {
public:
    virtual void handleEvent (const Event* event);

private:

};

#endif
