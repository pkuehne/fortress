#include "event_manager.h"
#include <iostream>

void EventManager::processEvents() {
    while (!m_events.empty()) {
        auto l_event = m_events.front();
        m_events.pop();

        // std::cout << *l_event << std::endl;

        for (HandlersIter iter = m_handlers.begin(); iter != m_handlers.end();
             ++iter) {
            (*iter)->handleEvent(l_event);
        }
    }
}
