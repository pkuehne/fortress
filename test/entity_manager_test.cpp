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
    EXPECT_EQ (entity, manager.getEntity (entity->getId()));

    manager.destroy();
}


TEST (EntityManager, destroyEntity)
{
    EntityManager   manager;
    GameEngineMock  engine;
    Entity*         entity1 = 0;
    Entity*         entity2 = 0;
    EXPECT_CALL (engine, raiseEvent(_)).Times(3);

    manager.initialise(&engine);

    entity1 = manager.createEntity("test");
    entity2 = manager.createEntity("test2");

    ASSERT_EQ (entity1, manager.getEntity (entity1->getId()));
    ASSERT_EQ (entity2, manager.getEntity (entity2->getId()));

    manager.destroyEntity (entity1->getId());
    ASSERT_NE (entity1, manager.getEntity (entity1->getId()));
    ASSERT_EQ (entity2, manager.getEntity (entity2->getId()));

    manager.destroy();
}

TEST (EntityManager, getEntityEmpty)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(0);

    manager.initialise(&engine);

    EXPECT_EQ (static_cast<Entity*>(0), manager.getEntity (0));
    EXPECT_EQ (static_cast<Entity*>(0), manager.getPlayer());
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
    EXPECT_EQ (entity, manager.getEntity (0));

    SpriteComponent* sprite = manager.getSprites()->get (entity->getId());
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ (1, sprite->xPos);
    EXPECT_EQ (2, sprite->yPos);
    EXPECT_EQ ('W', sprite->sprite);

    ColliderComponent* collider = manager.getColliders()->get(entity->getId());
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
    EXPECT_TRUE (entity->hasTag (WALL));
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
    EXPECT_EQ (entity, manager.getEntity (0));

    SpriteComponent* sprite = manager.getSprites()->get (entity->getId());
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ (1, sprite->xPos);
    EXPECT_EQ (2, sprite->yPos);
    EXPECT_EQ ('@', sprite->sprite);

    ColliderComponent* collider = manager.getColliders()->get(entity->getId());
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
    EXPECT_TRUE (entity->hasTag (PLAYER));
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
    EXPECT_EQ (entity, manager.getEntity (0));

    SpriteComponent* sprite = manager.getSprites()->get (entity->getId());
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ (1, sprite->xPos);
    EXPECT_EQ (2, sprite->yPos);
    EXPECT_EQ ('O', sprite->sprite);

    ColliderComponent* collider = manager.getColliders()->get(entity->getId());
    EXPECT_NE (static_cast<ColliderComponent*>(0), collider);
    EXPECT_TRUE (entity->hasTag (MONSTER));
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

    SpriteComponent* sprite = manager.getSprites()->get (entity->getId());
    EXPECT_NE (static_cast<SpriteComponent*>(0), sprite);
    EXPECT_EQ (1, sprite->xPos);
    EXPECT_EQ (2, sprite->yPos);
    EXPECT_EQ ('.', sprite->sprite);
    EXPECT_EQ (entity, manager.getEntity (0));

    ColliderComponent* collider = manager.getColliders()->get(entity->getId());
    EXPECT_EQ (static_cast<ColliderComponent*>(0), collider);
}

TEST (EntityManager, getPlayer)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(2);

    manager.initialise(&engine);
    EXPECT_EQ (static_cast<Entity*>(0), manager.getPlayer());

    Entity* tile = manager.createTilePrefab (1, 2);
    EXPECT_EQ (static_cast<Entity*>(0), manager.getPlayer());

    Entity* player = manager.createPlayerPrefab (1, 2);
    EXPECT_EQ (player, manager.getPlayer());
    EXPECT_NE (tile, manager.getPlayer());

}
