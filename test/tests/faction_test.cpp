#include "../../src/core/world_info.h"
#include <gtest/gtest.h>

using namespace ::testing;

class FactionTest : public ::testing::Test {};

TEST_F(FactionTest, initializedWithName) {
    // Given
    std::string name("Foo");

    // When
    Faction faction(name);

    // Then
    EXPECT_EQ(name, faction.getName());
}

class FactionTest_Relationship : public ::testing::Test {};

TEST_F(FactionTest_Relationship, defaultsToDefaultRelationshipValue) {
    // Given
    Faction faction("foo");

    // When
    faction.setDefaultRelationship(20);

    // Then
    EXPECT_EQ(20, faction.getRelationship("bar"));
}

TEST_F(FactionTest_Relationship, defaultRelationshipIsNotSticky) {
    // Given
    Faction faction("foo");

    // When
    faction.setDefaultRelationship(20);
    faction.getRelationship("bar");
    faction.setDefaultRelationship(-20);

    // Then
    EXPECT_EQ(-20, faction.getRelationship("bar"));
}

TEST_F(FactionTest_Relationship, getsTheValueSet) {
    // Given
    Faction faction("foo");
    int relationship = 24;

    // When
    faction.setRelationship("bar", relationship);

    // Then
    EXPECT_EQ(relationship, faction.getRelationship("bar"));
}

TEST_F(FactionTest_Relationship, clampsTo100) {
    // Given
    Faction faction("foo");

    // When
    faction.setRelationship("bar", 150);

    // Then
    EXPECT_EQ(100, faction.getRelationship("bar"));
}

TEST_F(FactionTest_Relationship, clampsToMinus100) {
    // Given
    Faction faction("foo");

    // When
    faction.setRelationship("bar", -150);

    // Then
    EXPECT_EQ(-100, faction.getRelationship("bar"));
}

TEST_F(FactionTest_Relationship, defaultRelationshipDefaultIsZero) {
    // Given
    Faction faction("foo");

    // Then
    EXPECT_EQ(0, faction.getRelationship("bar"));
}

TEST_F(FactionTest_Relationship, clampsDefaultRelationshipTo100) {
    // Given
    Faction faction("foo");

    // When
    faction.setDefaultRelationship(150);

    // Then
    EXPECT_EQ(100, faction.getRelationship("bar"));
}

TEST_F(FactionTest_Relationship, clampsDefaultRelationshipToMinus100) {
    // Given
    Faction faction("foo");

    // When
    faction.setDefaultRelationship(-150);

    // Then
    EXPECT_EQ(-100, faction.getRelationship("bar"));
}
