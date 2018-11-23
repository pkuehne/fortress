#pragma once

#include "../core/game_system_base.h"

class ObjectivesSystem : public GameSystemBase {
public:
    void registerHandlers();
    void handleAddEntityEvent(std::shared_ptr<AddEntityEvent> event);
    void handleRemoveEntityEvent(std::shared_ptr<RemoveEntityEvent> event);
    bool updateQuests();
    void showGameOverWindow(bool gameWon);

private:
    EntityId m_boss = 0;
};
