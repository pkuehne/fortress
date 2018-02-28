#ifndef STAIR_COMPONENT_H
#define STAIR_COMPONENT_H

#include "../core/utility.h"
#include "component_base.h"

struct StairComponent : public ComponentBase {
    STAIR       direction;
    EntityId    target;
};

#endif
