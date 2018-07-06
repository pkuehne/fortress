#include "prefab_builder.h"
#include "entity_manager.h"
#include "game_state.h"

#include "../components/collider_component.h"
#include "../components/consumable_component.h"
#include "../components/description_component.h"
#include "../components/droppable_component.h"
#include "../components/equipment_component.h"
#include "../components/health_component.h"
#include "../components/npc_component.h"
#include "../components/openable_component.h"
#include "../components/player_component.h"
#include "../components/sprite_component.h"
#include "../components/stair_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"
#include "floor.h"

PrefabBuilder::PrefabBuilder(GameState* state) : m_state(state) {}

EntityId PrefabBuilder::createWallPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    // Sprite Component
    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(GREY);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'W';

    // Collider Component
    m_state->components()->make<ColliderComponent>(l_entity);

    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Wall";
    l_description->text = "A smooth granite wall";

    return l_entity;
}

EntityId PrefabBuilder::createPlayerPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    // Sprite Component
    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(WHITE);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = '@';
    l_sprite->renderLayer = 2;

    // Collider Component
    m_state->components()->make<ColliderComponent>(l_entity);

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Player";
    l_description->text = "This isn't the time for introspection";

    // Health Component
    HealthComponent* l_health =
        m_state->components()->make<HealthComponent>(l_entity);
    l_health->health = 10;

    // Player Component
    m_state->components()->make<PlayerComponent>(l_entity);

    // Euipment Component
    Location invalidLoc;
    EquipmentComponent* l_equipment =
        m_state->components()->make<EquipmentComponent>(l_entity);
    l_equipment->rightHandWieldable = createWeaponPrefab(invalidLoc);
    l_equipment->leftHandWieldable = createShieldPrefab(invalidLoc);
    l_equipment->headWearable = createHelmetPrefab(invalidLoc);

    return l_entity;
}

EntityId PrefabBuilder::createEnemyPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    // Sprite Component
    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(RED);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'O';
    l_sprite->renderLayer = 2;

    // Collider Component
    m_state->components()->make<ColliderComponent>(l_entity);

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Orc";
    l_description->text = "A vile, stinking creature revelling in the dark.";

    // Health Component
    HealthComponent* l_health =
        m_state->components()->make<HealthComponent>(l_entity);
    l_health->health = 1;

    // NPC Component
    NpcComponent* l_npc = m_state->components()->make<NpcComponent>(l_entity);
    l_npc->state = "";
    l_npc->attribs["seek_target"] = "Player";
    l_npc->stateMachine = "human";

    // Euipment Component
    Location invalidLoc;
    EquipmentComponent* l_equipment =
        m_state->components()->make<EquipmentComponent>(l_entity);
    l_equipment->rightHandWieldable = createWeaponPrefab(invalidLoc);
    l_equipment->leftHandWieldable = createShieldPrefab(invalidLoc);
    l_equipment->headWearable = createHelmetPrefab(invalidLoc);

    return l_entity;
}

EntityId PrefabBuilder::createTrollPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    // Sprite Component
    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(RED);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'T';

    // Collider Component
    m_state->components()->make<ColliderComponent>(l_entity);

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Troll";
    l_description->text =
        "It is huge, with fierce red eyes, crackling with magic.";

    // Health Component
    HealthComponent* l_health =
        m_state->components()->make<HealthComponent>(l_entity);
    l_health->health = 8;

    // NPC Component
    NpcComponent* l_npc = m_state->components()->make<NpcComponent>(l_entity);
    l_npc->state = "";
    l_npc->attribs["seek_target"] = "Player";
    l_npc->stateMachine = "human";

    // Euipment Component
    Location invalidLoc;
    EquipmentComponent* l_equipment =
        m_state->components()->make<EquipmentComponent>(l_entity);
    l_equipment->rightHandWieldable = createWeaponPrefab(invalidLoc);
    l_equipment->leftHandWieldable = createShieldPrefab(invalidLoc);
    l_equipment->headWearable = createHelmetPrefab(invalidLoc);

    return l_entity;
}

EntityId PrefabBuilder::createMarkerPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    // Sprite Component
    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(YELLOW);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'X';

    return l_entity;
}

EntityId PrefabBuilder::createStairPrefab(STAIR dir, Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    // Sprite Component
    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(WHITE);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = (dir == STAIR_DOWN) ? 31 : 30; //'>' : '<';

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title =
        (dir == STAIR_DOWN) ? "A stairway down" : "A stairway up";
    l_description->text = "It has rough-hewn steps";

    // StairComponent
    StairComponent* l_stair =
        m_state->components()->make<StairComponent>(l_entity);
    l_stair->direction = dir;
    l_stair->target = 0;

    return l_entity;
}

EntityId PrefabBuilder::createWeaponPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(YELLOW);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 189; //'$';

    WieldableComponent* l_wieldable =
        m_state->components()->make<WieldableComponent>(l_entity);
    l_wieldable->position = WieldableRightHand;
    l_wieldable->baseDamage = 2;
    l_wieldable->baseDefence = 0;

    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Sword";
    l_description->text = "Stick 'em with the pointy end!";

    m_state->components()->make<DroppableComponent>(l_entity);

    return l_entity;
}

EntityId PrefabBuilder::createShieldPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(YELLOW);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 189; //'$';

    WieldableComponent* l_wieldable =
        m_state->components()->make<WieldableComponent>(l_entity);
    l_wieldable->position = WieldableLeftHand;
    l_wieldable->baseDamage = 0;
    l_wieldable->baseDefence = 4;

    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Shield";
    l_description->text = "Return with your shield or upon it!";

    m_state->components()->make<DroppableComponent>(l_entity);

    return l_entity;
}

EntityId PrefabBuilder::createHelmetPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(YELLOW);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 189; //'$';

    WearableComponent* l_wearable =
        m_state->components()->make<WearableComponent>(l_entity);
    l_wearable->position = WearableHead;

    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Helmet";
    l_description->text = "It says: One Size Fits All";

    m_state->components()->make<DroppableComponent>(l_entity);

    return l_entity;
}

EntityId PrefabBuilder::createPotionPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(YELLOW);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'Z' + 1; //'$';

    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Potion";
    l_description->text = "The label proclaims: Zero Calories!";

    m_state->components()->make<DroppableComponent>(l_entity);

    ConsumableComponent* l_consumable =
        m_state->components()->make<ConsumableComponent>(l_entity);
    l_consumable->quenches = THIRST;
    l_consumable->quenchStrength = 3;
    l_consumable->effect = HEALTH_EFFECT;
    l_consumable->effectStrength = 2;

    return l_entity;
}

EntityId PrefabBuilder::createTreePrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(BROWN);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'T';

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Tree";
    l_description->text = "Or maybe an Ent...?";

    // Health Component
    HealthComponent* l_health =
        m_state->components()->make<HealthComponent>(l_entity);
    l_health->health = 2;

    m_state->components()->make<ColliderComponent>(l_entity);

    return l_entity;
}

EntityId PrefabBuilder::createCorpsePrefab(Location& location, char sprite) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(GREY);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = sprite;

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Corpse";
    l_description->text = "A mangled body, splayed, leaking blood.";

    return l_entity;
}

EntityId PrefabBuilder::createForesterPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(GREEN);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'H';

    // Collider Component
    m_state->components()->make<ColliderComponent>(l_entity);

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Forester";
    l_description->text = "Chopping trees, hunting foxes, all in a day's work.";

    // Health Component
    HealthComponent* l_health =
        m_state->components()->make<HealthComponent>(l_entity);
    l_health->health = 4;

    // NPC Component
    NpcComponent* l_npc = m_state->components()->make<NpcComponent>(l_entity);
    l_npc->state = "";
    l_npc->stateMachine = "human";
    l_npc->attribs["seek_target"] = "Tree";

    // Euipment Component
    Location invalidLoc;
    EquipmentComponent* l_equipment =
        m_state->components()->make<EquipmentComponent>(l_entity);
    l_equipment->rightHandWieldable = createWeaponPrefab(invalidLoc);
    l_equipment->leftHandWieldable = createShieldPrefab(invalidLoc);
    l_equipment->headWearable = createHelmetPrefab(invalidLoc);

    return l_entity;
}

EntityId PrefabBuilder::createDogPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(GREEN);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'd';

    // Collider Component
    m_state->components()->make<ColliderComponent>(l_entity);

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Dog";
    l_description->text = "Man's best friend";

    // Health Component
    HealthComponent* l_health =
        m_state->components()->make<HealthComponent>(l_entity);
    l_health->health = 4;

    // NPC Component
    NpcComponent* l_npc = m_state->components()->make<NpcComponent>(l_entity);
    l_npc->state = "";
    l_npc->stateMachine = "dog";
    l_npc->attribs["seek_target"] = "Forester";

    return l_entity;
}

EntityId PrefabBuilder::createApplePrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    SpriteComponent* l_sprite =
        m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(RED);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'A';

    // Description Component
    DescriptionComponent* l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Apple";
    l_description->text = "One of these a day, keeps the sawbones away";

    m_state->components()->make<DroppableComponent>(l_entity);

    ConsumableComponent* l_consumable =
        m_state->components()->make<ConsumableComponent>(l_entity);
    l_consumable->quenches = HUNGER;
    l_consumable->quenchStrength = 2;

    return l_entity;
}

EntityId PrefabBuilder::createDoorPrefab(Location& location) {
    EntityId l_entity = m_state->createEntity(location);

    auto l_sprite = m_state->components()->make<SpriteComponent>(l_entity);
    l_sprite->fgColor = Color(GREY);
    l_sprite->bgColor = Color(BLACK);
    l_sprite->sprite = 'D';

    auto l_description =
        m_state->components()->make<DescriptionComponent>(l_entity);
    l_description->title = "Door";
    l_description->text = "A wall that moves";

    auto l_openable = m_state->components()->make<OpenableComponent>(l_entity);
    l_openable->open = false;

    m_state->components()->make<ColliderComponent>(l_entity);

    return l_entity;
}