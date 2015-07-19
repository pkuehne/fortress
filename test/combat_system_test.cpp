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

    Entity* l_entityPlayer = l_entities.createEntity ("Player");
    l_entityPlayer->addTag(PLAYER);
    SpriteComponent l_spritePlayer;
    l_spritePlayer.xPos  = 2;
    l_spritePlayer.yPos  = 2;
    l_spritePlayer.sprite= 181;

    Entity* l_entityOrc = l_entities.createEntity ("Orc");
    l_entityOrc->addTag (MONSTER);
    SpriteComponent l_spriteOrc;
    l_spriteOrc.xPos  = 2;
    l_spriteOrc.yPos  = 3;
    l_spriteOrc.sprite= 181;

    Entity* l_entityOrc2 = l_entities.createEntity ("Orc");
    l_entityOrc2->addTag (MONSTER);
    SpriteComponent l_spriteOrc2;
    l_spriteOrc2.xPos  = 4;
    l_spriteOrc2.yPos  = 4;
    l_spriteOrc2.sprite= 181;

    l_entities.getSprites()->add (l_entityPlayer,  l_spritePlayer);
    l_entities.getSprites()->add (l_entityOrc,     l_spriteOrc);
    l_entities.getSprites()->add (l_entityOrc2,    l_spriteOrc2);

    l_entities.initialise (&l_engine);

    EXPECT_NE (static_cast<Entity*>(0), l_entities.getEntity (l_entityOrc->getId()));
    EXPECT_NE (static_cast<Entity*>(0), l_entities.getEntity (l_entityOrc2->getId()));

    EXPECT_CALL (l_engine, getEntities()).WillRepeatedly (Return (&l_entities));
    l_system.initialise (&l_engine);

    EXPECT_CALL (l_engine, raiseEvent(_)).Times(1).WillOnce (SaveArg<0>(&l_removeEvent));
    l_system.handleEvent (&l_attackEvent);
    ASSERT_NE (static_cast<Event*> (0), l_removeEvent);
    ASSERT_EQ (EVENT_REMOVE_ENTITY, l_removeEvent->getType());
    EXPECT_EQ (l_entityOrc, dynamic_cast<RemoveEntityEvent*>(l_removeEvent)->entity);

    EXPECT_EQ (static_cast<Entity*>(0), l_entities.getEntity (l_entityOrc->getId()));
    EXPECT_NE (static_cast<Entity*>(0), l_entities.getEntity (l_entityOrc2->getId()));
}
