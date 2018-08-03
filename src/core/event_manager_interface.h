#pragma once

#include "event.h"
#include <memory>

class GameSystemInterface;

class EventManagerInterface {
public:
    virtual ~EventManagerInterface() {}
    virtual void registerHandler(GameSystemInterface* system) = 0;
    virtual void raiseEvent(Event* event) = 0;
    virtual void raiseEvent(std::shared_ptr<Event> event) = 0;
    virtual void processEvents() = 0;
};
