#include "../../src/core/location.h"
#include <gtest/gtest.h>

using namespace ::testing;

class LocationTest : public ::testing::Test {};

TEST_F(LocationTest, emptyLocationIsDefaulted) {
    // Given
    Location location;

    // Then
    EXPECT_EQ(UINT_MAX, location.x);
    EXPECT_EQ(UINT_MAX, location.y);
    EXPECT_EQ(UINT_MAX, location.z);
    EXPECT_EQ(0, location.area);
}

TEST_F(LocationTest, defaultLocationIsInvalid) {
    // Given
    Location location;

    // Then
    EXPECT_FALSE(location.isValid());
}

TEST_F(LocationTest, setLocationIsValid) {
    // Given
    Location location(1, 2, 3);

    // Then
    EXPECT_TRUE(location.isValid());
}

TEST_F(LocationTest, InitializedLocationHasThoseValues) {
    unsigned int x = 8;
    unsigned int y = 7;
    unsigned int z = 6;
    unsigned int area = 5;

    Location location(x, y, z, area);
    EXPECT_EQ(x, location.x);
    EXPECT_EQ(y, location.y);
    EXPECT_EQ(z, location.z);
    EXPECT_EQ(area, location.area);
}

TEST_F(LocationTest, DoubleEqualOperatorCompares) {
    Location lhs(1, 2, 3, 4);
    Location rhs(1, 2, 3, 4);
    Location nox(9, 2, 3, 4);
    Location noy(1, 9, 3, 4);
    Location noz(1, 2, 9, 4);
    Location noa(1, 2, 3, 9);

    EXPECT_TRUE(lhs == rhs);
    EXPECT_FALSE(lhs == nox);
    EXPECT_FALSE(lhs == noy);
    EXPECT_FALSE(lhs == noz);
    EXPECT_FALSE(lhs == noa);
}

TEST_F(LocationTest, LessThanComparesOnAllFields) {
    Location small(1, 2, 3, 4);
    Location big(2, 3, 4, 5);

    EXPECT_TRUE(small < big);
    big.area = 4;
    EXPECT_TRUE(small < big);
    big.z = 3;
    EXPECT_TRUE(small < big);
    big.y = 2;
    EXPECT_TRUE(small < big);
}

TEST_F(LocationTest, AssignmentCopiesAllFields) {
    Location rhs(1, 2, 3, 4);
    Location lhs(9, 9, 9, 9);

    lhs = rhs;
    EXPECT_EQ(lhs.x, rhs.x);
    EXPECT_EQ(lhs.y, rhs.y);
    EXPECT_EQ(lhs.z, rhs.z);
    EXPECT_EQ(lhs.area, rhs.area);
}

TEST_F(LocationTest, AssignmentIsTransitive) {
    // Given
    Location c(1, 2, 3, 4);
    Location b;
    Location a;

    // When
    a = b = c;

    // Then
    EXPECT_EQ(c.x, a.x);
    EXPECT_EQ(c.y, a.y);
    EXPECT_EQ(c.z, a.z);
    EXPECT_EQ(c.area, a.area);
}
