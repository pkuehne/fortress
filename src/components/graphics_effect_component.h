#ifndef GRAPHICS_EFFECT_COMPONENT_H_
#define GRAPHICS_EFFECT_COMPONENT_H_

#include <component_base.h>
#include <color.h>

typedef enum {
	EFFECT_NONE = 0,
	EFFECT_BLINK_SLOW,
	EFFECT_BLINK_FAST,
	EFFECT_MAX
} EFFECT;

struct GraphicsEffectComponent : public ComponentBase
{
	unsigned int ticks		= 0;
	unsigned int duration	= 0;
	unsigned int org_tile	= 0;
	Color org_color;
	EFFECT type				= EFFECT_NONE;
	bool removeEntity		= false;
};


#endif /* GRAPHICS_EFFECT_COMPONENT_H_ */
