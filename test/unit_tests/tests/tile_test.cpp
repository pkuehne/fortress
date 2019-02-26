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

TEST(Tile, setWallMaterial_floorMaterial) {
    // Given
    Tile tile;

    // When
    tile.setFloorMaterial(FloorMaterial::Rock);

    // Then
    EXPECT_EQ(FloorMaterial::Rock, tile.getFloorMaterial());
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

TEST(Tile, entities_setCountGet) {
    // Given
    Tile tile;
    EntityId entity = 1234;

    // When
    tile.addEntity(entity);

    // Then
    EXPECT_EQ(1, tile.entities().size());

    tile.removeEntity(entity);
    EXPECT_EQ(0, tile.entities().size());
}

TEST(Tile, entities_lit) {
    // Given
    Tile tile;
    EXPECT_FALSE(tile.lit());

    // When
    tile.lit() = true;

    // Then
    EXPECT_TRUE(tile.lit());
}

TEST(Tile, entities_lastVisited) {
    // Given
    Tile tile;
    EXPECT_EQ(0, tile.lastVisited());

    // When
    tile.lastVisited() = 1234;

    // Then
    EXPECT_EQ(1234, tile.lastVisited());
}