#include <graphics_effect_system.h>
#include <graphics_effect_component.h>
#include <sprite_component.h>
#include <glog/logging.h>

void GraphicsEffectSystem::update ()
{
    for (EntityId l_entity : getEngine()->getEntities()->get()) {
    	GraphicsEffectComponent* effect = getEngine()->getComponents()->get<GraphicsEffectComponent>(l_entity);
    	if (!effect) continue;

    	SpriteComponent* sprite = getEngine()->getComponents()->get<SpriteComponent>(l_entity);
    	if (!sprite) {
    		LOG(WARNING) << "GraphicsEffect without a sprite is pointless: " << l_entity << std::endl;
    		continue;
    	}
    	Color tempColor = sprite->fgColor;
    	tempColor.Red() += 5.0/256.0;
    	if (tempColor.Red() > 1.0) tempColor.Red() = 0.0;
    	sprite->fgColor = Color (tempColor.Red(), tempColor.Green(), tempColor.Blue());
    }
}
