#ifndef EVENT_MANAGER_INTERFACE_H
#define EVENT_MANAGER_INTERFACE_H

class GameSystemInterface;

class EventManagerInterface {
public:
    virtual ~EventManagerInterface() { }
    virtual void registerHandler (GameSystemInterface* system) = 0;
    virtual void raiseEvent (Event* event) = 0;
    virtual void processEvents() = 0;

};

#endif
