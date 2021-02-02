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
    void invokeWith(const Event& event) { invoke(event); }

private:
    virtual void invoke(const Event& event) = 0;
};

template <class EventType> class Handler : public BaseHandler {
public:
    explicit Handler(const std::function<void(const EventType& event)>& func)
        : m_func(func) {}

private:
    void invoke(const Event& event) override {
        m_func(dynamic_cast<const EventType&>(event));
    }

private:
    std::function<void(const EventType& event)> m_func;
};

template <typename T> using HandlerFunc = std::function<void(const T&)>;

/// @brief Manages events in the game and distributes them
/// to the Systems
class EventManager {
public:
    EventManager() = default;
    virtual ~EventManager() = default;

    /// @brief Notify the listeners of any new events
    void processEvents();

    template <class EventType, class... Args> void fire(Args&&... args) {
        m_eventList.push(std::make_pair(typeid(EventType).hash_code(),
                                        std::make_unique<EventType>(args...)));
    }

    template <class FuncType, class EventType> void subscribe(FuncType func) {
        subscribe(std::function<void(EventType)>(func));
    }

    template <class EventType> void subscribe(HandlerFunc<EventType> func) {

        m_handlerList[typeid(EventType).hash_code()].push_back(
            std::make_unique<Handler<EventType>>(func));
    }

    unsigned int getEventQueueSize() { return m_eventList.size(); }

protected:
    std::map<size_t, std::vector<std::unique_ptr<BaseHandler>>> m_handlerList;
    std::queue<std::pair<size_t, std::unique_ptr<Event>>> m_eventList;
};
