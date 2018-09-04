#pragma once

#include "../core/entity.h"
#include "component_base.h"
#include <string>
#include <vector>

struct PlayerComponent : public ComponentBase {
    EntityId inConversationWith = 0;
    std::vector<std::string> dialogOptions;
    unsigned int dialogChoice = 0;
    std::string dialogText = "";
};
