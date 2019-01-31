#pragma once

#include "component_base.h"
struct ExperienceComponent : public ComponentBase {
    unsigned int xp = 0;
    unsigned int level = 0;
};

namespace YAML {

// SpriteComponent
template <> struct convert<ExperienceComponent> {
    static Node encode(const ExperienceComponent& rhs) {
        Node node;
        node["xp"] = rhs.xp;
        node["level"] = rhs.level;
        return node;
    }

    static bool decode(const Node& node, ExperienceComponent& rhs) {
        if (!node.IsMap() || node.size() != 2) {
            return false;
        }

        rhs.xp = node["xp"].as<unsigned int>(0);
        rhs.level = node["level"].as<unsigned int>(0);
        return true;
    }
};

}