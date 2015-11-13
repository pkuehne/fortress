#ifndef GRAPHICS_EFFECT_COMPONENT_H_
#define GRAPHICS_EFFECT_COMPONENT_H_

#include <component_base.h>
#include <color.h>

typedef enum {
	EFFECT_NONE = 0,
	EFFECT_BLINK,
	EFFECT_MAX
} EFFECT;

struct GraphicsEffectComponent : public ComponentBase
{
	unsigned int ticks		= 0;
	unsigned int duration	= 0;
	unsigned int org_tile	= 0;
	Color org_color;
	EFFECT type				= EFFECT_NONE;
};


#endif /* GRAPHICS_EFFECT_COMPONENT_H_ */
