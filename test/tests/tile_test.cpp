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

TEST(Tile, overrideSprite_resetsSpriteToSomethingElse) {
    // Given
    Tile tile;
    char symbol = '-';

    ASSERT_NE(symbol, tile.getSprite().sprite);

    // When
    tile.overrideSpriteSymbol(symbol);

    // Then
    EXPECT_EQ(symbol, tile.getSprite().sprite);
}