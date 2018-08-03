#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include "event.h"
#include "event_manager_interface.h"
#include "game_system_interface.h"
#include <memory>
#include <queue>
#include <vector>

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

    /// @brief Notify the listeners of any new events
    void processEvents();

    void raiseStartConversationEvent(EntityId from, EntityId to);
    void raisePickupEqupmentEvent(EntityId equipment, EntityId entity);

private:
    EventQueue m_events;
    Handlers m_handlers;
};

#endif
