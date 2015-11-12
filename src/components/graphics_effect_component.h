#ifndef GRAPHICS_EFFECT_COMPONENT_H_
#define GRAPHICS_EFFECT_COMPONENT_H_

#include <component_base.h>
#include <color.h>

struct GraphicsEffectComponent : public ComponentBase
{
	unsigned int ticks;
	unsigned int maxTicks;
	unsigned int org_tile;
	Color org_color;

};


#endif /* GRAPHICS_EFFECT_COMPONENT_H_ */
