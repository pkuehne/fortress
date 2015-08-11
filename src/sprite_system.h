#ifndef __SPRITE_SYSTEM_H__
#define __SPRITE_SYSTEM_H__

#include "game_system_base.h"
#include "game_engine_interface.h"

class SpriteSystem : public GameSystemBase {
public:
    virtual ~SpriteSystem() { }
    virtual void handleEvent (const Event* event);

private:
    void handleAddWallEvent (EntityId a_entity);
    EntityId findWallEntity (unsigned int x, unsigned int y);
    void updateWallSprite (EntityId a_entity);

};

#endif
