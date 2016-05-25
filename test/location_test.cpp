#include <gtest/gtest.h>
#include "location.h"

using namespace ::testing;

class LocationTest : public ::testing::Test
{

};

TEST_F (LocationTest, emptyLocationIsInvalid)
{
    Location location;
    EXPECT_EQ (UINT_MAX, location.x);
    EXPECT_EQ (UINT_MAX, location.y);
    EXPECT_EQ (UINT_MAX, location.z);
    EXPECT_EQ (0, location.area);
}

TEST_F (LocationTest, InitializedLocationHasThoseValues)
{
    unsigned int x = 8;
    unsigned int y = 7;
    unsigned int z = 6;
    unsigned int area = 5;

    Location location(x, y, z, area);
    EXPECT_EQ (x, location.x);
    EXPECT_EQ (y, location.y);
    EXPECT_EQ (z, location.z);
    EXPECT_EQ (area, location.area);
}

TEST_F (LocationTest, DoubleEqualOperatorCompares)
{
    Location lhs (1, 2, 3, 4);
    Location rhs (1, 2, 3, 4);
    Location nox (9, 2, 3, 4);
    Location noy (1, 9, 3, 4);
    Location noz (1, 2, 9, 4);
    Location noa (1, 2, 3, 9);
    
    EXPECT_TRUE (lhs == rhs);
    EXPECT_FALSE (lhs == nox);
    EXPECT_FALSE (lhs == noy);
    EXPECT_FALSE (lhs == noz);
    EXPECT_FALSE (lhs == noa);
}

TEST_F (LocationTest, LessThanComparesOnAllFields)
{
    Location small (1, 2, 3, 4);
    Location big (2, 3, 4, 5);
    
    EXPECT_TRUE (small < big);
    big.area = 4;
    EXPECT_TRUE (small < big);
    big.z = 3;
    EXPECT_TRUE (small < big);
    big.y = 2;
    EXPECT_TRUE (small < big);
}



