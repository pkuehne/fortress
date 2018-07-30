#include "../../src/components/collider_component.h"
#include "../../src/components/connector_component.h"
#include "../../src/components/consumable_component.h"
#include "../../src/components/description_component.h"
#include "../../src/components/droppable_component.h"
#include "../../src/components/equipment_component.h"
#include "../../src/components/grouping_component.h"
#include "../../src/components/health_component.h"
#include "../../src/components/npc_component.h"
#include "../../src/components/openable_component.h"
#include "../../src/components/player_component.h"
#include "../../src/components/sprite_component.h"
#include "../../src/components/wearable_component.h"
#include "../../src/components/wieldable_component.h"
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
    EXPECT_CALL(components, add(Eq(newId), _)).Times(2);

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

TEST_F(PrefabBuilder_create, CreatesSpriteComponent) {
    // Given
    std::string name("Foo");
    node["symbol"] = 12;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(components, add(Eq(newId), WhenDynamicCastTo<SpriteComponent*>(
                                               Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesHealthComponent) {
    // Given
    std::string name("Foo");
    node["health"] = 12;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(components, add(Eq(newId), WhenDynamicCastTo<HealthComponent*>(
                                               Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesConsumableComponent) {
    // Given
    std::string name("Foo");
    node["consumable"]["effect"] = 123;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<ConsumableComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesDroppableComponent) {
    // Given
    std::string name("Foo");
    node["droppable"] = true;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DroppableComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesOpenableComponent) {
    // Given
    std::string name("Foo");
    node["openable"]["open"] = true;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<OpenableComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesWieldableComponent) {
    // Given
    std::string name("Foo");
    node["wieldable"]["damage"] = 0;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<WieldableComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesWearableComponent) {
    // Given
    std::string name("Foo");
    node["wearable"]["position"] = 0;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<WearableComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesEquipmentComponent) {
    // Given
    std::string name("Foo");
    node["equipment"]["maxWeight"] = 0;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<EquipmentComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesConnectorComponent) {
    // Given
    std::string name("Foo");
    node["connector"] = true;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<ConnectorComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesNpcComponent) {
    // Given
    std::string name("Foo");
    node["smart"]["fsm"] = "test";
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(components,
                add(Eq(newId), WhenDynamicCastTo<NpcComponent*>(Ne(nullptr))));
    EXPECT_CALL(
        components,
        add(Eq(newId), WhenDynamicCastTo<DescriptionComponent*>(Ne(nullptr))));

    // When
    builder.create(name, location);
}

TEST_F(PrefabBuilder_create, CreatesPlayerComponent) {
    // Given
    std::string name("Foo");
    node["player"] = true;
    builder.addPrefab(name, node);
    EntityId newId = 1234;

    EXPECT_CALL(entities, createEntity(_)).WillOnce(Return(newId));
    EXPECT_CALL(components, add(Eq(newId), WhenDynamicCastTo<PlayerComponent*>(
                                               Ne(nullptr))));
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
