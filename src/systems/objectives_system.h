#ifndef OBJECTIVES_SYSTEM_H
#define OBJECTIVES_SYSTEM_H

#include "game_system_base.h"

class ObjectivesSystem : public GameSystemBase {
public:
    virtual void handleEvent (const Event* event);

private:
    EntityId m_boss = 0;
};

#endif
