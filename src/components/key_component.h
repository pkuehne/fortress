#pragma once

#include "component_base.h"
struct KeyComponent : public ComponentBase {};

namespace YAML {
template <> struct convert<KeyComponent> {
    static Node encode(const KeyComponent& rhs) {
        Node node;
        node = true;
        return node;
    }

    static bool decode(const Node& node, KeyComponent& rhs) {
        if (!node.IsScalar()) {
            return false;
        }

        return true;
    }
};
} // namespace YAML