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

    Entity* entity = manager.createEntity("test");
    ASSERT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("test", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("test"));
    EXPECT_EQ (entity, manager.getEntity (0));

    manager.destroy();
}


TEST (EntityManager, destroyEntity)
{
    EntityManager   manager;
    GameEngineMock  engine;
    Entity*         entity = 0;
    EXPECT_CALL (engine, raiseEvent(_)).Times(3);

    manager.initialise(&engine);

    manager.createEntity("test");
    manager.createEntity("test2");
    entity = manager.getEntity ("test");
    ASSERT_NE (static_cast<Entity*>(0), entity);
    entity = manager.getEntity ("test2");
    ASSERT_NE (static_cast<Entity*>(0), entity);

    manager.destroyEntity ("test");
    entity = manager.getEntity ("test");
    ASSERT_EQ (static_cast<Entity*>(0), entity);
    entity = manager.getEntity ("test2");
    ASSERT_NE (static_cast<Entity*>(0), entity);

    manager.destroy();
}

TEST (EntityManager, getEntityEmpty)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(0);

    manager.initialise(&engine);

    EXPECT_EQ (static_cast<Entity*>(0), manager.getEntity ("test"));
    EXPECT_EQ (static_cast<Entity*>(0), manager.getEntity (0));
}

TEST (EntityManager, createWallPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise(&engine);

    Entity* entity = manager.createWallPrefab (1, 2);
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("Wall", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("Wall"));
    EXPECT_EQ (entity, manager.getEntity (0));

    SpriteComponent* sprite = manager.getSprites()->get (entity);
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ (1, sprite->xPos);
    EXPECT_EQ (2, sprite->yPos);
    EXPECT_EQ (247, sprite->sprite);

    ColliderComponent* collider = manager.getColliders()->get(entity);
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
}

TEST (EntityManager, createPlayerPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise(&engine);

    Entity* entity = manager.createPlayerPrefab (1, 2);
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("Player", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("Player"));
    EXPECT_EQ (entity, manager.getEntity (0));

    SpriteComponent* sprite = manager.getSprites()->get (entity);
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ (1, sprite->xPos);
    EXPECT_EQ (2, sprite->yPos);
    EXPECT_EQ ('@', sprite->sprite);

    ColliderComponent* collider = manager.getColliders()->get(entity);
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
}

TEST (EntityManager, createEnemyPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise(&engine);

    Entity* entity = manager.createEnemyPrefab (1, 2);
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("Orc", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("Orc"));
    EXPECT_EQ (entity, manager.getEntity (0));

    SpriteComponent* sprite = manager.getSprites()->get (entity);
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ (1, sprite->xPos);
    EXPECT_EQ (2, sprite->yPos);
    EXPECT_EQ ('O', sprite->sprite);

    ColliderComponent* collider = manager.getColliders()->get(entity);
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
}

TEST (EntityManager, createTilePrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise(&engine);

    Entity* entity = manager.createTilePrefab (1, 2);
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("Tile", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("Tile"));

    SpriteComponent* sprite = manager.getSprites()->get (entity);
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ (1, sprite->xPos);
    EXPECT_EQ (2, sprite->yPos);
    EXPECT_EQ ('.', sprite->sprite);
    EXPECT_EQ (entity, manager.getEntity (0));

    ColliderComponent* collider = manager.getColliders()->get(entity);
    EXPECT_EQ (static_cast<ColliderComponent*>(0), collider);
}
