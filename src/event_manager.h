#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <queue>
#include <vector>
#include "base_system.h"
#include "event.h"

typedef std::queue<Event*> EventQueue;
typedef std::vector<BaseSystem*> Handlers;
typedef Handlers::iterator HandlersIter;

class EventManager {
public:

    void initialise () { }

    void registerHandler (BaseSystem& system) { m_handlers.push_back (&system); }

    void raiseEvent (Event* event) { m_events.push (event); }

    void processEvents ();

private:
    EventQueue      m_events;
    Handlers        m_handlers;
};

#endif
