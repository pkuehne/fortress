#ifndef __BASE_SYSTEM_H__
#define __BASE_SYSTEM_H__

#include "event.h"
#include "game_engine_interface.h"

class BaseSystem {
public:
    virtual void initialise (GameEngineInterface* engine) = 0;
    virtual void handleEvent (const Event* event) { }
    virtual void update () { }

    virtual ~BaseSystem() { }
protected:
    GameEngineInterface*    m_engine;
};

#endif
