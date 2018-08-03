#include "event_manager.h"
#include <iostream>

void EventManager::registerHandler(GameSystemInterface* system) {
    m_handlers.push_back(system);
}

void EventManager::raiseEvent(Event* event) {
    m_events.push(std::shared_ptr<Event>(event));
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
}

void EventManager::raiseStartConversationEvent(EntityId from, EntityId to) {
    auto event = std::make_shared<StartConversationEvent>();
    event->initiatedBy = from;
    event->target = to;
    m_events.push(event);
}

void EventManager::raisePickupEqupmentEvent(EntityId equipment,
                                            EntityId entity) {
    auto event = std::make_shared<PickupEquipmentEvent>();
    event->entity = entity;
    event->item = equipment;
    m_events.push(event);
}
