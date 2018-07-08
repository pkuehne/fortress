#pragma once

#include "../components/sprite_component.h"
#include "color.h"
#include "floor.h"
#include "location.h"
#include "tile.h"

#include <yaml-cpp/yaml.h>

namespace YAML {

// Template
// template <> struct convert<Foo> {
//     static Node encode(const Foo& rhs) {
//         Node node;
//         node["a"] = rhs.a();
//         return node;
//     }

//     static bool decode(const Node& node, Foo& rhs) {
//         if (!node.IsSequence() || node.size() != 4) {
//             return false;
//         }
//         // Todo
//         return true;
//     }
// };

// Location
template <> struct convert<Location> {
    static Node encode(const Location& rhs) {
        Node node;
        node.push_back(rhs.x);
        node.push_back(rhs.y);
        node.push_back(rhs.z);
        node.push_back(rhs.area);
        return node;
    }

    static bool decode(const Node& node, Location& rhs) {
        if (!node.IsSequence() || node.size() != 4) {
            return false;
        }
        rhs.x = node[0].as<unsigned int>();
        rhs.y = node[1].as<unsigned int>();
        rhs.z = node[2].as<unsigned int>();
        rhs.area = node[3].as<unsigned int>();
        return true;
    }
};

// Color
template <> struct convert<Color> {
    static Node encode(const Color& rhs) {
        Node node;
        node.push_back(rhs.Red());
        node.push_back(rhs.Green());
        node.push_back(rhs.Blue());
        return node;
    }

    static bool decode(const Node& node, Color& rhs) {
        if (!node.IsSequence() || node.size() != 3) {
            return false;
        }

        rhs.Red() = node[0].as<float>();
        rhs.Green() = node[1].as<float>();
        rhs.Blue() = node[2].as<float>();

        return true;
    }
};

// Floor
template <> struct convert<Floor> {
    static Node encode(const Floor& rhs) {
        Node node;
        node["material"] = static_cast<int>(rhs.getMaterial());
        node["sprite"] = rhs.getSprite();
        return node;
    }

    static bool decode(const Node& node, Floor& rhs) {
        if (!node.IsMap() || node.size() != 2) {
            return false;
        }

        rhs.setMaterial(static_cast<Material>(node["material"].as<int>()));
        rhs.setSprite(node["sprite"].as<SpriteComponent>());

        return true;
    }
};

// Tile
template <> struct convert<Tile> {
    static Node encode(const Tile& rhs) {
        Node node;
        node["lit"] = rhs.lit();
        node["lastVisited"] = rhs.lastVisited();
        node["floor"] = rhs.getFloor();
        return node;
    }

    static bool decode(const Node& node, Tile& rhs) {
        if (!node.IsMap() || node.size() != 3) {
            return false;
        }

        rhs.lit() = node["lit"].as<bool>();
        rhs.lastVisited() = node["lastVisited"].as<unsigned int>();
        rhs.getFloor() = node["floor"].as<Floor>();

        return true;
    }
};

// SpriteComponent
template <> struct convert<SpriteComponent> {
    static Node encode(const SpriteComponent& rhs) {
        Node node;
        node["symbol"] = rhs.sprite;
        node["layer"] = rhs.renderLayer;
        node["foreground"] = rhs.fgColor;
        node["background"] = rhs.bgColor;
        return node;
    }

    static bool decode(const Node& node, SpriteComponent& rhs) {
        if (!node.IsMap() || node.size() != 4) {
            return false;
        }

        rhs.sprite = node["symbol"].as<unsigned int>();
        rhs.renderLayer = node["layer"].as<unsigned int>();
        rhs.fgColor = node["foreground"].as<Color>();
        rhs.bgColor = node["background"].as<Color>();
        return true;
    }
};

} // namespace YAML