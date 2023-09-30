#include "prefab_system.h"
#include "../components/debug_component.h"
#include "../components/experience_component.h"
#include "../components/key_component.h"
#include "../components/openable_component.h"
#include "../components/player_component.h"
#include "../core/yaml_converter.h"
#include <experimental/filesystem>
#include <iostream>
#include <spdlog/spdlog.h>
#include <yaml-cpp/yaml.h>

void PrefabSystem::registerHandlers() {
    events()->subscribe<InstantiatePrefabEvent>([=](auto event) {
        auto iter = m_prefabs.find(event.prefab);
        if (iter == m_prefabs.end()) {
            spdlog::warn("Invalid prefab '{}' requested", event.prefab);
            return;
        }

        YAML::Node node = iter->second;
        EntityId entity = event.entity;
        std::string name(event.prefab + std::string("_") +
                         std::to_string(event.entity));
        entities()->world().entity(event.entity).set_name(name.c_str());

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
        addExperienceComponent(node, entity);
        addGroupingComponent(node, entity);
        addKeyComponent(node, entity);

        events()->fire<PrefabCreatedEvent>(event.entity, event.prefab);
    });

    std::string path = "../data/prefabs/";
    loadPrefabsFromDirectory(path);

    entities()
        ->world()
        .component<DescriptionComponent>()
        .member<std::string>("title")
        .member<std::string>("text");
    entities()
        ->world()
        .component<OpenableComponent>()
        .member<bool>("open")
        .member<bool>("locked");
    entities()
        ->world()
        .component<ExperienceComponent>()
        .member<unsigned int>("xp")
        .member<unsigned int>("level");
    entities()
        ->world()
        .component<HealthComponent>()
        .member<unsigned int>("health")
        .member<unsigned int>("thirst")
        .member<unsigned int>("hunger")
        .member<unsigned int>("thirstRate")
        .member<unsigned int>("hungerRate")
        .member<unsigned int>("thirstStep")
        .member<unsigned int>("hungerStep");
    entities()
        ->world()
        .component<ConsumableComponent>()
        .member<int>("quenches")
        .member<int>("quenchStrength")
        .member<int>("effect")
        .member<int>("effectStrength");
    entities()
        ->world()
        .component<EquipmentComponent>()
        .member<unsigned long>("headWearable")
        .member<unsigned long>("faceWearable")
        .member<unsigned long>("chestWearable")
        .member<unsigned long>("armsWearable")
        .member<unsigned long>("handsWearable")
        .member<unsigned long>("legsWearable")
        .member<unsigned long>("feetWearable")
        .member<unsigned long>("rightHandWieldable")
        .member<unsigned long>("leftHandWieldable")
        .member<int>("maxCarryWeight")
        .member<int>("maxCarryVolume");
    entities()
        ->world()
        .component<GraphicsEffectComponent>()
        .member<unsigned int>("ticks")
        .member<unsigned int>("duration")
        .member<unsigned int>("org_tile")
        .member<int>("type")
        .member<bool>("removeEntity");
    entities()
        ->world()
        .component<NpcComponent>()
        .member<std::string>("stateMachine")
        .member<std::string>("state")
        .member<unsigned long>("target")
        .member<unsigned int>("losDistance");
    entities()
        ->world()
        .component<PlayerComponent>()
        .member<unsigned long>("turn")
        .member<bool>("playerTurn");
    entities()
        ->world()
        .component<SpriteComponent>()
        .member<unsigned int>("sprite")
        .member<unsigned int>("renderLayer");
    entities()->world().component<ConnectorComponent>().member<unsigned int>(
        "target");
    entities()
        ->world()
        .component<WearableComponent>()
        .member<int>("baseDamageAbsorb")
        .member<int>("position")
        .member<int>("warmth");
    entities()
        ->world()
        .component<WieldableComponent>()
        .member<int>("baseDamage")
        .member<int>("baseDefence")
        .member<int>("position");
}

void PrefabSystem::loadPrefabsFromDirectory(const std::string& directory) {
    namespace fs = std::experimental::filesystem;
    for (auto& filename : fs::directory_iterator(directory)) {
        YAML::Node node = YAML::LoadFile(filename.path().relative_path());
        addPrefab(filename.path().stem(), node);
    }
}

void PrefabSystem::addPrefab(const std::string& name, const YAML::Node& node) {
    m_prefabs[name] = node;
}

void PrefabSystem::addDescriptionComponent(YAML::Node& node,
                                           EntityId entity) const {
    entities()->world().entity(entity).set<DescriptionComponent>(
        {node["name"].as<std::string>("Unknown"),
         node["description"].as<std::string>("It's hard to describe")});
}

void PrefabSystem::addSpriteComponent(YAML::Node& node, EntityId entity) const {
    if (!node["symbol"].IsDefined()) {
        return;
    }

    auto l_sprite = SpriteComponent();
    l_sprite.fgColor = node["foreground-color"].as<Color>(Color(WHITE));
    l_sprite.bgColor = node["background-color"].as<Color>(Color(BLACK));
    unsigned int sprite = node["symbol"].as<unsigned int>(0);
    l_sprite.sprite = sprite ? sprite : node["symbol"].as<char>('?');
    entities()->world().entity(entity).set<SpriteComponent>(l_sprite);
}

void PrefabSystem::addColliderComponent(YAML::Node& node,
                                        EntityId entity) const {
    if (!node["collidable"].as<bool>(true)) {
        return;
    }
    entities()->world().entity(entity).add<ColliderComponent>();
}

void PrefabSystem::addHealthComponent(YAML::Node& node, EntityId entity) const {
    if (!node["health"].IsDefined()) {
        return;
    }
    auto l_health = HealthComponent();
    l_health.health = node["health"].as<unsigned int>(1);
    entities()->world().entity(entity).set<HealthComponent>(l_health);
}

void PrefabSystem::addDroppableComponent(YAML::Node& node,
                                         EntityId entity) const {
    if (!node["droppable"].IsDefined()) {
        return;
    }
    entities()->world().entity(entity).add<DroppableComponent>();
}
void PrefabSystem::addConsumableComponent(YAML::Node& node,
                                          EntityId entity) const {
    if (!node["consumable"].IsDefined()) {
        return;
    }
    auto l_consumable = ConsumableComponent();
    l_consumable.quenches =
        static_cast<HUNGER_THIRST>(node["consumable"]["quenches"].as<int>(0));
    l_consumable.quenchStrength = node["consumable"]["strength"].as<int>(0);
    l_consumable.effect =
        static_cast<EFFECT>(node["consumable"]["effect"].as<int>(0));
    l_consumable.effectStrength =
        node["consumable"]["effectStrength"].as<int>(0);
    entities()->world().entity(entity).set<ConsumableComponent>(l_consumable);
}

void PrefabSystem::addOpenableComponent(YAML::Node& node,
                                        EntityId entity) const {
    if (!node["openable"].IsDefined()) {
        return;
    }
    entities()->world().entity(entity).set<OpenableComponent>({false, false});
}

void PrefabSystem::addWearableComponent(YAML::Node& node,
                                        EntityId entity) const {
    if (!node["wearable"].IsDefined()) {
        return;
    }
    auto l_wearable = WearableComponent();
    l_wearable.position =
        static_cast<WearablePosition>(node["wearable"]["position"].as<int>(0));
    entities()->world().entity(entity).set<WearableComponent>(l_wearable);
}
void PrefabSystem::addWieldableComponent(YAML::Node& node,
                                         EntityId entity) const {
    if (!node["wieldable"].IsDefined()) {
        return;
    }
    auto l_wieldable = WieldableComponent();
    l_wieldable.position = static_cast<WieldablePosition>(
        node["wieldable"]["position"].as<int>(0));
    l_wieldable.baseDamage = node["wieldable"]["damage"].as<int>(0);
    l_wieldable.baseDefence = node["wieldable"]["defence"].as<int>(0);
    entities()->world().entity(entity).set<WieldableComponent>(l_wieldable);
}

void PrefabSystem::addEquipmentComponent(YAML::Node& node,
                                         EntityId entity) const {
    if (!node["equipment"].IsDefined()) {
        return;
    }
    Location invalidLoc;

    auto l_equipment = EquipmentComponent();
    l_equipment.maxCarryVolume = node["equipment"]["maxVolume"].as<int>(0);
    l_equipment.maxCarryWeight = node["equipment"]["maxWeight"].as<int>(0);
    l_equipment.headWearable = instantiatePrefab(
        node["equipment"]["head"].as<std::string>(""), invalidLoc);
    l_equipment.faceWearable = instantiatePrefab(
        node["equipment"]["face"].as<std::string>(""), invalidLoc);
    l_equipment.chestWearable = instantiatePrefab(
        node["equipment"]["chest"].as<std::string>(""), invalidLoc);
    l_equipment.armsWearable = instantiatePrefab(
        node["equipment"]["arms"].as<std::string>(""), invalidLoc);
    l_equipment.handsWearable = instantiatePrefab(
        node["equipment"]["hands"].as<std::string>(""), invalidLoc);
    l_equipment.legsWearable = instantiatePrefab(
        node["equipment"]["legs"].as<std::string>(""), invalidLoc);
    l_equipment.feetWearable = instantiatePrefab(
        node["equipment"]["feet"].as<std::string>(""), invalidLoc);

    l_equipment.rightHandWieldable = instantiatePrefab(
        node["equipment"]["rightHand"].as<std::string>(""), invalidLoc);
    l_equipment.leftHandWieldable = instantiatePrefab(
        node["equipment"]["leftHand"].as<std::string>(""), invalidLoc);

    if (node["equipment"]["carried"].IsSequence()) {
        for (auto& item :
             node["equipment"]["carried"].as<std::vector<std::string>>()) {
            l_equipment.carriedEquipment.push_back(
                instantiatePrefab(item, invalidLoc));
        }
    }
    entities()->world().entity(entity).set<EquipmentComponent>(l_equipment);
}

void PrefabSystem::addConnectorComponent(YAML::Node& node,
                                         EntityId entity) const {
    if (!node["connector"].IsDefined()) {
        return;
    }
    entities()->world().entity(entity).add<ConnectorComponent>();
}

void PrefabSystem::addNpcComponent(YAML::Node& node, EntityId entity) const {
    if (!node["smart"].IsDefined()) {
        return;
    }
    spdlog::debug("Adding NPC component to {}", entity);
    auto l_npc = NpcComponent();
    l_npc.stateMachine = node["smart"]["fsm"].as<std::string>("human");
    l_npc.attribs["seek_target"] = node["smart"]["target"].as<std::string>("");
    entities()->world().entity(entity).set<NpcComponent>(l_npc);
}

void PrefabSystem::addPlayerComponent(YAML::Node& node, EntityId entity) const {
    if (!node["player"].IsDefined()) {
        return;
    }
    entities()
        ->world()
        .entity(entity)
        .set_name("player")
        .add<PlayerComponent>()
        .add<DebugComponent>();
}

void PrefabSystem::addExperienceComponent(YAML::Node& node,
                                          EntityId entity) const {
    if (!node["experience"].IsDefined()) {
        return;
    }
    entities()->world().entity(entity).add<ExperienceComponent>();
}

void PrefabSystem::addGroupingComponent(YAML::Node& node,
                                        EntityId entity) const {
    if (!node["groupings"].IsDefined()) {
        return;
    }
    auto l_grouping = GroupingComponent();
    for (YAML::const_iterator iter = node["groupings"].begin();
         iter != node["groupings"].end(); ++iter) {
        std::string group(iter->as<std::string>());
        l_grouping.groupings.push_back(group);
    }
    entities()->world().entity(entity).set<GroupingComponent>(l_grouping);
}

void PrefabSystem::addKeyComponent(YAML::Node& node, EntityId entity) const {
    if (!node["key"].IsDefined()) {
        return;
    }
    entities()->world().entity(entity).add<KeyComponent>();
}