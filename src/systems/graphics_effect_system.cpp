#include "graphics_effect_system.h"
#include <spdlog/spdlog.h>

void GraphicsEffectSystem::onTick() {
    for (EntityId l_entity : entities()->all()) {
        GraphicsEffectComponent* effect =
            components()->get<GraphicsEffectComponent>(l_entity);
        if (!effect)
            continue;

        SpriteComponent* sprite = components()->get<SpriteComponent>(l_entity);
        if (!sprite) {
            spdlog::warn("GraphicsEffect without a sprite is pointless {}",
                         l_entity);
            continue;
        }

        if (effect->ticks == 0) {
            effect->org_color = sprite->fgColor;
            effect->org_tile = sprite->sprite;
        }
        if (effect->duration && effect->ticks > effect->duration) {
            sprite->fgColor = effect->org_color;
            sprite->sprite = effect->org_tile;
            components()->remove<GraphicsEffectComponent>(l_entity);
            if (effect->removeEntity) {
                const Location location = entities()->getLocation(l_entity);
                events()->fire<RemoveEntityEvent>(l_entity, location);
            }
            continue;
        }

        switch (effect->type) {
            case EFFECT_BLINK_SLOW:
            case EFFECT_BLINK_FAST:
                blinkEffect(effect, sprite);
                break;
            case EFFECT_CHANGE_COLOR:
                changeColor(effect, sprite);
                break;
            default:
                spdlog::error("Invalid effect type: {}", effect->type);
                break;
        }
        effect->ticks += 1;
    }
}

void GraphicsEffectSystem::blinkEffect(GraphicsEffectComponent* effect,
                                       SpriteComponent* sprite) {
    unsigned int speed = 10;

    if (effect->type == EFFECT_BLINK_FAST)
        speed = 5;

    if (effect->ticks % speed == 0) {
        if (sprite->sprite != ' ') {
            sprite->sprite = ' ';
        } else {
            sprite->sprite = effect->org_tile;
        }
    }
}

void GraphicsEffectSystem::changeColor(GraphicsEffectComponent* effect,
                                       SpriteComponent* sprite) {
    sprite->fgColor = effect->new_color;
}
