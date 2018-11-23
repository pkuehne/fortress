#include "event_manager.h"
#include <iostream>

void EventManager::processEvents() {
    while (!m_eventList.empty()) {
        auto event = m_eventList.front();
        m_eventList.pop();

        for (auto& handler : m_handlerList[event.first]) {
            handler->invokeWith(event.second);
        }
    }
}