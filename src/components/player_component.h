#pragma once

#include "../core/entity.h"
#include "component_base.h"

struct PlayerComponent : public ComponentBase {
    EntityId inConversationWith = 0;
};
