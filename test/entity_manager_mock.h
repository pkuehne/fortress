#include "entity_manager_interface.h"
#include <gmock/gmock.h>

class EntityManagerMock : public EntityManagerInterface {
public:
    MOCK_METHOD1 (initialise, void (GameEngineInterface* engine));
    MOCK_METHOD0 (destroy, void ());

    MOCK_METHOD0 (getPlayer, EntityId ());
    MOCK_METHOD0 (createEntity, EntityId ());
    MOCK_METHOD1 (destroyEntity, void (EntityId));

    MOCK_METHOD3 (createWallPrefab, EntityId (unsigned int x, unsigned int y, unsigned int z));
    MOCK_METHOD3 (createPlayerPrefab, EntityId (unsigned int x, unsigned int y, unsigned int z));
    MOCK_METHOD3 (createEnemyPrefab, EntityId (unsigned int x, unsigned int y, unsigned int z));
    MOCK_METHOD3 (createTilePrefab, EntityId (unsigned int x, unsigned int y, unsigned int z));
    MOCK_METHOD3 (createMarkerPrefab , EntityId (unsigned int x, unsigned int y, unsigned int z));
    MOCK_METHOD4 (createStairPrefab, EntityId (STAIR dir, unsigned int x, unsigned int y, unsigned int z));
    MOCK_METHOD0 (createWeaponPrefab, EntityId ());
    MOCK_METHOD0 (createShieldPrefab, EntityId ());
    MOCK_METHOD0 (createHelmetPrefab, EntityId ());

    MOCK_METHOD0 (getSprites, ComponentManagerInterface<SpriteComponent>* ());
    MOCK_METHOD0 (getColliders, ComponentManagerInterface<ColliderComponent>* ());
    MOCK_METHOD0 (getHealths, ComponentManagerInterface<HealthComponent>* ());
    MOCK_METHOD0 (getDescriptions, ComponentManagerInterface<DescriptionComponent>* ());
    MOCK_METHOD0 (getPlayers, ComponentManagerInterface<PlayerComponent>*());
    MOCK_METHOD0 (getNpcs, ComponentManagerInterface<NpcComponent>* ());
    MOCK_METHOD0 (getLocations, ComponentManagerInterface<LocationComponent>* ());
    MOCK_METHOD0 (getStairs, ComponentManagerInterface<StairComponent>* ());
    MOCK_METHOD0 (getEquipments, ComponentManagerInterface<EquipmentComponent>* ());
    MOCK_METHOD0 (getWearables, ComponentManagerInterface<WearableComponent>* ());
    MOCK_METHOD0 (getWieldables, ComponentManagerInterface<WieldableComponent>* ());

    MOCK_METHOD3 (findEntitiesNear, std::vector<EntityId>  (unsigned int x, unsigned int y, unsigned radius) );
    MOCK_METHOD2 (findEntitiesAt, std::vector<EntityId>  (unsigned int x, unsigned int y) );
    MOCK_METHOD2 (findEntitiesToThe, std::vector<EntityId>  (DIRECTION a_direction, EntityId a_entity) );

};
