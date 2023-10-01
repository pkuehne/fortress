#pragma once

#include "area_info.h"
#include "color.h"
#include "location.h"
#include "tile.h"
#include <iostream>
#include <vector>
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
//         if (!node.IsMap() || node.size() != 4) {
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
        node["x"] = rhs.x;
        node["y"] = rhs.y;
        node["z"] = rhs.z;
        node["a"] = rhs.area;

        return node;
    }

    static bool decode(const Node& node, Location& rhs) {
        if (!node.IsMap() || node.size() != 4) {
            return false;
        }
        rhs.x = node["x"].as<unsigned int>();
        rhs.y = node["y"].as<unsigned int>();
        rhs.z = node["z"].as<unsigned int>();
        rhs.area = node["a"].as<unsigned int>();
        return true;
    }
};

// Color
template <> struct convert<Color> {
    static Node encode(const Color& rhs) {
        Node node;
        node["red"] = rhs.Red();
        node["green"] = rhs.Green();
        node["blue"] = rhs.Blue();
        return node;
    }

    static bool decode(const Node& node, Color& rhs) {
        if (!node.IsMap() || node.size() != 3) {
            return false;
        }

        rhs.Red() = node["red"].as<float>();
        rhs.Green() = node["green"].as<float>();
        rhs.Blue() = node["blue"].as<float>();

        return true;
    }
};

// Tile
template <> struct convert<Tile> {
    static Node encode(const Tile& rhs) {
        Node node;
        node["lit"] = rhs.lit();
        node["lastVisited"] = rhs.lastVisited();
        node["floor"] = static_cast<int>(rhs.getFloorMaterial());
        node["wall"] = static_cast<int>(rhs.getWallMaterial());
        node["symbol"] = rhs.getSprite().sprite;
        return node;
    }

    static bool decode(const Node& node, Tile& rhs) {
        if (!node.IsMap() || node.size() != 5) {
            return false;
        }

        rhs.lit() = node["lit"].as<bool>();
        rhs.lastVisited() = node["lastVisited"].as<unsigned int>();
        rhs.setFloorMaterial(
            static_cast<FloorMaterial>(node["floor"].as<int>()));
        rhs.setWallMaterial(static_cast<WallMaterial>(node["wall"].as<int>()));
        rhs.overrideSpriteSymbol(node["symbol"].as<unsigned int>());
        return true;
    }
};

// AreaInfo
template <> struct convert<AreaInfo> {
    static Node encode(const AreaInfo& rhs) {
        Node node;
        node["width"] = rhs.getWidth();
        node["height"] = rhs.getHeight();
        node["depth"] = rhs.getDepth();
        node["tiles"] = rhs.getTiles();
        return node;
    }

    static bool decode(const Node& node, AreaInfo& rhs) {
        if (!node.IsMap() || node.size() < 4) {
            return false;
        }

        rhs.setSize(node["width"].as<unsigned int>(),
                    node["height"].as<unsigned int>(),
                    node["depth"].as<unsigned int>());
        rhs.setTiles(node["tiles"].as<std::vector<Tile>>());
        return true;
    }
};

} // namespace YAML