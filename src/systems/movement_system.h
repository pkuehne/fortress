#pragma once

#include "../core/game_system_base.h"

class MovementSystem : public GameSystemBase {
public:
    void registerHandlers();
    virtual ~MovementSystem() {}
    void handleMoveEntityEvent(std::shared_ptr<MoveEntityEvent> event);

private:
};
