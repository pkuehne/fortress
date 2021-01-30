#pragma once

#include "event.h"
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

template <typename T>
using HandlerFunc = std::function<void(std::shared_ptr<T>)>;

/// @brief Manages events in the game and distributes them
/// to the Systems
class EventManager {
public:
    EventManager() = default;
    virtual ~EventManager() = default;

    /// @brief Notify the listeners of any new events
    void processEvents();

    template <typename EventType> void fire(std::shared_ptr<EventType> event) {
        m_eventList.push(std::make_pair(typeid(EventType).hash_code(), event));
    }

    template <class FuncType, class EventType> void subscribe(FuncType func) {
        subscribe(std::function<void(std::shared_ptr<EventType>)>(func));
    }

    template <class EventType> void subscribe(HandlerFunc<EventType> func) {
        std::unique_ptr<BaseHandler> handler =
            std::make_unique<Handler<EventType>>(func);
        m_handlerList[typeid(EventType).hash_code()].push_back(
            std::move(handler));
    }

    unsigned int getEventQueueSize() { return m_eventList.size(); }

protected:
    std::map<size_t, std::vector<std::unique_ptr<BaseHandler>>> m_handlerList;
    std::queue<std::pair<size_t, std::shared_ptr<Event>>> m_eventList;
};
