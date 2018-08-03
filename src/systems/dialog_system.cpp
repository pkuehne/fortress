#include "dialog_system.h"
#include "../windows/dialog_window.h"

void DialogSystem::handleStartConversationEvent(
    std::shared_ptr<StartConversationEvent> event) {
    getEngine()->getWindows()->registerWindow(std::make_shared<DialogWindow>());
}
