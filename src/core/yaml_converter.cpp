#include "yaml_converter.h"

void encodeEntity(GameState* state, YAML::Node& node, EntityId entity) {
    auto* collide = state->components()->get<ColliderComponent>(entity);
    auto* consume = state->components()->get<ConsumableComponent>(entity);
    auto* describe = state->components()->get<DescriptionComponent>(entity);
    auto* drop = state->components()->get<DroppableComponent>(entity);
    auto* equip = state->components()->get<EquipmentComponent>(entity);
    auto* graphics = state->components()->get<GraphicsEffectComponent>(entity);
    auto* health = state->components()->get<HealthComponent>(entity);
    auto* npc = state->components()->get<NpcComponent>(entity);
    auto* open = state->components()->get<OpenableComponent>(entity);
    auto* player = state->components()->get<PlayerComponent>(entity);
    auto* sprite = state->components()->get<SpriteComponent>(entity);
    auto* connector = state->components()->get<ConnectorComponent>(entity);
    auto* wear = state->components()->get<WearableComponent>(entity);
    auto* wield = state->components()->get<WieldableComponent>(entity);
    auto* grouping = state->components()->get<GroupingComponent>(entity);

    if (collide) {
        node[entity]["collide"] = *collide;
    }
    if (consume) {
        node[entity]["consume"] = *consume;
    }
    if (describe) {
        node[entity]["describe"] = *describe;
    }
    if (drop) {
        node[entity]["drop"] = *drop;
    }
    if (equip) {
        node[entity]["equip"] = *equip;
    }
    if (graphics) {
        node[entity]["graphics"] = *graphics;
    }
    if (health) {
        node[entity]["health"] = *health;
    }
    if (npc) {
        node[entity]["npc"] = *npc;
    }
    if (open) {
        node[entity]["open"] = *open;
    }
    if (player) {
        node[entity]["player"] = *player;
    }
    if (sprite) {
        node[entity]["sprite"] = *sprite;
    }
    if (connector) {
        node[entity]["connector"] = *connector;
    }
    if (wear) {
        node[entity]["wear"] = *wear;
    }
    if (wield) {
        node[entity]["wield"] = *wield;
    }
    if (grouping) {
        node[entity]["grouping"] = *grouping;
    }

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
