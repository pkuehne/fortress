#pragma once

#include "entity.h"
#include "utility.h"
#include <map>
#include <yaml-cpp/yaml.h>

class GameState;
class Location;
class EntityManager;
class ComponentManager;

class PrefabBuilder {
public:
    PrefabBuilder(EntityManager* e, ComponentManager* c);

    EntityId createNpc(Location& location);
    EntityId create(const std::string& name, Location& location);

    EntityId createPlayerPrefab(Location& location);
    EntityId createStairPrefab(STAIR dir, Location& location);
    EntityId createCorpsePrefab(Location& location, char sprite);

private:
    EntityManager* m_entities = nullptr;
    ComponentManager* m_components = nullptr;
    std::map<std::string, YAML::Node> m_prefabs;
};