#pragma once

#include "../core/game_system_base.h"
#include "../core/utility.h"

class DialogSystem : public GameSystemBase {
public:
    void handleStartConversationEvent(
        std::shared_ptr<StartConversationEvent> event) override;
};
