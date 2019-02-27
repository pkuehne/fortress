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

class MapManager_isValidTile : public MapManagerFixture {
    void SetUp() {
        area.setSize(width, height, depth);
        ASSERT_EQ(id, manager.addArea(area, id));
    }

protected:
    unsigned int width = 5;
    unsigned int height = 5;
    unsigned int depth = 5;
    unsigned int id = 1;
    AreaInfo area;
};

TEST_F(MapManager_isValidTile, returnsFalseForZeroArea) {
    // Given
    Location loc(1, 1, 1, 0);

    // When
    bool retval = manager.isValidTile(loc);

    // Then
    EXPECT_FALSE(retval);
}

TEST_F(MapManager_isValidTile, returnsTrueForLocationInsideArea) {
    // Given
    Location loc(width - 1, height - 1, depth - 1, id);

    // When
    bool retval = manager.isValidTile(loc);

    // Then
    EXPECT_TRUE(retval);
}

TEST_F(MapManager_isValidTile, returnsFalseForXOutsideArea) {
    // Given
    Location loc(width, height - 1, depth - 1, id);

    // When
    bool retval = manager.isValidTile(loc);

    // Then
    EXPECT_FALSE(retval);
}

TEST_F(MapManager_isValidTile, returnsFalseForYOutsideArea) {
    // Given
    Location loc(width - 1, height, depth - 1, id);

    // When
    bool retval = manager.isValidTile(loc);

    // Then
    EXPECT_FALSE(retval);
}

TEST_F(MapManager_isValidTile, returnsFalseForZOutsideArea) {
    // Given
    Location loc(width - 1, height - 1, depth, id);

    // When
    bool retval = manager.isValidTile(loc);

    // Then
    EXPECT_FALSE(retval);
}

class MapManager_location : public MapManagerFixture {
    void SetUp() {
        area.setSize(width, height, depth);
        ASSERT_EQ(id, manager.addArea(area, id));
        loc = Location(3, 3, 3, id);
    }

protected:
    unsigned int width = 5;
    unsigned int height = 5;
    unsigned int depth = 5;
    unsigned int id = 1;
    AreaInfo area;
    Location loc;
};

TEST_F(MapManager_location, changesYForNorthDirection) {
    // When
    Location result = manager.location(loc, Direction::North);

    // Then
    EXPECT_EQ(result.x, loc.x);
    EXPECT_EQ(result.y, loc.y - 1);
    EXPECT_EQ(result.z, loc.z);
    EXPECT_EQ(result.area, loc.area);
}

TEST_F(MapManager_location, changesYForSouthDirection) {
    // When
    Location result = manager.location(loc, Direction::South);

    // Then
    EXPECT_EQ(result.x, loc.x);
    EXPECT_EQ(result.y, loc.y + 1);
    EXPECT_EQ(result.z, loc.z);
    EXPECT_EQ(result.area, loc.area);
}

TEST_F(MapManager_location, changesXForWestDirection) {
    // When
    Location result = manager.location(loc, Direction::West);

    // Then
    EXPECT_EQ(result.x, loc.x - 1);
    EXPECT_EQ(result.y, loc.y);
    EXPECT_EQ(result.z, loc.z);
    EXPECT_EQ(result.area, loc.area);
}

TEST_F(MapManager_location, changesXForEastDirection) {
    // When
    Location result = manager.location(loc, Direction::East);

    // Then
    EXPECT_EQ(result.x, loc.x + 1);
    EXPECT_EQ(result.y, loc.y);
    EXPECT_EQ(result.z, loc.z);
    EXPECT_EQ(result.area, loc.area);
}

TEST_F(MapManager_location, XDirectionMustBeInMapWhenGoingWest) {
    // Given
    loc.x = 0;

    // When
    Location result = manager.location(loc, Direction::West);

    // Then
    EXPECT_EQ(result, loc);
}

TEST_F(MapManager_location, XDirectionMustBeInMapWhenGoingEast) {
    // Given
    loc.x = area.getWidth();

    // When
    Location result = manager.location(loc, Direction::East);

    // Then
    EXPECT_EQ(result, loc);
}

TEST_F(MapManager_location, XDirectionMustBeInMapWhenGoingNorth) {
    // Given
    loc.y = 0;

    // When
    Location result = manager.location(loc, Direction::North);

    // Then
    EXPECT_EQ(result, loc);
}

TEST_F(MapManager_location, XDirectionMustBeInMapWhenGoingSouth) {
    // Given
    loc.y = area.getHeight();

    // When
    Location result = manager.location(loc, Direction::South);

    // Then
    EXPECT_EQ(result, loc);
}