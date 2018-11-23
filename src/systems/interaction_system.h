#pragma once

#include "../core/game_system_base.h"

class InteractionSystem : public GameSystemBase {
public:
    void registerHandlers();

private:
    void handleOpenEntityEvent(std::shared_ptr<OpenEntityEvent> event);
    void handleCloseEntityEvent(std::shared_ptr<CloseEntityEvent> event);
};
