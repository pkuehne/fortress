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
                    // GameOverWindow* l_win = new GameOverWindow();
                    // l_win->initialise(getEngine(),(void*)(1));
                    // getEngine()->getWindows()->pushWindow (l_win);
                    return;
                }
                break;
            }
        case EVENT_ADD_ENTITY:
            {
                const AddEntityEvent* l_event = static_cast<const AddEntityEvent*> (event);
                DescriptionComponent* l_desc = getEngine()->state()->components()->get<DescriptionComponent>(l_event->entity);
                if (l_desc && l_desc->title == "Troll") {
                    m_boss = l_event->entity;
                    LOG(INFO) << "Set Entity " << l_event->entity << " as Boss objective!" << std::endl;
                    KillQuest* quest = new KillQuest(getEngine()->state()->player(), m_boss);
                    getEngine()->state()->getQuests().push_back(quest);
                }
                break;
            }
        default: break;
    }
}

void ObjectivesSystem::update()
{
    for (Quest* quest : getEngine()->state()->getQuests()) {
        if (!quest->isCompleted() && !quest->isFailed()) {
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

}
