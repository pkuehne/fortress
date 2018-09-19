#pragma once

#include "../core/game_system_base.h"
#include "../core/utility.h"

class PlayerComponent;

class DialogSystem : public GameSystemBase {
public:
    void handleStartConversationEvent(
        std::shared_ptr<StartConversationEvent> event) override;
    void handleChooseDialogOptionEvent(
        std::shared_ptr<ChooseDialogOptionEvent> event) override;
    void handleEndConversationEvent(
        std::shared_ptr<EndConversationEvent> event) override;

    void generateDialog(PlayerComponent* player);
};
