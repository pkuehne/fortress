#ifndef GRAPHICS_EFFECT_SYSTEM_H
#define GRAPHICS_EFFECT_SYSTEM_H

#include <sprite_component.h>
#include <graphics_effect_component.h>
#include <game_system_base.h>

class GraphicsEffectSystem : public GameSystemBase
{
public:
	virtual ~GraphicsEffectSystem() { }
	virtual void handleEvent (const Event* event) { }
    virtual void update ();

private:
    void blinkEffect (GraphicsEffectComponent* effect, SpriteComponent* sprite);
};

#endif
