#include "dialog_system.h"
#include "../components/player_component.h"
#include "../windows/dialog_window.h"

void DialogSystem::handleStartConversationEvent(
    std::shared_ptr<StartConversationEvent> event) {
    auto state = getEngine()->state();

    auto playerId = state->player();
    auto player = state->components()->get<PlayerComponent>(playerId);
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
    getEngine()->getWindows()->registerWindow(std::make_shared<DialogWindow>());
}

void DialogSystem::generateDialog(PlayerComponent* player) {
    player->dialogText = "Hello there! What can I do for you?";
    player->dialogOptions.push_back("What's your name?");
    player->dialogOptions.push_back("Are you human?");
    player->dialogChoice = 0;
}