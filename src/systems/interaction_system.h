#pragma once

#include "../core/game_system_base.h"

class InteractionSystem : public GameSystemBase {
public:
    virtual void handleEvent(const Event* event) override;
    virtual void update() override;

private:
    void handleOpenEntityEvent(const OpenEntityEvent* event);
    void handleCloseEntityEvent(const CloseEntityEvent* event);
};
