#pragma once

#include "event.h"
#include <memory>

class GameEngine;

class GameSystemInterface {
public:
    virtual void initialise(GameEngine* engine) = 0;
    virtual void update() = 0;
    virtual GameEngine* getEngine() = 0;
    virtual ~GameSystemInterface() = default;
};
