#include <generator.h>
#include <gtest/gtest.h>
#include <game_engine_mock.h>
#include <entity_manager_mock.h>

using namespace ::testing;

TEST (Generator, SingleRoom)
{
    Generator l_generator;
    l_generator.mapHeight() = 50;
    l_generator.mapWidth() = 50;
    l_generator.numberOfRooms() = 1;

    GameEngineMock      l_engine;
    EntityManagerMock   l_entities;
    l_generator.initialise (&l_engine);

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    EXPECT_CALL (l_entities, createWallPrefab(_,_)).Times (AtLeast(1));
    EXPECT_CALL (l_entities, createTilePrefab(_,_)).Times (AtLeast(1));
    EXPECT_CALL (l_entities, createPlayerPrefab(_,_)).Times (1);
    EXPECT_CALL (l_entities, createEnemyPrefab(_,_)).Times (2);

    l_generator.generate();
}
