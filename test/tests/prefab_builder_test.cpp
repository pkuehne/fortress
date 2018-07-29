#include "../../src/core/location.h"
#include "../../src/core/prefab_builder.h"
#include "../mocks/component_manager_mock.h"
#include "../mocks/entity_manager_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class PrefabBuilder_addPrefab : public ::testing::Test {};

TEST_F(PrefabBuilder_addPrefab, addsPrefabToList) {
    // Given
    YAML::Node node;
    std::string name("Foo");
    PrefabBuilder builder(nullptr, nullptr);

    // When
    builder.addPrefab(name, node);

    // Then
    EXPECT_EQ(1, builder.countPrefabs());
}

TEST_F(PrefabBuilder_addPrefab, addingTheSamePrefabTwiceHasNoEffect) {
    // Given
    YAML::Node node;
    std::string name("Foo");
    PrefabBuilder builder(nullptr, nullptr);

    // When
    builder.addPrefab(name, node);
    builder.addPrefab(name, node);

    // Then
    EXPECT_EQ(1, builder.countPrefabs());
}

class PrefabBuilder_create : public ::testing::Test {
public:
    PrefabBuilder_create()
        : entities(), components(), builder(&entities, &components), node() {}

protected:
    EntityManagerMock entities;
    ComponentManagerMock components;
    PrefabBuilder builder;
    Location location;
    YAML::Node node;
};

TEST_F(PrefabBuilder_create, ReturnsZeroIfRequestedNameIsEmpty) {
    // Given
    std::string name("");
    PrefabBuilder builder(nullptr, nullptr);
    Location location;

    // When
    EntityId id = builder.create(name, location);

    // Then
    EXPECT_EQ(0, id);
}

TEST_F(PrefabBuilder_create, ReturnsZeroIfPrefabNotFound) {
    // Given
    std::string name("Foo");

    // When
    EntityId id = builder.create(name, location);

    // Then
    EXPECT_EQ(0, id);
}

TEST_F(PrefabBuilder_create, DISABLED_CreatesADescriptionComponent) {
    // Given
    std::string name("Foo");
    node["name"] = "bar"; // Make this a map
    builder.addPrefab(name, node);
    EntityId newId = 1234;
    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));

    // When
    EntityId id = builder.create(name, location);

    // Then
    EXPECT_EQ(newId, id);
}