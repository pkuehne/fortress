#pragma once

#include "component_base.h"
#include "entity.h"

struct CombatComponent : public ComponentBase {
    EntityId opponent = 0;
};

using T = CombatComponent;

namespace YAML {
template <> struct convert<T> {
    static Node encode(const T& rhs) {
        Node node;
        node["opponent"] = rhs.opponent;
        return node;
    }

    static bool decode(const Node& node, T& rhs) {
        if (!node.IsMap() || node.size() != 1) {
            return false;
        }
        rhs.opponent = node["opponent"].as<EntityId>(0);
        return true;
    }
};
} // namespace YAML