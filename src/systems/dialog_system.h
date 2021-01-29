#pragma once

#include "../core/game_system_base.h"
#include "../core/utility.h"

class DialogComponent;

class DialogSystem : public GameSystemBase {
public:
    void registerHandlers() override;
    void
    handleStartConversationEvent(std::shared_ptr<StartConversationEvent> event);
    void handleChooseDialogOptionEvent(
        std::shared_ptr<ChooseDialogOptionEvent> event);
    void
    handleEndConversationEvent(std::shared_ptr<EndConversationEvent> event);

    void generateDialog(DialogComponent* player);
};
