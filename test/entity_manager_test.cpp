#include <gtest/gtest.h>
#include <entity_manager.h>
#include <game_engine_mock.h>

using namespace ::testing;

TEST (EntityManager, createEntity)
{
    EntityManager   manager;
    GameEngineMock  engine;
    //EXPECT_CALL (engine, raiseEvent(WhenDynamicCastTo<AddEntityEvent*>(Not(IsNull()))));
    EXPECT_CALL (engine, raiseEvent(_));

    manager.initialise();
    manager.setGameEngineRef (&engine);

    Entity* entity = manager.createEntity("test");
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("test", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("test"));
    EXPECT_EQ (entity, manager.getEntity (0));
}

TEST (EntityManager, getEntityEmpty)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(0);

    manager.initialise();
    manager.setGameEngineRef (&engine);

    EXPECT_EQ (static_cast<Entity*>(0), manager.getEntity ("test"));
    EXPECT_EQ (static_cast<Entity*>(0), manager.getEntity (0));
}

TEST (EntityManager, createWallPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise();
    manager.setGameEngineRef (&engine);

    Entity* entity = manager.createWallPrefab (0, 0);
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("Wall", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("Wall"));
    EXPECT_EQ (entity, manager.getEntity (0));
}

TEST (EntityManager, createPlayerPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise();
    manager.setGameEngineRef (&engine);

    Entity* entity = manager.createPlayerPrefab (0, 0);
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("Player", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("Player"));
    EXPECT_EQ (entity, manager.getEntity (0));
}

TEST (EntityManager, createEnemyPrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise();
    manager.setGameEngineRef (&engine);

    Entity* entity = manager.createEnemyPrefab (0, 0);
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("Enemy", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("Enemy"));
    EXPECT_EQ (entity, manager.getEntity (0));
}

TEST (EntityManager, createTilePrefab)
{
    EntityManager   manager;
    GameEngineMock  engine;
    EXPECT_CALL (engine, raiseEvent(_)).Times(1);

    manager.initialise();
    manager.setGameEngineRef (&engine);

    Entity* entity = manager.createTilePrefab (0, 0);
    EXPECT_NE (static_cast<Entity*>(0), entity);
    EXPECT_EQ (0, entity->getId());
    EXPECT_EQ ("Tile", entity->getName());
    EXPECT_EQ (entity, manager.getEntity ("Tile"));
    EXPECT_EQ (entity, manager.getEntity (0));
}
