#include "floor.h"
#include "utility.h"

Floor::Floor (Material material) 
: m_material(material)
{
    setMaterial (material);
}

void Floor::setMaterial (Material material)
{
    m_material = material;
    char floor_sprites[] = ".,";
    switch (material) {
        case Grass:
            m_sprite.sprite  = floor_sprites[Utility::randBetween(0, 
                                            sizeof(floor_sprites)-2)];
            m_sprite.fgColor = GREEN;
            m_sprite.bgColor = DARK_GREEN;
            break;
        case Rock:
            std::cerr << "Rock material" << std::endl;
            m_sprite.sprite  = 
                floor_sprites[Utility::randBetween(0, 
                                            sizeof(floor_sprites)-2)];
            m_sprite.fgColor = GREY;
            m_sprite.bgColor = GREY;
            break;

        case None: // Default
        default:
            std::cerr << "Default material" << std::endl;
            m_sprite.sprite = 0;
            m_sprite.fgColor = BLACK;
            m_sprite.bgColor = BLACK;
            break;
    }
}

