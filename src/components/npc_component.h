#ifndef NPC_COMPONENT_H
#define NPC_COMPONENT_H

#include "component_base.h"

enum class NpcState {
    None        = 0,
    Idle        = 1,
    Searching   = 2,
    Hunting     = 3,
};

struct NpcComponent : ComponentBase {
    std::vector<Location>   path;
    NpcState                state;
    EntityId                target;
};

#endif
