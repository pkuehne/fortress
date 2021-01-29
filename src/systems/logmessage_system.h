#pragma once

#include "../core/game_system_base.h"

class LogMessageSystem : public GameSystemBase {
public:
    void registerHandlers() override;
};