#ifndef OBJECTIVES_SYSTEM_H
#define OBJECTIVES_SYSTEM_H

#include "../core/game_system_base.h"

class ObjectivesSystem : public GameSystemBase {
public:
    void handleAddEntityEvent(const AddEntityEvent* event);
    void handleRemoveEntityEvent(const RemoveEntityEvent* event);
    
    bool updateQuests();
    void showGameOverWindow(bool gameWon);

private:
    EntityId m_boss = 0;
};

#endif
