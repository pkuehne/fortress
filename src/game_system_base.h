#ifndef GAME_SYSTEM_BASE_H
#define GAME_SYSTEM_BASE_H

#include "event.h"
#include "game_system_interface.h"
#include "game_engine_interface.h"
#include <vector>

class GameSystemBase : public GameSystemInterface {
public:
    GameSystemBase() : m_engine (0) { }
    virtual void initialise (GameEngineInterface* engine) { m_engine = engine; }
    virtual GameEngineInterface* getEngineRef () { return m_engine; }
    virtual void handleEvent (const Event* event) { }
    virtual void update () { }

    virtual ~GameSystemBase() { }

    virtual std::vector<Entity*> findEntitiesNear (unsigned int x, unsigned int y, unsigned radius);
    virtual std::vector<Entity*> findEntitiesAt (unsigned int x, unsigned int y);
    virtual std::vector<Entity*> findEntitiesToThe (MoveEntityEvent::DIRECTION a_direction, Entity* a_entity);
protected:
    GameEngineInterface*    m_engine;
};

#endif
