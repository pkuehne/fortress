#ifndef STAIR_COMPONENT_H
#define STAIR_COMPONENT_H

#include "utility.h"
#include "component_base.h"

struct StairComponent : public ComponentBase {
    STAIR           direction;
    unsigned int    area;
};

#endif
