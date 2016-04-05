#include "objectives_system.h"
#include "game_over_window.h"
#include "description_component.h"

void ObjectivesSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_REMOVE_ENTITY: {
            const RemoveEntityEvent* l_event = static_cast<const RemoveEntityEvent*> (event);
            if (l_event->entity == getEngine()->getEntities()->getPlayer()) {
                GameOverWindow* l_win = new GameOverWindow();
                l_win->initialise(getEngine());
                getEngine()->getWindows()->pushWindow (l_win);
                return;
            }
            if (l_event->entity == m_boss) {
                GameOverWindow* l_win = new GameOverWindow();
                l_win->initialise(getEngine(),(void*)(1));
                getEngine()->getWindows()->pushWindow (l_win);
                return;
            }
            break;
        }
        case EVENT_ADD_ENTITY: {
            const AddEntityEvent* l_event = static_cast<const AddEntityEvent*> (event);
            DescriptionComponent* l_desc = getEngine()->getComponents()->get<DescriptionComponent>(l_event->entity);
            if (l_desc && l_desc->title == "Troll") {
                m_boss = l_event->entity;
                LOG(INFO) << "Set Entity " << l_event->entity << " as Boss objective!" << std::endl;
            }
            break;
        }
        default: break;
    }
}
