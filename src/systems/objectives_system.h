#ifndef OBJECTIVES_SYSTEM_H
#define OBJECTIVES_SYSTEM_H

#include "../core/game_system_base.h"

class ObjectivesSystem : public GameSystemBase {
public:
    virtual void handleEvent(const Event* event);
    virtual void update();
    virtual bool updateQuests();

private:
    EntityId m_boss = 0;
};

#endif
