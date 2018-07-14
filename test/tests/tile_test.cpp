#include "../../src/core/tile.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(Tile, setWallMaterial_TileNotBlockedByDefault) {
    // Given
    Tile tile;

    // When+Then
    EXPECT_FALSE(tile.blocked());
}

TEST(Tile, setWallMaterial_MarksTileAsBlocked) {
    // Given
    Tile tile;

    // When
    tile.setWallMaterial(WallMaterial::Rock);

    // Then
    EXPECT_TRUE(tile.blocked());
}