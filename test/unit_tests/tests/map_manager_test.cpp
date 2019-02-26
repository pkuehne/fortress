#include "map_manager.h"
#include <gtest/gtest.h>

using namespace ::testing;

class MapManagerFixture : public ::testing::Test {
protected:
    MapManager manager;
};

class MapManager_addArea : public MapManagerFixture {
protected:
    AreaInfo area;
    AreaInfo area_one;
    AreaInfo area_two;
};

TEST_F(MapManager_addArea, createsIdIfNotGiven) {
    // When
    auto id = manager.addArea(area);

    // Then
    ASSERT_NE(0, id);
}

TEST_F(MapManager_addArea, returnsGivenId) {
    unsigned int expected_id = 99;

    // When
    auto id = manager.addArea(area, expected_id);

    // Then
    ASSERT_EQ(expected_id, id);
}

TEST_F(MapManager_addArea, replacesAreaWithSameId) {
    // Given
    area_one.setSize(1, 2, 3);
    area_two.setSize(9, 8, 7);

    auto id = manager.addArea(area_one);

    // When
    auto new_id = manager.addArea(area_two, id);

    // Then
    ASSERT_EQ(id, new_id);
    EXPECT_EQ(area_two.getHeight(), manager.getAreas()[id].getHeight());
}

class MapManager_createArea : public MapManagerFixture {
protected:
    unsigned int width = 1;
    unsigned int height = 1;
    unsigned int depth = 1;
};

TEST_F(MapManager_createArea, requiredNonZeroWidth) {
    // Given
    width = 0;

    // When
    EXPECT_ANY_THROW(manager.createArea(width, height, depth));
}

TEST_F(MapManager_createArea, requiredNonZeroHeight) {
    // Given
    height = 0;

    // When
    EXPECT_ANY_THROW(manager.createArea(width, height, depth));
}

TEST_F(MapManager_createArea, requiredNonZeroDepth) {
    // Given
    depth = 0;

    // When
    EXPECT_ANY_THROW(manager.createArea(width, height, depth));
}

TEST_F(MapManager_createArea, createsAnArea) {
    // Given
    ASSERT_EQ(manager.getAreas().size(), 0);

    // When
    auto id = manager.createArea(width, height, depth);

    // Then
    EXPECT_EQ(1, manager.getAreas().size());
    EXPECT_NE(0, id);
}
