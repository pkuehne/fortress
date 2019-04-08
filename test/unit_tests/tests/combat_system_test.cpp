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
        eventManager = std::make_shared<EventManager>();
        componentManager = std::make_shared<ComponentManager>();
        entityManager = std::make_shared<EntityManager>();
        mapManager = std::make_shared<MapManager>();

        comp = componentManager->make<PlayerComponent>(player);
    }

    void SetUp() {
        system.initialise(eventManager, componentManager, entityManager,
                          mapManager);
    }
    WindowManagerMock windowManager;
    std::shared_ptr<EventManager> eventManager = nullptr;
    std::shared_ptr<ComponentManager> componentManager = nullptr;
    std::shared_ptr<EntityManager> entityManager = nullptr;
    std::shared_ptr<MapManager> mapManager = nullptr;
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