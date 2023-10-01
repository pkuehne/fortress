#include "../../src/systems/combat_system.h"
#include "../components/npc_component.h"
#include "../components/sprite_component.h"
#include "../mocks/game_engine_mock.h"
#include "../mocks/window_manager_mock.h"
#include "player_component.h"
#include <gtest/gtest.h>

using namespace ::testing;

class EventManagerProxy : public EventManager {
public:
    std::queue<std::pair<size_t, std::unique_ptr<Event>>>& getEventQueue() {
        return m_eventList;
    }
};

class CombatSystemTest : public ::testing::Test {
public:
    CombatSystemTest() {
        entityManager->initialise(eventManager);

        componentManager->make<PlayerComponent>(player);
        componentManager->make<NpcComponent>(npc);
        componentManager->make<SpriteComponent>(npc);
    }

    void SetUp() { system.initialise(eventManager, entityManager, mapManager); }
    WindowManagerMock windowManager;
    std::shared_ptr<EventManagerProxy> eventManager =
        std::make_shared<EventManagerProxy>();
    std::shared_ptr<ComponentManager> componentManager =
        std::make_shared<ComponentManager>();
    std::shared_ptr<EntityManager> entityManager =
        std::make_shared<EntityManager>();
    std::shared_ptr<MapManager> mapManager = std::make_shared<MapManager>();
    CombatSystem system;
    EntityId player = 1234;
    EntityId non_npc = 1111;
    EntityId npc = 2222;
};

TEST_F(CombatSystemTest, killEntity_doesNotCreateACorpseForPlayer) {
    // Given

    // When
    system.killEntity(player);

    // Then
    ASSERT_EQ(eventManager->getEventQueueSize(), 1);
    EXPECT_EQ(eventManager->getEventQueue().front().first,
              typeid(RemoveEntityEvent).hash_code());
}

TEST_F(CombatSystemTest, killEntity_doesNotCreateACorpseForNonNpc) {
    // Given

    // When
    system.killEntity(non_npc);

    // Then
    ASSERT_EQ(eventManager->getEventQueueSize(), 1);
    EXPECT_EQ(eventManager->getEventQueue().front().first,
              typeid(RemoveEntityEvent).hash_code());
}

TEST_F(CombatSystemTest, killEntity_createsACorpseForNpcs) {
    // Given

    // When
    system.killEntity(npc);

    // Then
    ASSERT_EQ(eventManager->getEventQueueSize(), 3);
    EXPECT_EQ(eventManager->getEventQueue().front().first,
              typeid(AddEntityEvent).hash_code());
    eventManager->getEventQueue().pop();
    EXPECT_EQ(eventManager->getEventQueue().front().first,
              typeid(InstantiatePrefabEvent).hash_code());
    eventManager->getEventQueue().pop();
    EXPECT_EQ(eventManager->getEventQueue().front().first,
              typeid(RemoveEntityEvent).hash_code());
}