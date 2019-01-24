#pragma once

#include "../core/game_system_base.h"
#include <yaml-cpp/yaml.h>

class PrefabSystem : public GameSystemBase {
public:
    void registerHandlers();

private:
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

private:
    std::map<std::string, YAML::Node> m_prefabs;
};