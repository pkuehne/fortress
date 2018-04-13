#ifndef __PREFAB_BUILDER_H__
#define __PREFAB_BUILDER_H__

#include "entity.h"
#include "utility.h"
class GameState;
class Location;

class PrefabBuilder 
{
public:
    PrefabBuilder (GameState* state);

    EntityId createWallPrefab (Location& location);
    EntityId createPlayerPrefab (Location& location);
    EntityId createEnemyPrefab (Location& location);
    EntityId createTrollPrefab (Location& location);
    EntityId createMarkerPrefab (Location& location);
    EntityId createStairPrefab (STAIR dir, Location& location);
    EntityId createWeaponPrefab (Location& location);
    EntityId createShieldPrefab (Location& location);
    EntityId createHelmetPrefab (Location& location);
    EntityId createPotionPrefab (Location& location);
    EntityId createTreePrefab(Location& location);
    EntityId createCorpsePrefab (Location& location, char sprite);
    EntityId createForesterPrefab (Location& location);

private:
    GameState* m_state;
};

#endif
