#include "tile.h"
#include "color.h"
#include "utility.h"

void Tile::setSprite() {
    if (m_wallMaterial != WallMaterial::None) {
        m_sprite.fgColor = Color(GREY);
        m_sprite.bgColor = Color(BLACK);
        m_sprite.sprite = 'W';
        return;
    }

    char floor_sprites[] = ".,";
    switch (m_floorMaterial) {
        case FloorMaterial::Grass:
            m_sprite.sprite = floor_sprites[Utility::randBetween(
                0, sizeof(floor_sprites) - 2)];
            m_sprite.fgColor = Color(GREEN);
            m_sprite.bgColor = Color(DARK_GREEN);
            break;
        case FloorMaterial::Rock:
            m_sprite.sprite = floor_sprites[Utility::randBetween(
                0, sizeof(floor_sprites) - 2)];
            m_sprite.fgColor = Color(GREY);
            m_sprite.bgColor = Color(GREY);
            break;

        case FloorMaterial::None: // Default
        default:
            m_sprite.sprite = 0;
            m_sprite.fgColor = Color(BLACK);
            m_sprite.bgColor = Color(BLACK);
            break;
    }
}

void Tile::setFloorMaterial(const FloorMaterial& material) {
    m_floorMaterial = material;
    setSprite();
}

void Tile::setWallMaterial(const WallMaterial& material) {
    m_wallMaterial = material;
    setSprite();
}
