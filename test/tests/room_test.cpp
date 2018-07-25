#include "../../src/generators/room.h"
#include <gtest/gtest.h>

using namespace ::testing;

class Room_Construction : public ::testing::Test {};

TEST_F(Room_Construction, defaultSetsValues) {
    // Given
    Room room;

    // Then
    EXPECT_EQ(0, room.getX());
    EXPECT_EQ(0, room.getY());
    EXPECT_EQ(0, room.getWidth());
    EXPECT_EQ(0, room.getHeight());
}

TEST_F(Room_Construction, initializeWithValues) {
    // Given
    Room room(1, 2, 10, 20);

    // Then
    EXPECT_EQ(1, room.getX());
    EXPECT_EQ(2, room.getY());
    EXPECT_EQ(10, room.getWidth());
    EXPECT_EQ(20, room.getHeight());
}

class Room_MidCalculations : public ::testing::Test {};

TEST_F(Room_MidCalculations, midsAreZeroForDefaultConstruction) {
    // Given
    Room room;

    // When
    unsigned int midX = room.getMidX();
    unsigned int midY = room.getMidY();

    // Then
    EXPECT_EQ(0, midX);
    EXPECT_EQ(0, midY);
}

TEST_F(Room_MidCalculations, midXIsXPlusHalfWidth) {
    // Given
    Room room(20, 0, 10, 0);

    // Then
    EXPECT_EQ(25, room.getMidX());
}

TEST_F(Room_MidCalculations, midYIsYPlusHalfHeight) {
    // Given
    Room room(0, 20, 0, 10);

    // Then
    EXPECT_EQ(25, room.getMidY());
}

class Room_LeftRightTopBottom : public ::testing::Test {};

TEST_F(Room_LeftRightTopBottom, areAllZeroForDefaultConstruction) {
    // Given
    Room room;

    // Then
    EXPECT_EQ(0, room.getLeft());
    EXPECT_EQ(0, room.getRight());
    EXPECT_EQ(0, room.getTop());
    EXPECT_EQ(0, room.getBottom());
}

// 012345
// 1WWW
// 2W W
// 3WWW

TEST_F(Room_LeftRightTopBottom, RightIsXPlusWidth) {
    // Given
    Room room(1, 0, 3, 0);

    // Then
    EXPECT_EQ(3, room.getRight());
}

TEST_F(Room_LeftRightTopBottom, BottomIsYPlusWidth) {
    // Given
    Room room(0, 1, 0, 3);

    // Then
    EXPECT_EQ(3, room.getBottom());
}

TEST_F(Room_LeftRightTopBottom, LeftAndTopAreAliases) {
    // Given
    Room room(10, 30, 0, 0);

    // Then
    EXPECT_EQ(room.getX(), room.getLeft());
    EXPECT_EQ(room.getY(), room.getTop());
}

class Room_InnerWidthHeight : public ::testing::Test {};

TEST_F(Room_InnerWidthHeight, isZeroForDefaultConstructedRoom) {
    // Given
    Room room;

    // Then
    EXPECT_EQ(0, room.getInnerWidth());
    EXPECT_EQ(0, room.getInnerHeight());
}

TEST_F(Room_InnerWidthHeight, isZeroFor1x1Room) {
    // Given
    Room room(0, 0, 1, 1);

    // Then
    EXPECT_EQ(0, room.getInnerWidth());
    EXPECT_EQ(0, room.getInnerHeight());
}

TEST_F(Room_InnerWidthHeight, isZeroFor2x2Room) {
    // Given
    Room room(0, 0, 2, 2);

    // Then
    EXPECT_EQ(0, room.getInnerWidth());
    EXPECT_EQ(0, room.getInnerHeight());
}

TEST_F(Room_InnerWidthHeight, isOneFor3x3Room) {
    // Given
    Room room(0, 0, 3, 3);

    // Then
    EXPECT_EQ(1, room.getInnerWidth());
    EXPECT_EQ(1, room.getInnerHeight());
}

TEST_F(Room_InnerWidthHeight, worksForRectangularRooms) {
    // Given
    Room room(0, 0, 3, 5);

    // Then
    EXPECT_EQ(1, room.getInnerWidth());
    EXPECT_EQ(3, room.getInnerHeight());
}

class Room_IsInRoom : public ::testing::Test {};

TEST_F(Room_IsInRoom, isTrueForPointInsideWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_TRUE(room.isInRoom(5, 5));
}

TEST_F(Room_IsInRoom, isFalseForPointOutsideWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_FALSE(room.isInRoom(50, 50));
}

TEST_F(Room_IsInRoom, isTrueForPointOnTheWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_TRUE(room.isInRoom(1, 1));
    EXPECT_TRUE(room.isInRoom(1, 5));
    EXPECT_TRUE(room.isInRoom(5, 1));
    EXPECT_TRUE(room.isInRoom(10, 10));
}

class Room_IsInterior : public ::testing::Test {};

TEST_F(Room_IsInterior, isTrueForPointInsideWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_TRUE(room.isInterior(5, 5));
}

TEST_F(Room_IsInterior, isFalseForPointOutsideWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_FALSE(room.isInterior(50, 50));
}

TEST_F(Room_IsInterior, isFalseForPointOnTheWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_FALSE(room.isInterior(1, 1));
    EXPECT_FALSE(room.isInterior(1, 5));
    EXPECT_FALSE(room.isInterior(5, 1));
    EXPECT_FALSE(room.isInterior(10, 10));
}

class Room_IsWall : public ::testing::Test {};

TEST_F(Room_IsWall, isFalseForPointInsideWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_FALSE(room.isWall(5, 5));
}

TEST_F(Room_IsWall, isTrueForPointOnTheWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_TRUE(room.isWall(1, 1));
    EXPECT_TRUE(room.isWall(1, 5));
    EXPECT_TRUE(room.isWall(5, 1));
    EXPECT_TRUE(room.isWall(10, 10));
}

TEST_F(Room_IsWall, isFalseForPointOutsideWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_FALSE(room.isWall(50, 50));
}

class Room_IsCorner : public ::testing::Test {};

TEST_F(Room_IsCorner, isTrueForTheCorners) {
    // Given
    Room room(1, 1, 5, 5);

    // Then
    EXPECT_TRUE(room.isCorner(1, 1));
    EXPECT_TRUE(room.isCorner(1, 5));
    EXPECT_TRUE(room.isCorner(5, 1));
    EXPECT_TRUE(room.isCorner(5, 5));
}

TEST_F(Room_IsCorner, isFalseForPointOutsideWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_FALSE(room.isCorner(50, 50));
}

TEST_F(Room_IsCorner, isFalseForPointOnTheWallsThatAreNotCorners) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_FALSE(room.isCorner(1, 5));
    EXPECT_FALSE(room.isCorner(5, 1));
}

TEST_F(Room_IsCorner, isFalseForPointInsideWalls) {
    // Given
    Room room(1, 1, 10, 10);

    // Then
    EXPECT_FALSE(room.isCorner(5, 5));
}

class Room_Intersect : public ::testing::Test {};

// AAAAAAA
// A BBB A
// A B B A
// A BBB A
// AAAAAAA
TEST_F(Room_Intersect, CompleteOverlap) {
    // Given
    Room A(5, 5, 5, 5);
    Room B(1, 1, 30, 30);

    // Then
    EXPECT_TRUE(A.intersect(B));
    EXPECT_TRUE(B.intersect(A));
}

//   AAAAA
// BBABB A
// B A B A
// BBABB A
//   AAAAA
TEST_F(Room_Intersect, RightMiddleOverlap) {
    // Given
    Room A(5, 5, 5, 5);
    Room B(7, 7, 10, 10);

    // Then
    EXPECT_TRUE(A.intersect(B));
    EXPECT_TRUE(B.intersect(A));
}

// AAAAA
// A BBABB
// A B A B
// A BBABB
// AAAAAA
TEST_F(Room_Intersect, LeftMiddleOverlap) {
    // Given
    Room A(5, 5, 5, 5);
    Room B(1, 1, 5, 5);

    // Then
    EXPECT_TRUE(A.intersect(B));
    EXPECT_TRUE(B.intersect(A));
}

// AAAAAAAAA
// A BBBBB A
// A B   B A
// AAAAAAAAA
//   B   B
//   BBBBB
TEST_F(Room_Intersect, TopMiddleOverlap) {
    // Given
    Room A(5, 5, 5, 5);
    Room B(1, 1, 7, 7);

    // Then
    EXPECT_TRUE(A.intersect(B));
    EXPECT_TRUE(B.intersect(A));
}

//   BBBBB
//   B   B
// AAAAAAAAA
// A B   B A
// A BBBBB A
// AAAAAAAAA
TEST_F(Room_Intersect, BottomMiddleOverlap) {
    // Given
    Room A(5, 5, 5, 5);
    Room B(1, 3, 7, 7);

    // Then
    EXPECT_TRUE(A.intersect(B));
    EXPECT_TRUE(B.intersect(A));
}

// BBB
// B B
// BBAAA
//   A A
//   AAA
TEST_F(Room_Intersect, CornerOverlap) {
    // Given
    Room A(1, 1, 5, 5);
    Room B(5, 5, 5, 5);

    // Then
    EXPECT_TRUE(A.intersect(B));
    EXPECT_TRUE(B.intersect(A));
}

// BBB
// B B
// BBB AAA
//     A A
//     AAA
TEST_F(Room_Intersect, NoOverlap) {
    // Given
    Room A(1, 1, 5, 5);
    Room B(10, 10, 5, 5);

    // Then
    EXPECT_FALSE(A.intersect(B));
    EXPECT_FALSE(B.intersect(A));
}

class Room_WalkWalls : public ::testing::Test {};

// WWW
// W W
// WWW
// = 8 Walls
TEST_F(Room_WalkWalls, walksAllWalls) {
    // Given
    Room room(1, 1, 3, 3);
    unsigned int walls = 0;
    unsigned int corners = 0;

    // When
    room.walkWalls([&](unsigned int x, unsigned int y) {
        EXPECT_TRUE(room.isWall(x, y));
        if (room.isCorner(x, y)) {
            corners++;
        }
        walls++;
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    });

    // Then
    EXPECT_EQ(8, walls);
    EXPECT_EQ(4, corners);
}