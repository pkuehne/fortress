#ifndef GRAPHICS_EFFECT_SYSTEM_H
#define GRAPHICS_EFFECT_SYSTEM_H

#include "../components/graphics_effect_component.h"
#include "../components/sprite_component.h"
#include "../core/game_system_base.h"

class GraphicsEffectSystem : public GameSystemBase {
public:
    virtual ~GraphicsEffectSystem() {}
    virtual void update();

private:
    void blinkEffect(GraphicsEffectComponent* effect, SpriteComponent* sprite);
    void changeColor(GraphicsEffectComponent* effect, SpriteComponent* sprite);
};

#endif
