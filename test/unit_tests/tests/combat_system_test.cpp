#include "../../src/systems/combat_system.h"
#include "../mocks/game_engine_mock.h"
#include "../mocks/game_state_mock.h"
#include "../mocks/window_manager_mock.h"
#include "player_component.h"
#include <gtest/gtest.h>

using namespace ::testing;

class CombatSystemTest : public ::testing::Test {
public:
    CombatSystemTest() {
        comp = componentManager->make<PlayerComponent>(player);
    }

    void SetUp() {
        system.initialise(eventManager, componentManager, entityManager,
                          mapManager);
    }
    WindowManagerMock windowManager;
    std::shared_ptr<EventManager> eventManager = std::make_shared<EventManager>();
    std::shared_ptr<ComponentManager> componentManager = std::make_shared<ComponentManager>();
    std::shared_ptr<EntityManager> entityManager = std::make_shared<EntityManager>();
    std::shared_ptr<MapManager> mapManager = std::make_shared<MapManager>();
    CombatSystem system;
    EntityId player = 1234;
    PlayerComponent* comp = nullptr;
};

TEST_F(CombatSystemTest, killEntity_doesNotCreateACorpseForPlayer) {
    // Given

    // When
    system.killEntity(player);

    // Then
    EXPECT_EQ(eventManager->getEventQueueSize(), 1);
}

TEST_F(CombatSystemTest, killEntity_createsACorpseForNonPlayer) {
    GTEST_SKIP();
    // Given

    // When
    system.killEntity(2222);

    // Then
    EXPECT_EQ(eventManager->getEventQueueSize(), 2);
}