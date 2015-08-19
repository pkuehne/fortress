#include "objectives_system.h"
#include "game_over_window.h"
#include "window_manager_interface.h"

void ObjectivesSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_REMOVE_ENTITY: {
            const RemoveEntityEvent* l_event = dynamic_cast<const RemoveEntityEvent*> (event);
            if (l_event->entity == getEngineRef()->getEntities()->getPlayer()) {
                
                GameOverWindow* l_win = new GameOverWindow();
                l_win->initialise(getEngineRef());
                getEngineRef()->getWindows()->pushWindow (l_win);
            }
            break;
        }
        default: break;
    }
}
