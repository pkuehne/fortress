#ifndef NPC_COMPONENT_H
#define NPC_COMPONENT_H

#include "component_base.h"
#include "utility.h"
#include <map>

struct NpcComponent : ComponentBase {
    std::vector<Location>   path;
    std::string             state           = "";
    EntityId                target          = 0;
    Direction               lastDirection   = Direction::None;
    std::map<std::string, std::string>  attribs;
    std::string             stateMachine    = "";
    unsigned int            losDistance     = 15;
};

#endif
