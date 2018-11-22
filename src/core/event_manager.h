#pragma once

#include "event.h"
#include "event_manager_interface.h"
#include "game_system_interface.h"
#include <memory>
#include <queue>
#include <vector>

class BaseHandler {
protected:
    BaseHandler() = default;

public:
    void invokeWith(const std::shared_ptr<Event>& event) { invoke(event); }

private:
    virtual void invoke(const std::shared_ptr<Event> event) = 0;
};

template <class EventType> class Handler : public BaseHandler {
public:
    explicit Handler(
        const std::function<void(std::shared_ptr<EventType> event)> func)
        : m_func(func) {}

private:
    void invoke(const std::shared_ptr<Event> event) {
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
class EventManager : public EventManagerInterface {
public:
    EventManager() = default;
    virtual ~EventManager() = default;

    /// @brief Register a new system to listen to events
    /// @param[in] system The Game System to register
    void registerHandler(GameSystemInterface* system);

    /// @brief Puts an event into the queue for distribution
    /// @param[in] event The event to store
    void raiseEvent(Event* event);

    /// @brief Puts an event into the queue for distribution
    /// @param[in] event The event to store
    void raiseEvent(std::shared_ptr<Event> event);

    /// @brief Notify the listeners of any new events
    void processEvents();

    template <typename EventType> void raise(std::shared_ptr<EventType> event) {
        for (auto& handler : m_handlerList[typeid(EventType).hash_code()]) {
            handler->invokeWith(event);
        }
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

private:
    EventQueue m_events;
    Handlers m_handlers;
    std::map<size_t, std::vector<std::unique_ptr<BaseHandler>>> m_handlerList;
};
