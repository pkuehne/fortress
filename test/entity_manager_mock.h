#include "entity_manager_interface.h"
#include <gmock/gmock.h>

class EntityManagerMock : public EntityManagerInterface {
public:
    MOCK_METHOD1 (initialise, void (GameEngineInterface* engine));
    MOCK_METHOD0 (destroy, void ());

    MOCK_METHOD1 (createEntity, Entity* (const std::string& name));
    MOCK_METHOD1 (destroyEntity, void (EntityId));
    MOCK_METHOD0 (getPlayer, Entity*());
    MOCK_METHOD2 (createWallPrefab, Entity* (unsigned int x, unsigned int y));
    MOCK_METHOD2 (createPlayerPrefab, Entity* (unsigned int x, unsigned int y));
    MOCK_METHOD2 (createEnemyPrefab, Entity* (unsigned int x, unsigned int y));
    MOCK_METHOD2 (createTilePrefab, Entity* (unsigned int x, unsigned int y));

    MOCK_METHOD0 (getSprites, ComponentManagerInterface<SpriteComponent>* ());
    MOCK_METHOD0 (getColliders, ComponentManagerInterface<ColliderComponent>* ());
    MOCK_METHOD0 (getHealths, ComponentManagerInterface<HealthComponent>* ());
    MOCK_METHOD0 (getDescriptions, ComponentManagerInterface<DescriptionComponent>* ());
    MOCK_METHOD1 (getEntity, Entity* (EntityId id));
};
