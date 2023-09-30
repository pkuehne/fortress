#pragma once

#include "../core/entity.h"
#include <string>
#include <vector>

struct DialogComponent {
    EntityId inConversationWith = 0;
    std::vector<std::string> dialogOptions;
    std::string dialogText = "";
};
