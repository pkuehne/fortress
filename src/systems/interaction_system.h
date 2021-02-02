#pragma once

#include "../core/game_system_base.h"

class InteractionSystem : public GameSystemBase {
public:
    void registerHandlers() override;

public:
    void handleOpenEntityEvent(const OpenEntityEvent& event);
    void handleCloseEntityEvent(const CloseEntityEvent& event);
    void handleLockEntityEvent(const LockEntityEvent& event);
    void handleUnlockEntityEvent(const UnlockEntityEvent& event);
};
