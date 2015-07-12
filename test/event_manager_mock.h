#ifndef EVENT_MANAGER_MOCK_H
#define EVENT_MANAGER_MOCK_H

#include <event_manager_interface.h>
#include <gmock/gmock.h>

class GameSystemMock;

class EventManagerMock : public EventManagerInterface {
public:
    MOCK_METHOD1(initialise, void (GameEngineInterface* engine) );
    MOCK_METHOD1(registerHandler, void (GameSystemInterface* system) );
    MOCK_METHOD1(raiseEvent, void (Event* event) );
    MOCK_METHOD0(processEvents, void() );
};

#endif
