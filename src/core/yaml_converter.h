#pragma once

#include "../components/collider_component.h"
#include "../components/consumable_component.h"
#include "../components/sprite_component.h"
#include "area_info.h"
#include "color.h"
#include "floor.h"
#include "game_state.h"
#include "location.h"
#include "map_manager.h"
#include "tile.h"
#include <vector>
#include <yaml-cpp/yaml.h>

void encodeEntity(GameState* state, YAML::Node& node, EntityId entity) {
    SpriteComponent* sprite = state->components()->get<SpriteComponent>(entity);
    ColliderComponent* collide =
        state->components()->get<ColliderComponent>(entity);
    if (sprite) {
        node[entity]["sprite"] = *sprite;
    }
    if (collide) {
        node[entity]["collider"] = *collide;
    }
    node[entity]["location"] = state->entityManager()->getLocation(entity);
}

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
        if (!node.IsMap() || node.size() != 4) {
            return false;
        }

        rhs.setSize(node["width"].as<unsigned int>(),
                    node["height"].as<unsigned int>(),
                    node["depth"].as<unsigned int>());
        rhs.setTiles(node["tiles"].as<std::vector<Tile>>());
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

// ColliderComponent
template <> struct convert<ColliderComponent> {
    static Node encode(const ColliderComponent& rhs) {
        Node node;
        node = true;
        return node;
    }

    static bool decode(const Node& node, ColliderComponent& rhs) {
        if (!node.IsScalar()) {
            return false;
        }
        return true;
    }
};

// ConsumableComponent
template <> struct convert<ConsumableComponent> {
    static Node encode(const ConsumableComponent& rhs) {
        Node node;
        node["quenches"] = static_cast<int>(rhs.quenches);
        node["quenchStrength"] = rhs.quenchStrength;
        node["effect"] = static_cast<int>(rhs.effect);
        node["effectStrength"] = rhs.effectStrength;
        return node;
    }

    static bool decode(const Node& node, ConsumableComponent& rhs) {
        if (!node.IsSequence() || node.size() != 4) {
            return false;
        }

        rhs.quenches = static_cast<HUNGER_THIRST>(node["quenches"].as<int>());
        rhs.quenchStrength = node["quenchStrength"].as<unsigned int>();
        rhs.effect = static_cast<EFFECT>(node["effect"].as<int>());
        rhs.effectStrength = node["effectStrength"].as<unsigned int>();

        return true;
    }
};

} // namespace YAML