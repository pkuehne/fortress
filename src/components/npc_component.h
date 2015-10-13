#ifndef NPC_COMPONENT_H
#define NPC_COMPONENT_H

#include "component_base.h"

struct NpcComponent : ComponentBase {
    std::vector<Location>   path;
};

#endif
