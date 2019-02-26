#include "../../src/core/map_manager.h"
#include <gtest/gtest.h>

using namespace ::testing;

class MapManager_addArea : public ::testing::Test {};

TEST_F(MapManager_addArea, createsIdIfNotGiven) {
    // Given
    MapManager map;
    AreaInfo area;

    // When
    auto id = map.addArea(area);

    // Then
    ASSERT_NE(0, id);
}

TEST_F(MapManager_addArea, returnsGivenId) {
    // Given
    MapManager map;
    AreaInfo area;
    unsigned int expected_id = 99;

    // When
    auto id = map.addArea(area, expected_id);

    // Then
    ASSERT_EQ(expected_id, id);
}

TEST_F(MapManager_addArea, replacesAreaWithSameId) {
    // Given
    MapManager map;
    AreaInfo area_one;
    AreaInfo area_two;

    area_one.setSize(1, 2, 3);
    area_two.setSize(9, 8, 7);

    auto id = map.addArea(area_one);

    // When
    auto new_id = map.addArea(area_two, id);

    // Then
    ASSERT_EQ(id, new_id);
    EXPECT_EQ(area_two.getHeight(), map.getAreas()[id].getHeight());
}
