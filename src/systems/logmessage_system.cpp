
#include "logmessage_system.h"
#include "../components/logmessage_component.h"
#include "../components/player_component.h"

void LogMessageSystem::registerHandlers() {
    events()->subscribe<AddLogMessageEvent>([=](auto event) {
        auto player = this->entities()->world().lookup("player");
        auto messages = player.get_mut<LogMessageComponent>();
        messages->messages.push_back(
            LogMessageComponent::Message(event.message, event.category));
    });

    events()->subscribe<PrefabCreatedEvent>([=](auto event) {
        // Todo: This should go into the narrator system...
        if (event.prefab == "player") {
            events()->fire<AddLogMessageEvent>(
                "You find yourself in a forest.");
            events()->fire<AddLogMessageEvent>(
                "Stairs will lead you into the dungeons.");
            events()->fire<AddLogMessageEvent>(
                "Beware the troll, living in the depths", "warning");
        }
    });
}