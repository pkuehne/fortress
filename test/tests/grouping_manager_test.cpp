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

class GroupingManager_AddEntityToGrouping : public ::testing::Test {};

TEST_F(GroupingManager_AddEntityToGrouping, throwsIfGroupingNameNotValid) {
    // Given
    GroupingManager manager;
    std::string name("Foo");
    manager.createNewGrouping(name);

    // When
    EXPECT_THROW(manager.addEntityToGrouping(123, "Bar"), std::string);
}

TEST_F(GroupingManager_AddEntityToGrouping, addsMemberToGrouping) {
    // Given
    GroupingManager manager;
    std::string name("Foo");
    manager.createNewGrouping(name);
    EntityId id = 1234;

    // When
    ASSERT_NO_THROW(manager.addEntityToGrouping(id, name));

    // Then
    EXPECT_EQ(1, manager.getGrouping(name).getMembers().size());
    EXPECT_TRUE(manager.getGrouping(name).hasMember(id));
}

TEST_F(GroupingManager_AddEntityToGrouping,
       addsMemberToParentGroupingThrowsIfParentIsInvalid) {
    // Given
    GroupingManager manager;
    std::string name("Foo");
    std::string parent("Bar");
    manager.createNewGrouping(name);
    manager.getGrouping(name).setParentGrouping(parent);
    EntityId id = 1234;

    // When
    ASSERT_THROW(manager.addEntityToGrouping(id, name), std::string);
}

TEST_F(GroupingManager_AddEntityToGrouping, addsMemberToParentGroupingAsWell) {
    // Given
    GroupingManager manager;
    std::string name("Foo");
    std::string parent("Bar");
    manager.createNewGrouping(name);
    manager.createNewGrouping(parent);
    manager.getGrouping(name).setParentGrouping(parent);
    EntityId id = 1234;

    // When
    ASSERT_NO_THROW(manager.addEntityToGrouping(id, name));

    // Then
    EXPECT_TRUE(manager.getGrouping(name).hasMember(id));
    EXPECT_TRUE(manager.getGrouping(parent).hasMember(id));
}

class GroupingManager_RemoveEntityFromAllGroupings : public ::testing::Test {};

TEST_F(GroupingManager_RemoveEntityFromAllGroupings, removesEntityFromAll) {
    // Given
    GroupingManager manager;
    EntityId id = 1234;

    std::string one("Foo");
    std::string two("Bar");
    manager.createNewGrouping(one).addMember(id);
    manager.createNewGrouping(two).addMember(id);

    // When
    manager.removeEntityFromAllGroupings(id);

    // Then
    EXPECT_FALSE(manager.getGrouping(one).hasMember(id));
    EXPECT_FALSE(manager.getGrouping(two).hasMember(id));
}