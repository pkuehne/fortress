#pragma once

#include "../core/game_system_base.h"

class HealthSystem : public GameSystemBase {
public:
    void onTurn() override;
};
