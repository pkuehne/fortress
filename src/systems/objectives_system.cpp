#include "objectives_system.h"
#include "game_over_window.h"
#include "window_manager_interface.h"
#include "description_component.h"

void ObjectivesSystem::handleEvent (const Event* event)
{
    switch (event->getType()) {
        case EVENT_REMOVE_ENTITY: {
            const RemoveEntityEvent* l_event = dynamic_cast<const RemoveEntityEvent*> (event);
            if (l_event->entity == getEngine()->getEntities()->getPlayer()) {

                GameOverWindow* l_win = new GameOverWindow();
                l_win->initialise(getEngine());
                getEngine()->getWindows()->pushWindow (l_win);
                return;
            }
            DescriptionComponent* l_desc = getEngine()->getComponents()->get<DescriptionComponent>(l_event->entity);
            if (l_desc) std::cout << "Name of killed entity: " << l_desc->title << std::endl;
            if (l_desc && l_desc->title == "Troll") {
                GameOverWindow* l_win = new GameOverWindow();
                l_win->initialise(getEngine(),(void*)(1));
                getEngine()->getWindows()->pushWindow (l_win);
                return;
            }
            break;
        }
        default: break;
    }
}
