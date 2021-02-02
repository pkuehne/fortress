#pragma once

#include "../core/game_system_base.h"
#include "../core/utility.h"

class DialogComponent;

class DialogSystem : public GameSystemBase {
public:
    void registerHandlers() override;
    void handleStartConversationEvent(const StartConversationEvent& event);
    void handleChooseDialogOptionEvent(const ChooseDialogOptionEvent& event);
    void handleEndConversationEvent(const EndConversationEvent& event);

    void generateDialog(DialogComponent* player);
};
