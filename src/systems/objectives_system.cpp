#include "objectives_system.h"
#include "../components/description_component.h"
#include "../core/quest.h"
#include "../windows/game_over_window.h"

void ObjectivesSystem::registerHandlers() {
    // events()->subscribe(std::bind(
    //     &ObjectivesSystem::handleAddEntityEvent, this,
    //     std::placeholders::_1));
    events()->subscribe<PrefabCreatedEvent>(
        [=](std::shared_ptr<PrefabCreatedEvent> event) {
            handleAddEntityEvent(event);
        });
    events()->subscribe<RemoveEntityEvent>(
        [=](std::shared_ptr<RemoveEntityEvent> event) {
            handleRemoveEntityEvent(event);
        });
}

void ObjectivesSystem::showGameOverWindow(bool gameWon) {
    events()->fire(std::make_shared<RegisterWindowEvent>(
        std::make_shared<GameOverWindow>(gameWon)));
}

void ObjectivesSystem::handleAddEntityEvent(
    std::shared_ptr<PrefabCreatedEvent> event) {
    // DescriptionComponent* l_desc =
    //     components()->get<DescriptionComponent>(event->entity);
    // if (l_desc && l_desc->title == "Troll") {
    //     m_boss = event->entity;
    //     KillQuest* quest =
    //         new KillQuest(entities()->getPlayer(), event->entity);
    //     quest->title() = "Kill the Troll";
    //     // state()->getQuests().push_back(quest);
    // }
}

void ObjectivesSystem::handleRemoveEntityEvent(
    std::shared_ptr<RemoveEntityEvent> event) {
    // if (event->entity == entities()->getPlayer()) {
    //     showGameOverWindow(false);
    //     return;
    // }
    if (updateQuests()) {
        showGameOverWindow(true);
    }
}

bool ObjectivesSystem::updateQuests() {
    bool allComplete = true;
    // for (Quest* quest : state()->getQuests()) {
    //     if (!quest->isCompleted() && !quest->isFailed()) {
    //         quest->update(*(state()));
    //         if (quest->isCompleted()) {
    //             std::cout << "Quest " << quest->title()
    //                       << " has just completed!" << std::endl;
    //             continue;
    //         } else if (quest->isFailed()) {
    //             std::cout << "Quest " << quest->title() << " has just
    //             failed!"
    //                       << std::endl;
    //         }
    //         allComplete = false;
    //     }
    // }
    return allComplete;
}
