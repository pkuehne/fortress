#include "prefab_builder.h"
#include "entity_manager.h"
#include "game_state.h"

#include "../components/collider_component.h"
#include "../components/connector_component.h"
#include "../components/consumable_component.h"
#include "../components/description_component.h"
#include "../components/droppable_component.h"
#include "../components/equipment_component.h"
#include "../components/grouping_component.h"
#include "../components/health_component.h"
#include "../components/npc_component.h"
#include "../components/openable_component.h"
#include "../components/player_component.h"
#include "../components/sprite_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"
#include "../world/grouping_manager.h"
#include "../world/world_info.h"
#include "yaml_converter.h"
#include <experimental/filesystem>
#include <glog/logging.h>
#include <iostream>
#include <yaml-cpp/yaml.h>

PrefabBuilder::PrefabBuilder(EntityManager* e, ComponentManager* c,
                             std::shared_ptr<WorldInfo> w)
    : m_entities(e), m_components(c), m_world(w) {}

void PrefabBuilder::loadPrefabsFromDirectory(const std::string& directory) {
    namespace fs = std::experimental::filesystem;
    for (auto& filename : fs::directory_iterator(directory)) {
        YAML::Node node = YAML::LoadFile(filename.path().relative_path());
        addPrefab(filename.path().stem(), node);
    }
}

void PrefabBuilder::addPrefab(const std::string& name, const YAML::Node& node) {
    m_prefabs[name] = node;
}

EntityId PrefabBuilder::create(const std::string& name,
                               const Location& location) const {
    if (name.empty()) {
        return 0;
    }
    auto iter = m_prefabs.find(name);
    if (m_prefabs.find(name) == m_prefabs.end()) {
        LOG(WARNING) << "Invalid prefab '" << name << "' requested"
                     << std::endl;
        return 0;
    }

    YAML::Node node = iter->second;
    EntityId entity = m_entities->createEntity(location);

    addDescriptionComponent(node, entity);
    addSpriteComponent(node, entity);
    addColliderComponent(node, entity);
    addHealthComponent(node, entity);
    addDroppableComponent(node, entity);
    addConsumableComponent(node, entity);
    addOpenableComponent(node, entity);
    addWearableComponent(node, entity);
    addWieldableComponent(node, entity);
    addEquipmentComponent(node, entity);
    addConnectorComponent(node, entity);
    addNpcComponent(node, entity);
    addPlayerComponent(node, entity);
    addGroupingComponent(node, entity);

    return entity;
}

void PrefabBuilder::addDescriptionComponent(YAML::Node& node,
                                            EntityId entity) const {
    auto l_description = m_components->make<DescriptionComponent>(entity);
    l_description->title = node["name"].as<std::string>("Unknown");
    l_description->text =
        node["description"].as<std::string>("It's hard to describe");
}

void PrefabBuilder::addSpriteComponent(YAML::Node& node,
                                       EntityId entity) const {
    if (!node["symbol"].IsDefined()) {
        return;
    }

    auto l_sprite = m_components->make<SpriteComponent>(entity);
    l_sprite->fgColor = node["foreground-color"].as<Color>(Color(WHITE));
    l_sprite->bgColor = node["background-color"].as<Color>(Color(BLACK));
    l_sprite->sprite = node["symbol"].as<unsigned int>('?');
}

void PrefabBuilder::addColliderComponent(YAML::Node& node,
                                         EntityId entity) const {
    if (!node["collidable"].as<bool>(true)) {
        return;
    }
    m_components->make<ColliderComponent>(entity);
}

void PrefabBuilder::addHealthComponent(YAML::Node& node,
                                       EntityId entity) const {
    if (!node["health"].IsDefined()) {
        return;
    }
    auto l_health = m_components->make<HealthComponent>(entity);
    l_health->health = node["health"].as<unsigned int>(1);
}

void PrefabBuilder::addDroppableComponent(YAML::Node& node,
                                          EntityId entity) const {
    if (!node["droppable"].IsDefined()) {
        return;
    }
    m_components->make<DroppableComponent>(entity);
}
void PrefabBuilder::addConsumableComponent(YAML::Node& node,
                                           EntityId entity) const {
    if (!node["consumable"].IsDefined()) {
        return;
    }
    auto l_consumable = m_components->make<ConsumableComponent>(entity);
    l_consumable->quenches =
        static_cast<HUNGER_THIRST>(node["consumable"]["quenches"].as<int>(0));
    l_consumable->quenchStrength = node["consumable"]["strength"].as<int>(0);
    l_consumable->effect =
        static_cast<EFFECT>(node["consumable"]["effect"].as<int>(0));
    l_consumable->effectStrength =
        node["consumable"]["effectStrength"].as<int>(0);
}

void PrefabBuilder::addOpenableComponent(YAML::Node& node,
                                         EntityId entity) const {
    if (!node["openable"].IsDefined()) {
        return;
    }
    auto l_openable = m_components->make<OpenableComponent>(entity);
    l_openable->open = node["openable"]["open"].as<bool>(false);
}

void PrefabBuilder::addWearableComponent(YAML::Node& node,
                                         EntityId entity) const {
    if (!node["wearable"].IsDefined()) {
        return;
    }
    auto l_wearable = m_components->make<WearableComponent>(entity);
    l_wearable->position =
        static_cast<WearablePosition>(node["wearable"]["position"].as<int>(0));
}
void PrefabBuilder::addWieldableComponent(YAML::Node& node,
                                          EntityId entity) const {
    if (!node["wieldable"].IsDefined()) {
        return;
    }
    auto l_wieldable = m_components->make<WieldableComponent>(entity);
    l_wieldable->position = static_cast<WieldablePosition>(
        node["wieldable"]["position"].as<int>(0));
    l_wieldable->baseDamage = node["wieldable"]["damage"].as<int>(0);
    l_wieldable->baseDefence = node["wieldable"]["defence"].as<int>(0);
}

void PrefabBuilder::addEquipmentComponent(YAML::Node& node,
                                          EntityId entity) const {
    if (!node["equipment"].IsDefined()) {
        return;
    }
    Location invalidLoc;

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

    l_equipment->rightHandWieldable =
        create(node["equipment"]["rightHand"].as<std::string>(""), invalidLoc);
    l_equipment->leftHandWieldable =
        create(node["equipment"]["leftHand"].as<std::string>(""), invalidLoc);
}

void PrefabBuilder::addConnectorComponent(YAML::Node& node,
                                          EntityId entity) const {
    if (!node["connector"].IsDefined()) {
        return;
    }
    m_components->make<ConnectorComponent>(entity);
}

void PrefabBuilder::addNpcComponent(YAML::Node& node, EntityId entity) const {
    if (!node["smart"].IsDefined()) {
        return;
    }
    auto l_npc = m_components->make<NpcComponent>(entity);
    l_npc->stateMachine = node["smart"]["fsm"].as<std::string>("human");
    l_npc->attribs["seek_target"] = node["smart"]["target"].as<std::string>("");
}

void PrefabBuilder::addPlayerComponent(YAML::Node& node,
                                       EntityId entity) const {
    if (!node["player"].IsDefined()) {
        return;
    }
    m_components->make<PlayerComponent>(entity);
}

void PrefabBuilder::addGroupingComponent(YAML::Node& node,
                                         EntityId entity) const {
    if (!node["groupings"].IsDefined()) {
        return;
    }
    auto l_grouping = m_components->make<GroupingComponent>(entity);
    for (YAML::const_iterator iter = node["groupings"].begin();
         iter != node["groupings"].end(); ++iter) {
        std::string group(iter->as<std::string>());

        m_world->getGroupings().addEntityToGrouping(entity, group);
        l_grouping->groupings.push_back(group);
    }
}
