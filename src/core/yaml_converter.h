#pragma once

#include "../components/collider_component.h"
#include "../components/connector_component.h"
#include "../components/consumable_component.h"
#include "../components/description_component.h"
#include "../components/droppable_component.h"
#include "../components/equipment_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/health_component.h"
#include "../components/npc_component.h"
#include "../components/openable_component.h"
#include "../components/player_component.h"
#include "../components/sprite_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"
#include "area_info.h"
#include "color.h"
#include "game_state.h"
#include "location.h"
#include "map_manager.h"
#include "tile.h"
#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>

void encodeEntity(GameState* state, YAML::Node& node, EntityId entity);

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

// Tile
template <> struct convert<Tile> {
    static Node encode(const Tile& rhs) {
        Node node;
        node["lit"] = rhs.lit();
        node["lastVisited"] = rhs.lastVisited();
        node["floor"] = static_cast<int>(rhs.getFloorMaterial());
        node["wall"] = static_cast<int>(rhs.getFloorMaterial());
        return node;
    }

    static bool decode(const Node& node, Tile& rhs) {
        if (!node.IsMap() || node.size() != 4) {
            return false;
        }

        rhs.lit() = node["lit"].as<bool>();
        rhs.lastVisited() = node["lastVisited"].as<unsigned int>();
        rhs.setFloorMaterial(
            static_cast<FloorMaterial>(node["floor"].as<int>()));
        rhs.setWallMaterial(static_cast<WallMaterial>(node["wall"].as<int>()));

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

// DescriptionComponent
template <> struct convert<DescriptionComponent> {
    static Node encode(const DescriptionComponent& rhs) {
        Node node;
        node["title"] = rhs.title;
        node["text"] = rhs.text;
        return node;
    }

    static bool decode(const Node& node, DescriptionComponent& rhs) {
        if (!node.IsMap() || node.size() != 2) {
            return false;
        }
        rhs.title = node["title"].as<std::string>();
        rhs.text = node["text"].as<std::string>();
        return true;
    }
};

// DroppableComponent
template <> struct convert<DroppableComponent> {
    static Node encode(const DroppableComponent& rhs) {
        Node node;
        node = true;
        return node;
    }

    static bool decode(const Node& node, DroppableComponent& rhs) {
        if (!node.IsScalar()) {
            return false;
        }
        return true;
    }
};

// EquipmentComponent
template <> struct convert<EquipmentComponent> {
    static Node encode(const EquipmentComponent& rhs) {
        Node node;
        node["headWearable"] = rhs.headWearable;
        node["faceWearable"] = rhs.faceWearable;
        node["chestWearable"] = rhs.chestWearable;
        node["armsWearable"] = rhs.armsWearable;
        node["handsWearable"] = rhs.handsWearable;
        node["legsWearable"] = rhs.legsWearable;
        node["feetWearable"] = rhs.feetWearable;
        node["rightHandWieldable"] = rhs.rightHandWieldable;
        node["leftHandWieldable"] = rhs.leftHandWieldable;
        node["carriedEquipment"] = rhs.carriedEquipment;
        node["maxCarryWeight"] = rhs.maxCarryWeight;
        node["maxCarryVolume"] = rhs.maxCarryVolume;
        return node;
    }

    static bool decode(const Node& node, EquipmentComponent& rhs) {
        if (!node.IsMap() || node.size() != 12) {
            return false;
        }
        rhs.headWearable = node["headWearable"].as<EntityId>();
        rhs.faceWearable = node["faceWearable"].as<EntityId>();
        rhs.chestWearable = node["chestWearable"].as<EntityId>();
        rhs.armsWearable = node["armsWearable"].as<EntityId>();
        rhs.handsWearable = node["handsWearable"].as<EntityId>();
        rhs.legsWearable = node["legsWearable"].as<EntityId>();
        rhs.feetWearable = node["feetWearable"].as<EntityId>();
        rhs.rightHandWieldable = node["rightHandWieldable"].as<EntityId>();
        rhs.leftHandWieldable = node["leftHandWieldable"].as<EntityId>();
        rhs.carriedEquipment =
            node["carriedEquipment"].as<std::vector<EntityId>>();
        rhs.maxCarryWeight = node["maxCarryWeight"].as<unsigned int>();
        rhs.maxCarryVolume = node["maxCarryVolume"].as<unsigned int>();
        return true;
    }
};

// GraphicsEffectComponent
template <> struct convert<GraphicsEffectComponent> {
    static Node encode(const GraphicsEffectComponent& rhs) {
        Node node;
        node["ticks"] = rhs.ticks;
        node["duration"] = rhs.duration;
        node["org_tile"] = rhs.org_tile;
        node["org_color"] = rhs.org_color;
        node["type"] = static_cast<int>(rhs.type);
        node["removeEntity"] = rhs.removeEntity;
        node["new_color"] = rhs.new_color;
        return node;
    }

    static bool decode(const Node& node, GraphicsEffectComponent& rhs) {
        if (!node.IsMap() || node.size() != 7) {
            return false;
        }
        // Todo
        rhs.ticks = node["ticks"].as<unsigned int>();
        rhs.duration = node["duration"].as<unsigned int>();
        rhs.org_tile = node["org_tile"].as<unsigned int>();
        rhs.org_color = node["org_color"].as<Color>();
        rhs.new_color = node["org_color"].as<Color>();
        rhs.type = static_cast<GRAPHICS_EFFECT>(node["type"].as<int>());
        rhs.removeEntity = node["removeEntity"].as<bool>();
        return true;
    }
};

// Template
template <> struct convert<HealthComponent> {
    static Node encode(const HealthComponent& rhs) {
        Node node;
        node["health"] = rhs.health;
        node["thirst"] = rhs.thirst;
        node["hunger"] = rhs.hunger;
        node["thirstRate"] = rhs.thirstRate;
        node["hungerRate"] = rhs.hungerRate;
        node["thirstStep"] = rhs.thirstStep;
        node["hungerStep"] = rhs.hungerStep;

        return node;
    }

    static bool decode(const Node& node, HealthComponent& rhs) {
        if (!node.IsMap() || node.size() != 7) {
            return false;
        }
        rhs.health = node["health"].as<unsigned int>();
        rhs.thirst = node["thirst"].as<unsigned int>();
        rhs.hunger = node["hunger"].as<unsigned int>();
        rhs.thirstRate = node["thirstRate"].as<unsigned int>();
        rhs.hungerRate = node["hungerRate"].as<unsigned int>();
        rhs.thirstStep = node["thirstStep"].as<unsigned int>();
        rhs.hungerStep = node["hungerStep"].as<unsigned int>();
        return true;
    }
};

// NpcComponent
template <> struct convert<NpcComponent> {
    static Node encode(const NpcComponent& rhs) {
        Node node;
        node["path"] = rhs.path;
        node["state"] = rhs.state;
        node["target"] = rhs.target;
        node["attribs"] = rhs.attribs;
        node["stateMachine"] = rhs.stateMachine;
        node["losDistance"] = rhs.losDistance;
        return node;
    }

    static bool decode(const Node& node, NpcComponent& rhs) {
        if (!node.IsMap() || node.size() != 6) {
            return false;
        }
        rhs.path = node["path"].as<std::vector<Location>>();
        rhs.state = node["state"].as<std::string>();
        rhs.target = node["target"].as<EntityId>();
        rhs.attribs = node["attribs"].as<std::map<std::string, std::string>>();
        rhs.stateMachine = node["stateMachine"].as<std::string>();
        rhs.losDistance = node["losDistance"].as<unsigned int>();
        // Todo
        return true;
    }
};

// OpenableComponent
template <> struct convert<OpenableComponent> {
    static Node encode(const OpenableComponent& rhs) {
        Node node;
        node["open"] = rhs.open;
        return node;
    }

    static bool decode(const Node& node, OpenableComponent& rhs) {
        if (!node.IsMap() || node.size() != 4) {
            return false;
        }

        rhs.open = node["open"].as<bool>();
        return true;
    }
};

// PlayerComponent
template <> struct convert<PlayerComponent> {
    static Node encode(const PlayerComponent& rhs) {
        Node node;
        node = true;
        return node;
    }

    static bool decode(const Node& node, PlayerComponent& rhs) {
        if (!node.IsScalar()) {
            return false;
        }
        return true;
    }
};

// ConnectorComponent
template <> struct convert<ConnectorComponent> {
    static Node encode(const ConnectorComponent& rhs) {
        Node node;
        node["target"] = rhs.target;
        return node;
    }

    static bool decode(const Node& node, ConnectorComponent& rhs) {
        if (!node.IsMap() || node.size() != 4) {
            return false;
        }

        rhs.target = node["target"].as<EntityId>();
        return true;
    }
};

// WearableComponent
template <> struct convert<WearableComponent> {
    static Node encode(const WearableComponent& rhs) {
        Node node;
        node["baseDamageAbsorb"] = rhs.baseDamageAbsorb;
        node["position"] = static_cast<int>(rhs.position);
        node["warmth"] = rhs.warmth;
        return node;
    }

    static bool decode(const Node& node, WearableComponent& rhs) {
        if (!node.IsMap() || node.size() != 4) {
            return false;
        }
        rhs.baseDamageAbsorb = node["baseDamageAbsorb"].as<int>();
        rhs.position =
            static_cast<WearablePosition>(node["position"].as<int>());
        rhs.warmth = node["warmth"].as<int>();

        return true;
    }
};

// WieldableComponent
template <> struct convert<WieldableComponent> {
    static Node encode(const WieldableComponent& rhs) {
        Node node;
        node["baseDamage"] = rhs.baseDamage;
        node["baseDefence"] = rhs.baseDefence;
        node["position"] = static_cast<int>(rhs.position);
        return node;
    }

    static bool decode(const Node& node, WieldableComponent& rhs) {
        if (!node.IsMap() || node.size() != 4) {
            return false;
        }

        rhs.baseDamage = node["baseDamage"].as<int>();
        rhs.baseDefence = node["baseDefence"].as<int>();
        rhs.position =
            static_cast<WieldablePosition>(node["position"].as<int>());
        return true;
    }
};

} // namespace YAML