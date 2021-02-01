#pragma once

#include "component_base.h"

struct DebugComponent : public ComponentBase {
    bool show_entity_info = true;
};

// No YAML encoding/decoding as this information should not persist through
// saves