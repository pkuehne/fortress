#pragma once

#include "event.h"
#include "game_engine.h"
#include "game_system_interface.h"
#include <memory>
#include <vector>

class GameSystemBase : public GameSystemInterface {
public:
    GameSystemBase() : m_engine(0) {}
    virtual ~GameSystemBase() {}

    virtual void initialise(GameEngine* engine) {
        m_engine = engine;
        registerHandlers();
    }
    virtual void registerHandlers() {}
    virtual GameEngine* getEngine() { return m_engine; }
    virtual void update() {}

protected:
    GameEngine* m_engine;
};
