#pragma once

#include "../core/game_system_base.h"

class MovementSystem : public GameSystemBase {
public:
    void registerHandlers() override;
    virtual ~MovementSystem() {}
    void handleMoveEntityEvent(const MoveEntityEvent& event);

private:
};
