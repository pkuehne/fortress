#ifndef GAME_SYSTEM_INTERFACE_H
#define GAME_SYSTEM_INTERFACE_H

#include "event.h"

class GameEngineInterface;

class GameSystemInterface {
public:
    virtual void initialise (GameEngineInterface* engine) = 0;
    virtual void handleEvent (const Event* event) = 0;
    virtual void update () = 0;
    virtual GameEngineInterface* getEngine() = 0;
    virtual ~GameSystemInterface() { }
};

#endif
