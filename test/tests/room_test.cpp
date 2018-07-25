#include "../../src/generators/dungeon_generator.h"
#include <gtest/gtest.h>

using namespace ::testing;

class RoomConstruction : public ::testing::Test {};

TEST_F(RoomConstruction, defaultSetsValues) {
    // Given
    Room room;

    // Then
    EXPECT_EQ(0, room.getX());
    EXPECT_EQ(0, room.getY());
    EXPECT_EQ(0, room.getWidth());
    EXPECT_EQ(0, room.getHeight());
}

TEST_F(RoomConstruction, initializeWithValues) {
    // Given
    Room room(1, 2, 10, 20);

    // Then
    EXPECT_EQ(1, room.getX());
    EXPECT_EQ(2, room.getY());
    EXPECT_EQ(10, room.getWidth());
    EXPECT_EQ(20, room.getHeight());
}

class RoomMidCalculations : public ::testing::Test {};

TEST_F(RoomMidCalculations, midsAreZeroForDefaultConstruction) {
    // Given
    Room room;

    // When
    unsigned int midX = room.getMidX();
    unsigned int midY = room.getMidY();

    // Then
    EXPECT_EQ(0, midX);
    EXPECT_EQ(0, midY);
}

TEST_F(RoomMidCalculations, midXIsXPlusHalfWidth) {
    // Given
    Room room(20, 0, 10, 0);

    // Then
    EXPECT_EQ(25, room.getMidX());
}

TEST_F(RoomMidCalculations, midYIsYPlusHalfHeight) {
    // Given
    Room room(0, 20, 0, 10);

    // Then
    EXPECT_EQ(25, room.getMidY());
}