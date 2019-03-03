#pragma once

#include "../core/entity.h"
#include "component_base.h"
#include <string>
#include <vector>

struct DialogComponent : public ComponentBase {
    EntityId inConversationWith = 0;
    std::vector<std::string> dialogOptions;
    std::string dialogText = "";
};

namespace YAML {

// DialogComponent
template <> struct convert<DialogComponent> {
    static Node encode(const DialogComponent& rhs) {
        Node node;
        node["inConversationWith"] = rhs.inConversationWith;
        node["dialogOptions"] = rhs.dialogOptions;
        node["dialogText"] = rhs.dialogText;
        return node;
    }

    static bool decode(const Node& node, DialogComponent& rhs) {
        if (!node.IsMap() || node.size() != 3) {
            return false;
        }
        rhs.inConversationWith = node["inConversationWith"].as<EntityId>();
        rhs.dialogOptions =
            node["dialogOptions"].as<std::vector<std::string>>();
        rhs.dialogText = node["dialogText"].as<std::string>();
        return true;
    }
};

} // namespace YAML