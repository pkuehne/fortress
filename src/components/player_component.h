#pragma once

#include "../core/entity.h"
#include "component_base.h"

struct PlayerComponent : public ComponentBase {
    unsigned long long turn = 0;
    bool playerTurn = false;
};

namespace YAML {

// PlayerComponent
template <> struct convert<PlayerComponent> {
    static Node encode(const PlayerComponent& rhs) {
        Node node;
        node["turn"] = rhs.turn;
        node["playerTurn"] = rhs.playerTurn;
        return node;
    }

    static bool decode(const Node& node, PlayerComponent& rhs) {
        if (!node.IsMap() || node.size() != 2) {
            return false;
        }
        rhs.turn = node["turn"].as<unsigned long long>();
        rhs.playerTurn = node["playerTurn"].as<bool>();
        return true;
    }
};

}