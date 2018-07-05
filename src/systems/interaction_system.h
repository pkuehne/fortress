#pragma once

#include "../core/game_system_base.h"

class InteractionSystem : public GameSystemBase {
private:
    void handleOpenEntityEvent(const OpenEntityEvent* event) override;
    void handleCloseEntityEvent(const CloseEntityEvent* event) override;
};
