#include "../../src/core/world_info.h"
#include <gtest/gtest.h>

using namespace ::testing;

class WorldInfoTest_Faction : public ::testing::Test {};

TEST_F(WorldInfoTest_Faction, initializedWithName) {
    // Given
    WorldInfo info;

    // When
    Faction faction("bar");
    info.addFaction(faction);

    // Then
    EXPECT_EQ(1, info.getFactions().size());
}
