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

    if (event->initiatedBy == playerId) {
        player->inConversationWith = event->target;
    } else {
        player->inConversationWith = event->initiatedBy;
    }

    // Show the dialog window
    getEngine()->getWindows()->registerWindow(std::make_shared<DialogWindow>());
}
