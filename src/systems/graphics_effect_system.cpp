#include <graphics_effect_system.h>
#include <glog/logging.h>

void GraphicsEffectSystem::update ()
{
	//std::cout << "Checking " << getEngine()->getEntities()->get().size() << " entities in " << getEngine()->getArea() << std::endl;
	for (EntityId l_entity : getEngine()->getEntities()->get()) {
    	GraphicsEffectComponent* effect = getEngine()->getComponents()->get<GraphicsEffectComponent>(l_entity);
    	if (!effect) continue;

    	SpriteComponent* sprite = getEngine()->getComponents()->get<SpriteComponent>(l_entity);
    	if (!sprite) {
    		LOG(WARNING) << "GraphicsEffect without a sprite is pointless: " << l_entity << std::endl;
    		continue;
    	}
    	std::cout << "Processing effect for " << l_entity << std::endl;

    	if (effect->ticks == 0) {
    		effect->org_color = sprite->fgColor;
    		effect->org_tile = sprite->sprite;
    		std::cout << getEngine()->getTick() << ": Setting org values for " << l_entity << std::endl;
    	}
    	if (effect->duration && effect->ticks > effect->duration) {
    		sprite->fgColor = effect->org_color;
    		sprite->sprite = effect->org_tile;
    		getEngine()->getComponents()->remove<GraphicsEffectComponent>(l_entity);
    		if (effect->removeEntity) {
    			std::cout << "Removing entity" << std::endl;
    			getEngine()->getEntities()->destroyEntity(l_entity);
    		}
    		continue;
    	}

    	switch (effect->type) {
    	case EFFECT_BLINK_SLOW:
    	case EFFECT_BLINK_FAST:
    			blinkEffect (effect, sprite);
    		break;
    	default:
    		LOG(ERROR) << "Invalid effect type: " << effect->type << std::endl;
    		break;
    	}

    	std::cout << "Processed effect " << std::endl;
    	effect->ticks += 1;
    }
}

void GraphicsEffectSystem::blinkEffect (GraphicsEffectComponent* effect, SpriteComponent* sprite)
{
	unsigned int speed = 10;

	if (effect->type == EFFECT_BLINK_FAST) speed = 5;

	if (effect->ticks % speed == 0) {
		if (sprite->sprite != ' ') {
			sprite->sprite = ' ';
		} else {
			sprite->sprite = effect->org_tile;
		}
	}
}
