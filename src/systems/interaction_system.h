#pragma once

#include "../core/game_system_base.h"

class InteractionSystem : public GameSystemBase {
public:
    void registerHandlers() override;

public:
    void handleOpenEntityEvent(std::shared_ptr<OpenEntityEvent> event);
    void handleCloseEntityEvent(std::shared_ptr<CloseEntityEvent> event);
    void handleLockEntityEvent(std::shared_ptr<LockEntityEvent> event);
    void handleUnlockEntityEvent(std::shared_ptr<UnlockEntityEvent> event);
};
