#include "../../src/world/grouping.h"
#include <gtest/gtest.h>

using namespace ::testing;

class GroupingTest : public ::testing::Test {};

TEST_F(GroupingTest, initializedWithName) {
    // Given
    std::string name("Foo");

    // When
    Grouping grouping(name);

    // Then
    EXPECT_EQ(name, grouping.getName());
}

class GroupingTest_Relationship : public ::testing::Test {};

TEST_F(GroupingTest_Relationship, defaultsToDefaultRelationshipValue) {
    // Given
    Grouping grouping("foo");

    // When
    grouping.setDefaultRelationship(20);

    // Then
    EXPECT_EQ(20, grouping.getRelationship("bar"));
}

TEST_F(GroupingTest_Relationship, defaultRelationshipIsNotSticky) {
    // Given
    Grouping grouping("foo");

    // When
    grouping.setDefaultRelationship(20);
    grouping.getRelationship("bar");
    grouping.setDefaultRelationship(-20);

    // Then
    EXPECT_EQ(-20, grouping.getRelationship("bar"));
}

TEST_F(GroupingTest_Relationship, getsTheValueSet) {
    // Given
    Grouping grouping("foo");
    int relationship = 24;

    // When
    grouping.setRelationship("bar", relationship);

    // Then
    EXPECT_EQ(relationship, grouping.getRelationship("bar"));
}

TEST_F(GroupingTest_Relationship, clampsTo100) {
    // Given
    Grouping grouping("foo");

    // When
    grouping.setRelationship("bar", 150);

    // Then
    EXPECT_EQ(100, grouping.getRelationship("bar"));
}

TEST_F(GroupingTest_Relationship, clampsToMinus100) {
    // Given
    Grouping grouping("foo");

    // When
    grouping.setRelationship("bar", -150);

    // Then
    EXPECT_EQ(-100, grouping.getRelationship("bar"));
}

TEST_F(GroupingTest_Relationship, defaultRelationshipDefaultIsZero) {
    // Given
    Grouping grouping("foo");

    // Then
    EXPECT_EQ(0, grouping.getRelationship("bar"));
}

TEST_F(GroupingTest_Relationship, clampsDefaultRelationshipTo100) {
    // Given
    Grouping grouping("foo");

    // When
    grouping.setDefaultRelationship(150);

    // Then
    EXPECT_EQ(100, grouping.getRelationship("bar"));
}

TEST_F(GroupingTest_Relationship, clampsDefaultRelationshipToMinus100) {
    // Given
    Grouping grouping("foo");

    // When
    grouping.setDefaultRelationship(-150);

    // Then
    EXPECT_EQ(-100, grouping.getRelationship("bar"));
}

class GroupingTest_Membership : public ::testing::Test {
public:
    GroupingTest_Membership() : grouping(Grouping("foo")) {}
    void SetUp() { grouping.addMember(id); }

protected:
    EntityId id = 1234;
    Grouping grouping;
};

TEST_F(GroupingTest_Membership, addMemberIncludesItInGroup) {
    // Then
    ASSERT_EQ(1, grouping.getMembers().size());
    EXPECT_NE(grouping.getMembers().end(), grouping.getMembers().find(id));
}

TEST_F(GroupingTest_Membership, addingSameMemberAgainHasNoEffect) {
    // When
    grouping.addMember(id);

    // Then
    ASSERT_EQ(1, grouping.getMembers().size());
    EXPECT_NE(grouping.getMembers().end(), grouping.getMembers().find(id));
}

TEST_F(GroupingTest_Membership, removeMemberRemovesFromList) {
    // When
    grouping.removeMember(id);

    // Then
    ASSERT_EQ(0, grouping.getMembers().size());
    EXPECT_EQ(grouping.getMembers().end(), grouping.getMembers().find(id));
}

TEST_F(GroupingTest_Membership, removingNonExistentMemberHasNoEffect) {
    // When
    grouping.removeMember(id);
    grouping.removeMember(id);

    // Then
    ASSERT_EQ(0, grouping.getMembers().size());
    EXPECT_EQ(grouping.getMembers().end(), grouping.getMembers().find(id));
}

TEST_F(GroupingTest_Membership, hasMemberReturnsTrueForMemberInGroup) {
    // Then
    EXPECT_TRUE(grouping.hasMember(id));
}

TEST_F(GroupingTest_Membership, hasMemberReturnsFalseForMemberNotInGroup) {
    // Then
    EXPECT_FALSE(grouping.hasMember(9999));
}

class GroupingTest_OperatorLessThan : public ::testing::Test {};

TEST_F(GroupingTest_OperatorLessThan, comparesOnName) {
    // Given
    Grouping a("A");
    Grouping b("B");
    Grouping z("Z");

    // Then
    EXPECT_LT(a, b);
    EXPECT_LT(b, z);
    EXPECT_LT(a, z);
}

class GroupingTest_Parent : public ::testing::Test {};

TEST_F(GroupingTest_Parent, getSetParent) {
    // Given
    std::string parent("parent");
    Grouping grouping("Foo");

    // When
    grouping.setParentGrouping(parent);

    // Then
    EXPECT_EQ(parent, grouping.getParentGrouping());
}

TEST_F(GroupingTest_Parent, emptyParentClearsIt) {
    // Given
    std::string parent("parent");
    std::string empty("");
    Grouping grouping("Foo");

    // When
    grouping.setParentGrouping(parent);
    grouping.setParentGrouping(empty);

    // Then
    EXPECT_EQ(empty, grouping.getParentGrouping());
}