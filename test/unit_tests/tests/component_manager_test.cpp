#include "component_base.h"
#include "component_manager.h"
#include <gtest/gtest.h>

using namespace ::testing;
struct TestComponent : public ComponentBase {
    int indicator = 0;
};

struct Test2Component : public ComponentBase {
    //
};

class ComponentManagerTest : public ::testing::Test {
public:
    ComponentManager manager;
    EntityId entity = 1234;
};

TEST_F(ComponentManagerTest, makeCreatesNewComponent) {
    // Given
    manager.make<TestComponent>(entity);

    // When
    auto test = manager.get<TestComponent>(entity);
    auto test2 = manager.get<Test2Component>(entity);

    // Then
    EXPECT_NE(nullptr, test);
    EXPECT_EQ(nullptr, test2);
}

TEST_F(ComponentManagerTest, makeDoesNotAddSameComponentTwice) {
    // Given
    manager.make<TestComponent>(entity);
    manager.get<TestComponent>(entity)->indicator = 1;

    // When
    manager.make<TestComponent>(entity);

    // Then
    auto test = manager.get<TestComponent>(entity);
    EXPECT_EQ(1, test->indicator);
}

TEST_F(ComponentManagerTest, makeReturnsTheOriginalComponentWhenAddingTwice) {
    // Given
    auto component = manager.make<TestComponent>(entity);
    manager.get<TestComponent>(entity)->indicator = 1;

    // When
    auto component2 = manager.make<TestComponent>(entity);

    // Then
    EXPECT_EQ(component, component2);
}

TEST_F(ComponentManagerTest, getReturnsNullptrIfNotFound) {
    // Given

    // When
    auto test = manager.get<TestComponent>(entity);

    // Then
    EXPECT_EQ(nullptr, test);
}

TEST_F(ComponentManagerTest, returnedComponentsAreDistinct) {
    // Given
    manager.make<TestComponent>(entity);
    manager.make<Test2Component>(entity);

    // When
    auto test = manager.get<TestComponent>(entity);
    auto test2 = manager.get<Test2Component>(entity);

    // Then
    EXPECT_NE(nullptr, test);
    EXPECT_NE(nullptr, test2);
    EXPECT_NE(static_cast<ComponentBase*>(test),
              static_cast<ComponentBase*>(test2));
}

TEST_F(ComponentManagerTest, getAllReturnsAllMakedComponents) {
    // Given
    manager.make<TestComponent>(entity);
    manager.make<Test2Component>(entity);

    // When
    const ComponentHolder& holder = manager.getAll(entity);

    // Then
    EXPECT_EQ(2, holder.size());
}

TEST_F(ComponentManagerTest, removeOnlyRemovesSpecificComponent) {
    // Given
    manager.make<TestComponent>(entity);
    manager.make<Test2Component>(entity);

    // When
    manager.remove<Test2Component>(entity);

    // Then
    auto test = manager.get<TestComponent>(entity);
    auto test2 = manager.get<Test2Component>(entity);
    const ComponentHolder& holder = manager.getAll(entity);

    EXPECT_NE(nullptr, test);
    EXPECT_EQ(nullptr, test2);
    EXPECT_EQ(1, holder.size());
}

TEST_F(ComponentManagerTest, removesNothingIfNotFound) {
    // Given
    manager.make<TestComponent>(entity);

    // When
    manager.remove<Test2Component>(entity);

    // Then
    auto test = manager.get<TestComponent>(entity);
    auto test2 = manager.get<Test2Component>(entity);
    const ComponentHolder& holder = manager.getAll(entity);

    EXPECT_NE(nullptr, test);
    EXPECT_EQ(nullptr, test2);
    EXPECT_EQ(1, holder.size());
}

TEST_F(ComponentManagerTest, removeAllRemovesAll) {
    // Given
    manager.make<TestComponent>(entity);
    manager.make<Test2Component>(entity);

    // When
    manager.removeAll(entity);

    // Then
    auto test = manager.get<TestComponent>(entity);
    auto test2 = manager.get<Test2Component>(entity);
    const ComponentHolder& holder = manager.getAll(entity);

    EXPECT_EQ(nullptr, test);
    EXPECT_EQ(nullptr, test2);
    EXPECT_EQ(0, holder.size());
}

TEST_F(ComponentManagerTest, existsReturnsFalseIfNoComponentsAtAll) {
    // When
    bool retval = manager.exists<Test2Component>(entity);

    // Then
    EXPECT_FALSE(retval);
}

TEST_F(ComponentManagerTest, existsReturnsFalseIfNoComponentExists) {
    // Given
    manager.make<TestComponent>(entity);

    // When
    bool retval = manager.exists<Test2Component>(entity);

    // Then
    EXPECT_FALSE(retval);
}

TEST_F(ComponentManagerTest, existsReturnsTrueIfComponentExists) {
    // Given
    manager.make<TestComponent>(entity);

    // When
    bool retval = manager.exists<TestComponent>(entity);

    // Then
    EXPECT_TRUE(retval);
}

TEST_F(ComponentManagerTest, entitiesForReturnsEmptyListIfNoneExist) {
    // Given

    // When
    EntityHolder entities = manager.entitiesFor<TestComponent>();

    // Then
    EXPECT_TRUE(entities.empty());
}

TEST_F(ComponentManagerTest,
       entitiesForReturnsEmptyListIfNothingForThatComponent) {
    // Given
    manager.make<Test2Component>(entity);

    // When
    EntityHolder entities = manager.entitiesFor<TestComponent>();

    // Then
    EXPECT_TRUE(entities.empty());
}

TEST_F(ComponentManagerTest, entitiesForReturnsHolderWithEntity) {
    // Given
    manager.make<TestComponent>(entity);

    // When
    EntityHolder entities = manager.entitiesFor<TestComponent>();

    // Then
    EXPECT_EQ(1, entities.size());
    auto iter = entities.find(entity);
    EXPECT_FALSE(iter == entities.end());
}

TEST_F(ComponentManagerTest, entitiesReturnsNothingAfterRemoval) {
    // Given
    manager.make<TestComponent>(entity);
    manager.remove<TestComponent>(entity);

    // When
    EntityHolder entities = manager.entitiesFor<TestComponent>();

    // Then
    EXPECT_TRUE(entities.empty());
}

TEST_F(ComponentManagerTest, entitiesReturnsNothingAfterRemovAll) {
    // Given
    manager.make<TestComponent>(entity);
    manager.make<TestComponent>(entity);
    manager.removeAll(entity);

    // When
    EntityHolder entities1 = manager.entitiesFor<TestComponent>();
    EntityHolder entities2 = manager.entitiesFor<TestComponent>();

    // Then
    EXPECT_TRUE(entities1.empty());
    EXPECT_TRUE(entities2.empty());
}

TEST_F(ComponentManagerTest, getUniqueReturnsEmptyIfNotFound) {
    // Given
    manager.make<TestComponent>(entity);

    // When
    auto retval = manager.getUnique<Test2Component>();

    // Then
    EXPECT_EQ(0, retval.id);
    EXPECT_EQ(nullptr, retval.component);
}

TEST_F(ComponentManagerTest, getUniqueReturnsFilledStructIfFound) {
    // Given
    manager.make<TestComponent>(entity);

    // When
    auto retval = manager.getUnique<TestComponent>();

    // Then
    EXPECT_EQ(entity, retval.id);
    EXPECT_EQ(manager.get<TestComponent>(entity), retval.component);
}