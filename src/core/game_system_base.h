#ifndef GAME_SYSTEM_BASE_H
#define GAME_SYSTEM_BASE_H

#include "event.h"
#include "game_engine.h"
#include "game_system_interface.h"
#include <vector>

class GameSystemBase : public GameSystemInterface {
public:
    GameSystemBase() : m_engine(0) {}
    virtual void initialise(GameEngine* engine) { m_engine = engine; }
    virtual GameEngine* getEngine() { return m_engine; }
    virtual void handleEvent(const Event* event) {}
    virtual void update() {}

    virtual ~GameSystemBase() {}

protected:
    GameEngine* m_engine;
};

#endif
