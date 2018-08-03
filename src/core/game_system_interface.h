#ifndef GAME_SYSTEM_INTERFACE_H
#define GAME_SYSTEM_INTERFACE_H

#include "event.h"
#include <memory>

class GameEngine;

class GameSystemInterface {
public:
    virtual void initialise(GameEngine* engine) = 0;
    virtual void handleEvent(std::shared_ptr<Event> event) = 0;
    virtual void update() = 0;
    virtual GameEngine* getEngine() = 0;
    virtual ~GameSystemInterface() = default;

    virtual void handleStartConversationEvent(
        std::shared_ptr<StartConversationEvent> event) = 0;
};

#endif
