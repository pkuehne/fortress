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
