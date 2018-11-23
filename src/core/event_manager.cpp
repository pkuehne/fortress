#include "event_manager.h"
#include <iostream>

void EventManager::registerHandler(GameSystemInterface* system) {
    m_handlers.push_back(system);
}

void EventManager::raiseEvent(Event* event) {
    m_events.push(std::shared_ptr<Event>(event));
}

void EventManager::raiseEvent(std::shared_ptr<Event> event) {
    m_events.push(event);
}

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

    while (!m_eventList.empty()) {
        auto event = m_eventList.front();
        m_eventList.pop();

        for (auto& handler : m_handlerList[event.first]) {
            handler->invokeWith(event.second);
        }
    }
}