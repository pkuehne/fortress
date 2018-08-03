#ifndef EVENT_MANAGER_INTERFACE_H
#define EVENT_MANAGER_INTERFACE_H

#include "event.h"

class GameSystemInterface;

class EventManagerInterface {
public:
    virtual ~EventManagerInterface() {}
    virtual void registerHandler(GameSystemInterface* system) = 0;
    virtual void raiseEvent(Event* event) = 0;
    virtual void processEvents() = 0;
    virtual void raiseStartConversationEvent(EntityId from, EntityId to) = 0;
    virtual void raisePickupEqupmentEvent(EntityId equipment,
                                          EntityId entity) = 0;
};

#endif
