#include "dialog_system.h"
#include "../components/player_component.h"
#include "../windows/dialog_window.h"

void DialogSystem::registerHandlers() {
    events()->subscribe<StartConversationEvent>(
        [=](std::shared_ptr<StartConversationEvent> event) {
            handleStartConversationEvent(event);
        });
    events()->subscribe<ChooseDialogOptionEvent>(
        [=](std::shared_ptr<ChooseDialogOptionEvent> event) {
            handleChooseDialogOptionEvent(event);
        });
    events()->subscribe<EndConversationEvent>(
        [=](std::shared_ptr<EndConversationEvent> event) {
            handleEndConversationEvent(event);
        });
}

void DialogSystem::handleStartConversationEvent(
    std::shared_ptr<StartConversationEvent> event) {

    auto playerId = state()->player();
    auto player = components()->get<PlayerComponent>(playerId);
    if (player == nullptr) {
        throw std::string("Player has no PlayerComponent");
    }

    if (player->inConversationWith != 0) {
        return;
    }
    if (event->initiatedBy == playerId) {
        player->inConversationWith = event->target;
    } else {
        player->inConversationWith = event->initiatedBy;
    }

    generateDialog(player);

    // Show the dialog window
    events()->raise(std::make_shared<RegisterWindowEvent>(
        std::make_shared<DialogWindow>()));
}

void DialogSystem::handleChooseDialogOptionEvent(
    std::shared_ptr<ChooseDialogOptionEvent> event) {
    auto playerId = state()->player();
    auto player = components()->get<PlayerComponent>(playerId);

    if (event->option == 1) {
        player->dialogText = "I don't know you well enough to say.";
    }
    if (event->option == 2) {
        player->dialogText = "Do I look human to you?";
    }
    events()->raise(std::make_shared<EndTurnEvent>());
}

void DialogSystem::handleEndConversationEvent(
    std::shared_ptr<EndConversationEvent> event) {
    auto playerId = state()->player();
    auto player = components()->get<PlayerComponent>(playerId);

    player->inConversationWith = 0;
}

void DialogSystem::generateDialog(PlayerComponent* player) {
    player->dialogText = "Hello there! What can I do for you?";
    player->dialogOptions.clear();
    player->dialogOptions.push_back("What's your name?");
    player->dialogOptions.push_back("Are you human?");
}