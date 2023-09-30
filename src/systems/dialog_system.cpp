#include "dialog_system.h"
#include "../components/dialog_component.h"
#include "../components/player_component.h"
#include "../windows/dialog_window.h"

void DialogSystem::registerHandlers() {
    events()->subscribe<StartConversationEvent>(
        [=](const StartConversationEvent& event) {
            handleStartConversationEvent(event);
        });
    events()->subscribe<ChooseDialogOptionEvent>(
        [=](const ChooseDialogOptionEvent& event) {
            handleChooseDialogOptionEvent(event);
        });
    events()->subscribe<EndConversationEvent>(
        [=](const EndConversationEvent& event) {
            handleEndConversationEvent(event);
        });
}

void DialogSystem::handleStartConversationEvent(
    const StartConversationEvent& event) {

    auto player = entities()->world().lookup("player");
    auto component = player.get_mut<DialogComponent>();

    if (component->inConversationWith != 0) {
        return;
    }
    if (event.initiatedBy == player.id()) {
        component->inConversationWith = event.target;
    } else {
        component->inConversationWith = event.initiatedBy;
    }

    generateDialog(component);

    // Show the dialog window
    events()->fire<AddWindowEvent<DialogWindow>>();
}

void DialogSystem::handleChooseDialogOptionEvent(
    const ChooseDialogOptionEvent& event) {
    auto player = entities()->world().lookup("player");
    auto component = player.get_mut<DialogComponent>();

    if (event.option == 1) {
        component->dialogText = "I don't know you well enough to say.";
    }
    if (event.option == 2) {
        component->dialogText = "Do I look human to you?";
    }
    events()->fire<EndTurnEvent>();
}

void DialogSystem::handleEndConversationEvent(
    const EndConversationEvent& event) {
    auto player = entities()->world().lookup("player");
    auto component = player.get_mut<DialogComponent>();

    component->inConversationWith = 0;
}

void DialogSystem::generateDialog(DialogComponent* player) {
    player->dialogText = "Hello there! What can I do for you?";
    player->dialogOptions.clear();
    player->dialogOptions.push_back("What's your name?");
    player->dialogOptions.push_back("Are you human?");
}