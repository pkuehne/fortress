#include "yaml_converter.h"

template <typename T>
void loadComponent(const std::string& name, GameState* state, YAML::Node& node,
                   EntityId entity) {
    auto* comp = state->components()->get<T>(entity);
    if (comp) {
        node[entity][name] = *comp;
    }
}

void encodeEntity(GameState* state, YAML::Node& node, EntityId entity) {
    loadComponent<ColliderComponent>("collide", state, node, entity);
    loadComponent<ConsumableComponent>("consue", state, node, entity);
    loadComponent<DescriptionComponent>("describe", state, node, entity);
    loadComponent<DroppableComponent>("drop", state, node, entity);
    loadComponent<EquipmentComponent>("equip", state, node, entity);
    loadComponent<GraphicsEffectComponent>("graphics", state, node, entity);
    loadComponent<HealthComponent>("health", state, node, entity);
    loadComponent<NpcComponent>("npc", state, node, entity);
    loadComponent<OpenableComponent>("open", state, node, entity);
    loadComponent<PlayerComponent>("player", state, node, entity);
    loadComponent<SpriteComponent>("sprite", state, node, entity);
    loadComponent<ConnectorComponent>("connector", state, node, entity);
    loadComponent<WearableComponent>("wear", state, node, entity);
    loadComponent<WieldableComponent>("wield", state, node, entity);
    loadComponent<GroupingComponent>("grouping", state, node, entity);

    node[entity]["location"] = state->entityManager()->getLocation(entity);
}

template <typename T>
void decodeComponent(GameState* state, const YAML::Node& node, EntityId entity,
                     const std::string& nodeName) {
    if (node[nodeName].IsDefined()) {
        *state->components()->make<T>(entity) = node[nodeName].as<T>();
    }
}

void decodeEntity(GameState* state, const YAML::Node& node, EntityId entity) {
    // Add Entity
    state->entityManager()->addEntity(entity, node["location"].as<Location>());

    decodeComponent<ColliderComponent>(state, node, entity, "collide");
    decodeComponent<ConsumableComponent>(state, node, entity, "consume");
    decodeComponent<DescriptionComponent>(state, node, entity, "describe");
    decodeComponent<DroppableComponent>(state, node, entity, "drop");
    decodeComponent<EquipmentComponent>(state, node, entity, "equip");
    decodeComponent<GraphicsEffectComponent>(state, node, entity, "graphics");
    decodeComponent<HealthComponent>(state, node, entity, "health");
    decodeComponent<NpcComponent>(state, node, entity, "npc");
    decodeComponent<OpenableComponent>(state, node, entity, "open");
    decodeComponent<PlayerComponent>(state, node, entity, "player");
    decodeComponent<SpriteComponent>(state, node, entity, "sprite");
    decodeComponent<ConnectorComponent>(state, node, entity, "connector");
    decodeComponent<WearableComponent>(state, node, entity, "wear");
    decodeComponent<WieldableComponent>(state, node, entity, "wield");
    decodeComponent<GroupingComponent>(state, node, entity, "grouping");
}
