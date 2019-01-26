#pragma once

#include "../components/graphics_effect_component.h"
#include "../components/sprite_component.h"
#include "../core/game_system_base.h"

class GraphicsEffectSystem : public GameSystemBase {
public:
    virtual ~GraphicsEffectSystem() {}
    virtual void onTick();

private:
    void blinkEffect(GraphicsEffectComponent* effect, SpriteComponent* sprite);
    void changeColor(GraphicsEffectComponent* effect, SpriteComponent* sprite);
};
