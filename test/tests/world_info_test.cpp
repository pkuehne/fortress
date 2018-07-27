#include "../../src/world/world_info.h"
#include <gtest/gtest.h>

using namespace ::testing;

class WorldInfoTest_Grouping : public ::testing::Test {};

TEST_F(WorldInfoTest_Grouping, initializedWithName) {
    // Given
    WorldInfo info;

    // When
    Grouping grouping("bar");
    info.addGrouping(grouping);

    // Then
    EXPECT_EQ(1, info.getGroupings().size());
}
