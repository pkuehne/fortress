#ifndef __SPRITE_SYSTEM_H__
#define __SPRITE_SYSTEM_H__

#include "base_system.h"

class SpriteSystem : public BaseSystem {
public:
    virtual void handleEvent (const Event* event);

};

#endif
