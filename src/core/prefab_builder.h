#pragma once

#include "entity.h"
#include "utility.h"
#include <map>
#include <yaml-cpp/yaml.h>

class GameState;
class Location;
class EntityManager;
class ComponentManager;
class WorldInfo;

class PrefabBuilder {
public:
    PrefabBuilder(EntityManager* e, ComponentManager* c,
                  std::shared_ptr<WorldInfo> w);

    /// @brief Construct a new entity in the given location from the given
    /// prefab
    /// @param[in] name The name of the prefab to construct
    /// @param[in] location The location to put the prefab once created
    EntityId create(const std::string& name, const Location& location) const;

    /// @brief Finds all yaml files in the given directory and loads them as
    /// prefabs
    /// @param[in] directory The directory to search
    void loadPrefabsFromDirectory(const std::string& directory);

    /// @brief Add a new pre-fab with the specified name to the list
    /// @param[in] name The name with which to create the prefab
    /// @param[in] node The top-level YAML node that holds all the prefabs data
    void addPrefab(const std::string& name, const YAML::Node& node);

    void addDescriptionComponent(YAML::Node& node, EntityId entity) const;
    void addSpriteComponent(YAML::Node& node, EntityId entity) const;
    void addColliderComponent(YAML::Node& node, EntityId entity) const;
    void addHealthComponent(YAML::Node& node, EntityId entity) const;
    void addConsumableComponent(YAML::Node& node, EntityId entity) const;
    void addDroppableComponent(YAML::Node& node, EntityId entity) const;
    void addOpenableComponent(YAML::Node& node, EntityId entity) const;
    void addWearableComponent(YAML::Node& node, EntityId entity) const;
    void addWieldableComponent(YAML::Node& node, EntityId entity) const;
    void addEquipmentComponent(YAML::Node& node, EntityId entity) const;
    void addConnectorComponent(YAML::Node& node, EntityId entity) const;
    void addNpcComponent(YAML::Node& node, EntityId entity) const;
    void addPlayerComponent(YAML::Node& node, EntityId entity) const;
    void addGroupingComponent(YAML::Node& node, EntityId entity) const;

    unsigned int countPrefabs() const { return m_prefabs.size(); }

private:
    EntityManager* m_entities = nullptr;
    ComponentManager* m_components = nullptr;
    std::shared_ptr<WorldInfo> m_world;
    std::map<std::string, YAML::Node> m_prefabs;
};