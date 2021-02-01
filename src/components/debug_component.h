#pragma once

#include "component_base.h"

struct DebugComponent : public ComponentBase {};

// No YAML encoding/decoding as this information should not persist through
// saves