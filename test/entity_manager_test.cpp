#include <gtest/gtest.h>
#include <entity_manager.h>
#include <game_engine_mock.h>
#include <window_manager.h>

using namespace ::testing;

TEST (EntityManager, createEntity)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_));

    manager.initialise(&engine);

    EntityId entity = manager.createEntity();
    ASSERT_NE (0, entity);

    manager.destroy();
}

TEST (EntityManager, destroyEntity)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EntityId        entity1 = 0;
    EntityId        entity2 = 0;
    EXPECT_CALL (engine, raiseEvent(_)).Times(3);

    manager.initialise(&engine);

    entity1 = manager.createEntity();
    entity2 = manager.createEntity();

    LocationComponent l_loc1;
    LocationComponent l_loc2;
    manager.getLocations()->add (entity1, l_loc1);
    manager.getLocations()->add (entity2, l_loc2);

    ASSERT_NE (static_cast<LocationComponent*>(0), manager.getLocations()->get (entity1));
    ASSERT_NE (static_cast<LocationComponent*>(0), manager.getLocations()->get (entity2));

    manager.destroyEntity (entity1);
    ASSERT_NE (static_cast<LocationComponent*>(0), manager.getLocations()->get (entity1));
    ASSERT_EQ (static_cast<LocationComponent*>(0), manager.getLocations()->get (entity2));

    manager.destroy();
}

TEST (EntityManager, createWallPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise(&engine);

    EntityId entity = manager.createWallPrefab (1, 2);
    EXPECT_EQ (1, entity);

    SpriteComponent* sprite = manager.getSprites()->get (entity);
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ ('#', sprite->sprite);

    LocationComponent* loc = manager.getLocations()->get (entity);
    EXPECT_EQ (1, loc->x);
    EXPECT_EQ (2, loc->y);

    ColliderComponent* collider = manager.getColliders()->get(entity);
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
}

TEST (EntityManager, createPlayerPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise(&engine);

    EntityId entity = manager.createPlayerPrefab (1, 2);
    EXPECT_EQ (1, entity);

    SpriteComponent* sprite = manager.getSprites()->get (entity);
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ ('@', sprite->sprite);

    LocationComponent* loc = manager.getLocations()->get (entity);
    EXPECT_EQ (1, loc->x);
    EXPECT_EQ (2, loc->y);

    ColliderComponent* collider = manager.getColliders()->get(entity);
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
}

TEST (EntityManager, createEnemyPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise(&engine);

    EntityId entity = manager.createEnemyPrefab (1, 2);
    EXPECT_EQ (1, entity);

    SpriteComponent* sprite = manager.getSprites()->get (entity);
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ ('O', sprite->sprite);

    LocationComponent* loc = manager.getLocations()->get (entity);
    EXPECT_EQ (1, loc->x);
    EXPECT_EQ (2, loc->y);

    ColliderComponent* collider = manager.getColliders()->get(entity);
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
}

TEST (EntityManager, createTilePrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise(&engine);

    EntityId entity = manager.createTilePrefab (1, 2);
    EXPECT_EQ (1, entity);

    SpriteComponent* sprite = manager.getSprites()->get (entity);
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ ('.', sprite->sprite);

    LocationComponent* loc = manager.getLocations()->get (entity);
    EXPECT_EQ (1, loc->x);
    EXPECT_EQ (2, loc->y);

    ColliderComponent* collider = manager.getColliders()->get(entity);
    EXPECT_EQ (static_cast<ColliderComponent*>(0), collider);
}

TEST (EntityManager, getPlayer)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(2);

    manager.initialise(&engine);
    EXPECT_EQ (0, manager.getPlayer());

    EntityId tile = manager.createTilePrefab (1, 2);
    EXPECT_EQ (0, manager.getPlayer());

    EntityId player = manager.createPlayerPrefab (1, 2);
    EXPECT_EQ (player, manager.getPlayer());
    EXPECT_NE (tile, manager.getPlayer());

}
