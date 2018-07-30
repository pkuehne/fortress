#include "../../src/components/collider_component.h"
#include "../../src/components/description_component.h"
#include "../../src/components/grouping_component.h"
#include "../../src/core/location.h"
#include "../../src/core/prefab_builder.h"
#include "../mocks/component_manager_mock.h"
#include "../mocks/entity_manager_mock.h"
#include "../mocks/grouping_manager_mock.h"
#include "../mocks/world_info_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

class PrefabBuilder_addPrefab : public ::testing::Test {
public:
    PrefabBuilder_addPrefab()
        : world(std::make_shared<WorldInfoMock>()),
          builder(nullptr, nullptr, world) {}

protected:
    std::shared_ptr<WorldInfoMock> world;
    PrefabBuilder builder;
};

TEST_F(PrefabBuilder_addPrefab, addsPrefabToList) {
    // Given
    YAML::Node node;
    std::string name("Foo");

    // When
    builder.addPrefab(name, node);

    // Then
    EXPECT_EQ(1, builder.countPrefabs());
}

TEST_F(PrefabBuilder_addPrefab, addingTheSamePrefabTwiceHasNoEffect) {
    // Given
    YAML::Node node;
    std::string name("Foo");

    // When
    builder.addPrefab(name, node);
    builder.addPrefab(name, node);

    // Then
    EXPECT_EQ(1, builder.countPrefabs());
}

class PrefabBuilder_create : public ::testing::Test {
public:
    PrefabBuilder_create()
        : world(std::make_shared<WorldInfoMock>()), entities(), components(),
          builder(&entities, &components, world), node() {
        node["collidable"] = false;
    }

protected:
    std::shared_ptr<WorldInfoMock> world;
    EntityManagerMock entities;
    ComponentManagerMock components;
    PrefabBuilder builder;
    Location location;
    YAML::Node node;
};

TEST_F(PrefabBuilder_create, ReturnsZeroIfRequestedNameIsEmpty) {
    // Given
    std::string name("");
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

TEST_F(PrefabBuilder_create, retunsANewlyCreatedEntity) {
    // Given
    std::string name("Foo");
    node = YAML::Load("{name: Foo, description: Bar}");
    builder.addPrefab(name, node);
    EntityId newId = 1234;
    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));

    // When
    EntityId id = builder.create(name, location);

    // Then
    EXPECT_EQ(newId, id);
}

TEST_F(PrefabBuilder_create, CreatesDescriptionComponent) {
    // Given
    std::string name("Foo");
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesCollidableComponentByDefault) {
    // Given
    std::string name("Foo");
    node.reset();
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<ColliderComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, addsEntityToAllSpecifiedGroups) {
    // Given
    std::string name("Foo");
    builder.addPrefab(name, node);
    EntityId newId = 1234;
    // ComponentBase* ptr = nullptr;
    GroupingManagerMock groupings;

    std::string group1("Group1");
    std::string group2("Group2");
    node["groupings"].push_back(group1);
    node["groupings"].push_back(group2);

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<GroupingComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    EXPECT_CALL(*world, getGroupings()).WillRepeatedly(ReturnRef(groupings));

    EXPECT_CALL(groupings, addEntityToGrouping(Eq(newId), Eq(group1)));
    EXPECT_CALL(groupings, addEntityToGrouping(Eq(newId), Eq(group2)));

    // When
    builder.create(name, location);
}
