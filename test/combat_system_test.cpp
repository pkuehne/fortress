#include <combat_system.h>
#include <gtest/gtest.h>
#include <entity_manager.h>
#include "game_engine_mock.h"

using namespace ::testing;

TEST (CombatSystem, handleAttackEvent)
{
    CombatSystem        l_system;
    GameEngineMock      l_engine;
    AttackEntityEvent   l_attackEvent;
    Event*              l_removeEvent = 0;
    EntityManager       l_entities;

    EXPECT_CALL (l_engine, raiseEvent(NotNull())).Times (3);
    l_entities.initialise (&l_engine);

    Entity* l_entityPlayer = l_entities.createPlayerPrefab (2, 2);
    Entity* l_entityOrc = l_entities.createEnemyPrefab (2, 1);
    Entity* l_entityOrc2 = l_entities.createEnemyPrefab (4, 4);

    EXPECT_EQ (3, l_entities.getSprites()->getAll().size());

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    EXPECT_CALL (l_engine, raiseEvent(_)).Times(1).WillOnce (SaveArg<0>(&l_removeEvent));

    l_system.initialise (&l_engine);
    l_system.handleEvent (&l_attackEvent);

    ASSERT_NE (static_cast<Event*> (0), l_removeEvent);
    ASSERT_EQ (EVENT_REMOVE_ENTITY, l_removeEvent->getType());
    EXPECT_EQ (l_entityOrc->getId(), dynamic_cast<RemoveEntityEvent*>(l_removeEvent)->entity);

    EXPECT_EQ (static_cast<Entity*>(0), l_entities.getEntity (l_entityOrc->getId()));
    EXPECT_NE (static_cast<Entity*>(0), l_entities.getEntity (l_entityOrc2->getId()));
}
