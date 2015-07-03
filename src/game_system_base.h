#ifndef GAME_SYSTEM_BASE_H
#define GAME_SYSTEM_BASE_H

#include "event.h"
#include "game_system_interface.h"
#include "game_engine_interface.h"

class GameSystemBase : public GameSystemInterface {
public:
    GameSystemBase() : m_engine (0) { }
    virtual void initialise (GameEngineInterface* engine) { m_engine = engine; }
    virtual GameEngineInterface* getEngineRef () { return m_engine; }
    virtual void handleEvent (const Event* event) { }
    virtual void update () { }

    virtual ~GameSystemBase() { }
protected:
    GameEngineInterface*    m_engine;
};

#endif
