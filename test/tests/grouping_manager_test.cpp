#include "../../src/world/grouping_manager.h"
#include <gtest/gtest.h>

using namespace ::testing;

class GroupingManager_createNewGrouping : public ::testing::Test {};

TEST_F(GroupingManager_createNewGrouping, throwsIfNameIsEmpty) {
    // Given
    GroupingManager manager;
    std::string empty("");

    // When
    try {
        manager.createNewGrouping(empty);
        FAIL() << "manager did not throw";
    } catch (std::string err) {
        ASSERT_FALSE(err.empty());
    }
}

TEST_F(GroupingManager_createNewGrouping, throwsIfNameAlreadyExists) {
    // Given
    GroupingManager manager;
    std::string name("Foo");
    manager.createNewGrouping(name);

    // When
    try {
        manager.createNewGrouping(name);
        FAIL() << "manager did not throw";
    } catch (std::string err) {
        ASSERT_FALSE(err.empty());
    }
}

TEST_F(GroupingManager_createNewGrouping, returnsGroupingWithSuppliedName) {
    // Given
    GroupingManager manager;
    std::string name("Foo");

    // When
    auto retval = manager.createNewGrouping(name);

    // Then
    EXPECT_EQ(name, retval.getName());
}

class GroupingManager_getGrouping : public ::testing::Test {};

TEST_F(GroupingManager_getGrouping, returnsExistingGrouping) {
    // Given
    GroupingManager manager;
    std::string name("Foo");
    manager.createNewGrouping(name);

    // When
    Grouping val = manager.getGrouping(name);
    EXPECT_EQ(name, val.getName());
}

TEST_F(GroupingManager_getGrouping, throwsIfGroupingDoesntExist) {
    // Given
    GroupingManager manager;
    std::string name("Foo");

    // When
    try {
        manager.getGrouping(name);
        FAIL() << "manager did not throw";
    } catch (std::string err) {
        ASSERT_FALSE(err.empty());
    }
}

class GroupingManager_setRelationship : public ::testing::Test {
public:
    GroupingManager_setRelationship()
        : manager(), A(manager.createNewGrouping("A")),
          B(manager.createNewGrouping("B")) {}

protected:
    GroupingManager manager;
    Grouping A;
    Grouping B;
};

TEST_F(GroupingManager_setRelationship, setsTheRelationshipOneWayByObject) {
    // Given
    int relationship = 50;

    // When
    manager.setRelationship(A, B, relationship);

    // Then
    EXPECT_EQ(relationship, manager.getGrouping("A").getRelationship("B"));
    EXPECT_NE(relationship, manager.getGrouping("B").getRelationship("A"));
}

TEST_F(GroupingManager_setRelationship, setsTheRelationshipOneWayByName) {
    // Given
    int relationship = 50;

    // When
    manager.setRelationship("A", "B", relationship);

    // Then
    EXPECT_EQ(relationship, manager.getGrouping("A").getRelationship("B"));
    EXPECT_NE(relationship, manager.getGrouping("B").getRelationship("A"));
}