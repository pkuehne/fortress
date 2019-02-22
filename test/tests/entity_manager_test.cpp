#include "../../src/core/component_manager.h"
#include "../../src/core/entity_manager.h"
#include "../../src/core/event_manager.h"
#include "../../src/core/map_manager.h"
#include "../mocks/component_manager_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class EntityManagerFixture : public ::testing::Test {
public:
    void SetUp() {
        events = std::make_shared<EventManager>();
        components = std::make_shared<ComponentManager>();
        map = std::make_shared<MapManager>();
        manager.initialise(events, map, components);
    }

protected:
    EntityManager manager;
    std::shared_ptr<EventManager> events;
    std::shared_ptr<ComponentManager> components;
    std::shared_ptr<MapManager> map;
};

class EntityManager_createEntity : public EntityManagerFixture {
public:
    void SetUp() { EntityManagerFixture::SetUp(); }
};

TEST_F(EntityManager_createEntity, raisedAddEntityEvent) {
    // Given
    Location location;

    // When
    manager.createEntity(location);

    // Then
    EXPECT_EQ(1, events->getEventQueueSize());
}

class EntityManager_addEntity : public EntityManagerFixture {

protected:
    EntityId entity = 1234;
    Location location;
};

TEST_F(EntityManager_addEntity, addsEntityforAllList) {
    // When
    manager.addEntity(entity, location);

    // Then
    ASSERT_EQ(1, manager.all().size());
}

class EntityManager_destroyEntity : public EntityManagerFixture {
public:
    void SetUp() {
        EntityManagerFixture::SetUp();
        manager.addEntity(entity, location);
    }

protected:
    EntityId entity = 1234;
    Location location;
};

TEST_F(EntityManager_destroyEntity, addsEntityforAllList) {
    // Given

    // When
    manager.destroyEntity(entity);

    // Then
    ASSERT_EQ(0, manager.all().size());
}

TEST_F(EntityManager_destroyEntity, doesnotraiseanyevents) {
    // Given
    EXPECT_EQ(1, events->getEventQueueSize());

    // When
    manager.destroyEntity(entity);

    // Then
    EXPECT_EQ(1, events->getEventQueueSize());
}

class EntityManager_getsetLocation : public EntityManagerFixture {};

TEST_F(EntityManager_getsetLocation, raisedAddEntityEvent) {
    // Given
    Location location;
    EntityId entity = 1234;

    // When
    manager.setLocation(entity, location);
    Location l = manager.getLocation(entity);

    // Then
    EXPECT_EQ(l, location);
}

TEST_F(EntityManager_getsetLocation, setDoesNothingForZeroEntity) {
    // Given
    Location location(1, 2, 3);
    EntityId entity = 0;

    // When
    manager.setLocation(entity, location);
    Location l = manager.getLocation(entity);

    // Then
    EXPECT_NE(l, location);
}
