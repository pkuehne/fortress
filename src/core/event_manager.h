#pragma once

#include "event.h"
#include "game_system_interface.h"
#include <map>
#include <memory>
#include <queue>
#include <vector>

class BaseHandler {
protected:
    BaseHandler() = default;

public:
    void invokeWith(const std::shared_ptr<Event>& event) { invoke(event); }

private:
    virtual void invoke(const std::shared_ptr<Event>& event) = 0;
};

template <class EventType> class Handler : public BaseHandler {
public:
    explicit Handler(
        const std::function<void(std::shared_ptr<EventType> event)>& func)
        : m_func(func) {}

private:
    void invoke(const std::shared_ptr<Event>& event) {
        m_func(std::dynamic_pointer_cast<EventType>(event));
    }

private:
    std::function<void(std::shared_ptr<EventType> event)> m_func;
};

typedef std::queue<std::shared_ptr<Event>> EventQueue;
typedef std::vector<GameSystemInterface*> Handlers;
typedef Handlers::iterator HandlersIter;

/// @brief Manages events in the game and distributes them
/// to the Systems
class EventManager {
public:
    EventManager() = default;
    virtual ~EventManager() = default;

    /// @brief Notify the listeners of any new events
    void processEvents();

    template <typename EventType> void raise(std::shared_ptr<EventType> event) {
        m_eventList.push(std::make_pair(typeid(EventType).hash_code(), event));
    }

    template <class FuncType, class EventType> void subscribe(FuncType func) {
        subscribe(std::function<void(std::shared_ptr<EventType>)>(func));
    }

    template <class EventType>
    void subscribe(std::function<void(std::shared_ptr<EventType>)> func) {
        std::unique_ptr<BaseHandler> handler =
            std::make_unique<Handler<EventType>>(func);
        m_handlerList[typeid(EventType).hash_code()].push_back(
            std::move(handler));
    }

    unsigned int getEventQueueSize() { return m_eventList.size(); }

private:
    EventQueue m_events;
    Handlers m_handlers;
    std::map<size_t, std::vector<std::unique_ptr<BaseHandler>>> m_handlerList;
    std::queue<std::pair<size_t, std::shared_ptr<Event>>> m_eventList;
};
