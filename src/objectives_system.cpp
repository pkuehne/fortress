#include "objectives_system.h"
#include "game_over_window.h"
#include "window_manager_interface.h"

void ObjectivesSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_REMOVE_ENTITY: {
            const RemoveEntityEvent* l_event = dynamic_cast<const RemoveEntityEvent*> (event);
            if (l_event->entity == getEngine()->getEntities()->getPlayer()) {

                GameOverWindow* l_win = new GameOverWindow();
                l_win->initialise(getEngine());
                getEngine()->getWindows()->pushWindow (l_win);
            }
            break;
        }
        case EVENT_CHANGE_LEVEL: {
            const ChangeLevelEvent* l_event = dynamic_cast<const ChangeLevelEvent*> (event);
            unsigned int level = l_event->level;

            if (level > m_engine->getMaxLevel()) {
                GameOverWindow* l_win = new GameOverWindow();
                l_win->initialise (m_engine, m_engine);
                m_engine->getWindows()->pushWindow (l_win);
            }
            break;
        }
        default: break;
    }
}
