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
    auto* stair = state->components()->get<ConnectorComponent>(entity);
    auto* wear = state->components()->get<WearableComponent>(entity);
    auto* wield = state->components()->get<WieldableComponent>(entity);

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
    if (stair) {
        node[entity]["stair"] = *stair;
    }
    if (wear) {
        node[entity]["wear"] = *wear;
    }
    if (wield) {
        node[entity]["wield"] = *wield;
    }
    node[entity]["location"] = state->entityManager()->getLocation(entity);
}
