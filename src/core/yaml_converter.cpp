#include "yaml_converter.h"
#include "../components/combat_component.h"
#include "../components/experience_component.h"
#include "../components/key_component.h"
#include "../components/openable_component.h"
#include "../components/player_component.h"

void YamlConverter::encodeEntity(YAML::Node& node, EntityId entity) {
    // encodeComponent<ColliderComponent>("collide", node, entity);
    // encodeComponent<ConsumableComponent>("consue", node, entity);
    // encodeComponent<DescriptionComponent>("describe", node, entity);
    // encodeComponent<DroppableComponent>("drop", node, entity);
    // encodeComponent<EquipmentComponent>("equip", node, entity);
    // encodeComponent<GraphicsEffectComponent>("graphics", node, entity);
    // encodeComponent<HealthComponent>("health", node, entity);
    // encodeComponent<NpcComponent>("npc", node, entity);
    // encodeComponent<OpenableComponent>("open", node, entity);
    // encodeComponent<PlayerComponent>("player", node, entity);
    // encodeComponent<SpriteComponent>("sprite", node, entity);
    // encodeComponent<ConnectorComponent>("connector", node, entity);
    // encodeComponent<WearableComponent>("wear", node, entity);
    // encodeComponent<WieldableComponent>("wield", node, entity);
    // encodeComponent<GroupingComponent>("grouping", node, entity);
    // encodeComponent<ExperienceComponent>("experience", node, entity);
    // encodeComponent<ExperienceComponent>("key", node, entity);
    // encodeComponent<ExperienceComponent>("fight", node, entity);

    node[entity]["location"] = entities()->getLocation(entity);
}

void YamlConverter::decodeEntity(const YAML::Node& node, EntityId entity) {
    // Add Entity
    // entities()->addEntity(entity, node["location"].as<Location>());

    // decodeComponent<ColliderComponent>("collide", node, entity);
    // decodeComponent<ConsumableComponent>("consume", node, entity);
    // decodeComponent<DescriptionComponent>("describe", node, entity);
    // decodeComponent<DroppableComponent>("drop", node, entity);
    // decodeComponent<EquipmentComponent>("equip", node, entity);
    // decodeComponent<GraphicsEffectComponent>("graphics", node, entity);
    // decodeComponent<HealthComponent>("health", node, entity);
    // decodeComponent<NpcComponent>("npc", node, entity);
    // decodeComponent<OpenableComponent>("open", node, entity);
    // decodeComponent<PlayerComponent>("player", node, entity);
    // decodeComponent<SpriteComponent>("sprite", node, entity);
    // decodeComponent<ConnectorComponent>("connector", node, entity);
    // decodeComponent<WearableComponent>("wear", node, entity);
    // decodeComponent<WieldableComponent>("wield", node, entity);
    // decodeComponent<GroupingComponent>("grouping", node, entity);
    // decodeComponent<ExperienceComponent>("experience", node, entity);
    // decodeComponent<ExperienceComponent>("key", node, entity);
    // decodeComponent<ExperienceComponent>("fight", node, entity);
}

template <typename T>
void YamlConverter::encodeComponent(const std::string& name, YAML::Node& node,
                                    EntityId entity) {
    auto* comp = components()->get<T>(entity);
    if (comp) {
        node[entity][name] = *comp;
    }
}

template <typename T>
void YamlConverter::decodeComponent(const std::string& name,
                                    const YAML::Node& node, EntityId entity) {
    if (node[name].IsDefined()) {
        *(components()->make<T>(entity)) = node[name].as<T>();
    }
}
