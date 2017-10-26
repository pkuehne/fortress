#include "objectives_system.h"
#include "../windows/game_over_window.h"
#include "../components/description_component.h"
#include "../core/quest.h"

void ObjectivesSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_REMOVE_ENTITY:
            {
                const RemoveEntityEvent* l_event = static_cast<const RemoveEntityEvent*> (event);
                if (l_event->entity == getEngine()->state()->player()) {
                    GameOverWindow* l_win = new GameOverWindow();
                    l_win->initialise(getEngine());
                    getEngine()->getWindows()->pushWindow (l_win);
                    return;
                }
                if (l_event->entity == m_boss) {
                    std::cout << "Killed the boss!" << std::endl;
                }
                if (updateQuests()) {
                    GameOverWindow* l_win = new GameOverWindow();
                    l_win->initialise(getEngine(),(void*)(1));
                    getEngine()->getWindows()->pushWindow (l_win);
                }

                break;
            }
        case EVENT_ADD_ENTITY:
            {
                const AddEntityEvent* l_event = static_cast<const AddEntityEvent*> (event);
                DescriptionComponent* l_desc = getEngine()->state()->components()->get<DescriptionComponent>(l_event->entity);
                if (l_desc && l_desc->title == "Troll") {
                    m_boss = l_event->entity;
                    KillQuest* quest = new KillQuest(
                            getEngine()->state()->player(),
                            l_event->entity);
                    quest->title() = "Kill the Troll";
                    getEngine()->state()->getQuests().push_back(quest);
                }
                break;
            }
        default: break;
    }
}

void ObjectivesSystem::update()
{
}

bool ObjectivesSystem::updateQuests()
{
    bool allComplete = true;
    std::cout << "Updating Quests" << std::endl;
    for (Quest* quest : getEngine()->state()->getQuests()) {
        if (!quest->isCompleted() && !quest->isFailed()) {
            allComplete = false;
            std::cout << "Updating " << quest->title() << std::endl;
            quest->update(*(getEngine()->state()));
            if (quest->isCompleted()) {
                std::cout << "Quest " << quest->title()
                    << " has just completed!" << std::endl;
            } else if (quest->isFailed()) {
                std::cout << "Quest " << quest->title()
                    << " has just failed!" << std::endl;
            }
        }
    }
    return allComplete;
}
