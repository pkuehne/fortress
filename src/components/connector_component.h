#pragma once

#include "../core/entity.h"
#include "../core/utility.h"
#include "component_base.h"

struct ConnectorComponent : public ComponentBase {
    EntityId target;
};
