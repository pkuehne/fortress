#ifndef __SPRITE_SYSTEM_H__
#define __SPRITE_SYSTEM_H__

#include "base_system.h"

class SpriteSystem : public BaseSystem {
public:
    virtual ~SpriteSystem() { }
    virtual void initialise (GameEngineInterface* engine){m_engine = engine; }
    virtual void handleEvent (const Event* event);

};

#endif
