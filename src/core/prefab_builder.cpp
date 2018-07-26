#include "prefab_builder.h"
#include "entity_manager.h"
#include "game_state.h"

#include "../components/collider_component.h"
#include "../components/connector_component.h"
#include "../components/consumable_component.h"
#include "../components/description_component.h"
#include "../components/droppable_component.h"
#include "../components/equipment_component.h"
#include "../components/health_component.h"
#include "../components/identity_component.h"
#include "../components/npc_component.h"
#include "../components/openable_component.h"
#include "../components/player_component.h"
#include "../components/sprite_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"
#include "yaml_converter.h"
#include <experimental/filesystem>
#include <iostream>
#include <yaml-cpp/yaml.h>

PrefabBuilder::PrefabBuilder(EntityManager* e, ComponentManager* c)
    : m_entities(e), m_components(c) {
    namespace fs = std::experimental::filesystem;

    std::string path = "./data/prefabs/";
    for (auto& filename : fs::directory_iterator(path)) {
        YAML::Node node = YAML::LoadFile(filename.path().relative_path());
        m_prefabs[filename.path().stem()] = node;
    }
}

EntityId PrefabBuilder::create(const std::string& name,
                               const Location& location) {
    if (name.empty()) {
        return 0;
    }
    if (m_prefabs.find(name) == m_prefabs.end()) {
        LOG(WARNING) << "Invalid prefab '" << name << "' requested"
                     << std::endl;
        return 0;
    }

    YAML::Node& node = m_prefabs[name];

    EntityId entity = m_entities->createEntity(location);
    Location invalidLoc;

    // Description Component
    auto l_description = m_components->make<DescriptionComponent>(entity);
    l_description->title = node["name"].as<std::string>("Unknown");
    l_description->text =
        node["description"].as<std::string>("It's hard to describe");

    // Sprite
    auto l_sprite = m_components->make<SpriteComponent>(entity);
    l_sprite->fgColor = node["foreground-color"].as<Color>(Color(WHITE));
    l_sprite->bgColor = node["background-color"].as<Color>(Color(BLACK));
    l_sprite->sprite = node["symbol"].as<unsigned int>('?');

    // Collider Component
    if (node["collidable"].as<bool>(true)) {
        m_components->make<ColliderComponent>(entity);
    }

    // Health Component
    if (node["health"].IsDefined()) {
        auto l_health = m_components->make<HealthComponent>(entity);
        l_health->health = node["health"].as<unsigned int>(1);
    }

    // Droppable Component
    if (node["droppable"].IsDefined()) {
        m_components->make<DroppableComponent>(entity);
    }

    // Consumable Component
    if (node["consumable"].IsDefined()) {
        auto l_consumable = m_components->make<ConsumableComponent>(entity);
        l_consumable->quenches = static_cast<HUNGER_THIRST>(
            node["consumable"]["quenches"].as<int>(0));
        l_consumable->quenchStrength =
            node["consumable"]["strength"].as<int>(0);
        l_consumable->effect =
            static_cast<EFFECT>(node["consumable"]["effect"].as<int>(0));
        l_consumable->effectStrength =
            node["consumable"]["effectStrength"].as<int>(0);
    }

    // Openable Component
    if (node["openable"].IsDefined()) {
        auto l_openable = m_components->make<OpenableComponent>(entity);
        l_openable->open = node["openable"]["open"].as<bool>(false);
    }

    // Wearable Comoponent
    if (node["wearable"].IsDefined()) {
        auto l_wearable = m_components->make<WearableComponent>(entity);
        l_wearable->position = static_cast<WearablePosition>(
            node["wearable"]["position"].as<int>(0));
    }

    // Wieldable Component
    if (node["wieldable"].IsDefined()) {
        auto l_wieldable = m_components->make<WieldableComponent>(entity);
        l_wieldable->position = static_cast<WieldablePosition>(
            node["wieldable"]["position"].as<int>(0));
        l_wieldable->baseDamage = node["wieldable"]["damage"].as<int>(0);
        l_wieldable->baseDefence = node["wieldable"]["defence"].as<int>(0);
    }

    // Equipment Component
    if (node["equipment"].IsDefined()) {
        auto l_equipment = m_components->make<EquipmentComponent>(entity);
        l_equipment->maxCarryVolume = node["equipment"]["maxVolume"].as<int>(0);
        l_equipment->maxCarryWeight = node["equipment"]["maxWeight"].as<int>(0);
        l_equipment->headWearable =
            create(node["equipment"]["head"].as<std::string>(""), invalidLoc);
        l_equipment->faceWearable =
            create(node["equipment"]["face"].as<std::string>(""), invalidLoc);
        l_equipment->chestWearable =
            create(node["equipment"]["chest"].as<std::string>(""), invalidLoc);
        l_equipment->armsWearable =
            create(node["equipment"]["arms"].as<std::string>(""), invalidLoc);
        l_equipment->handsWearable =
            create(node["equipment"]["hands"].as<std::string>(""), invalidLoc);
        l_equipment->legsWearable =
            create(node["equipment"]["legs"].as<std::string>(""), invalidLoc);
        l_equipment->feetWearable =
            create(node["equipment"]["feet"].as<std::string>(""), invalidLoc);

        l_equipment->rightHandWieldable = create(
            node["equipment"]["rightHand"].as<std::string>(""), invalidLoc);
        l_equipment->leftHandWieldable = create(
            node["equipment"]["leftHand"].as<std::string>(""), invalidLoc);
    }

    // Connector Component
    if (node["connector"].IsDefined()) {
        m_components->make<ConnectorComponent>(entity);
    }

    // NPC Component
    if (node["smart"].IsDefined()) {
        auto l_npc = m_components->make<NpcComponent>(entity);
        l_npc->stateMachine = node["smart"]["fsm"].as<std::string>("human");
        l_npc->attribs["seek_target"] =
            node["smart"]["target"].as<std::string>("");
    }

    if (node["player"].IsDefined()) {
        m_components->make<PlayerComponent>(entity);
    }

    if (node["smart"].IsDefined() || node["player"].IsDefined()) {
        auto l_identity = m_components->make<IdentityComponent>(entity);
        l_identity->faction = node["faction"].as<std::string>("");
    }

    return entity;
}
