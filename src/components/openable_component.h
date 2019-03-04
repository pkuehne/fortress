#pragma once

#include "component_base.h"
struct OpenableComponent : public ComponentBase {
    bool open = false;
    bool locked = false;
};

namespace YAML {
template <> struct convert<OpenableComponent> {
    static Node encode(const OpenableComponent& rhs) {
        Node node;
        node["open"] = rhs.open;
        node["locked"] = rhs.locked;
        return node;
    }

    static bool decode(const Node& node, OpenableComponent& rhs) {
        if (!node.IsMap() || node.size() != 2) {
            return false;
        }

        rhs.open = node["open"].as<bool>();
        rhs.locked = node["open"].as<bool>();
        return true;
    }
};
}