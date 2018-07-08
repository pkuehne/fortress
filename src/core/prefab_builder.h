#ifndef __PREFAB_BUILDER_H__
#define __PREFAB_BUILDER_H__

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

    EntityId createWallPrefab(Location& location);
    EntityId createPlayerPrefab(Location& location);
    EntityId createEnemyPrefab(Location& location);
    EntityId createTrollPrefab(Location& location);
    EntityId createMarkerPrefab(Location& location);
    EntityId createStairPrefab(STAIR dir, Location& location);
    EntityId createWeaponPrefab(Location& location);
    EntityId createShieldPrefab(Location& location);
    EntityId createHelmetPrefab(Location& location);
    EntityId createPotionPrefab(Location& location);
    EntityId createTreePrefab(Location& location);
    EntityId createCorpsePrefab(Location& location, char sprite);
    EntityId createForesterPrefab(Location& location);
    EntityId createDogPrefab(Location& location);
    EntityId createApplePrefab(Location& location);
    EntityId createDoorPrefab(Location& location);

private:
    EntityManager* m_entities = nullptr;
    ComponentManager* m_components = nullptr;
    std::map<std::string, YAML::Node> m_species;
};

#endif
