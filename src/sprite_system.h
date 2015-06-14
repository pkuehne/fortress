#ifndef __SPRITE_SYSTEM_H__
#define __SPRITE_SYSTEM_H__

#include "base_system.h"
#include "game_engine_interface.h"

class SpriteSystem : public BaseSystem {
public:
    virtual ~SpriteSystem() { }
    virtual void initialise (GameEngineInterface* engine){m_engine = engine; }
    virtual void handleEvent (const Event* event);

private:
    Entity* findWallEntity (unsigned int x, unsigned int y);
    void updateWallSprite (Entity* a_entity);


private:
    GameEngineInterface*    m_engine;
};

#endif
