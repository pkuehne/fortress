#include "rural_generator.h"
#include "utility.h"
#include "game_engine.h"
#include "sprite_component.h"
#include <ctime>
#include <cstring>
#include <map>
#include <iostream>

const unsigned char EMPTY = '.';
const unsigned char TREE = 'T';

bool RuralGenerator::generate()
{
    reset();
    initMap (EMPTY);

    std::cout << "Generating rural area" << std::endl;
    placeWoods();
    placePlayer();
    createEntitiesFromMap();
    std::cout << "Done generating" << std::endl;
    return true;
}

void RuralGenerator::createEntitiesFromMap()
{
    EntityId l_entity = 0;
    Location location;

    for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
        for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
            location.x = xx;
            location.y = yy;
            location.z = 1;
            switch (getByCoordinate(xx, yy)) {
                case EMPTY:
                    l_entity = m_engine->getEntities()->createTilePrefab (location);
                    m_engine->getComponents()->get<SpriteComponent>(l_entity)->fgColor = Color (DARK_GREEN);
                    break;
                case TREE:
                default:
                    l_entity = m_engine->getEntities()->createTreePrefab (location);
                    break;
            }
        }
    }
    location.x = m_mapWidth/2;
    location.y = m_mapHeight/2;
    location.z = 1;
    m_engine->getEntities()->createPlayerPrefab (location);

}

void RuralGenerator::reset ()
{
    GeneratorInterface::reset();
}

void RuralGenerator::placeWoods()
{
    //unsigned int xOffset = Utility::randBetween (0, m_mapWidth);
    //unsigned int yOffset = Utility::randBetween (0, m_mapHeight);
    for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
        for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
            if (isValidCoordinate (xx, yy)) {
                unsigned char& tile = getByCoordinate(xx,yy);
                if (tile == TREE) continue;
                unsigned int percentage = 60;
                if (isValidCoordinate (xx-1, yy) && getByCoordinate (xx-1, yy)) percentage -= 10;
                if (isValidCoordinate (xx+1, yy) && getByCoordinate (xx+1, yy)) percentage -= 10;
                if (isValidCoordinate (xx, yy-1) && getByCoordinate (xx, yy-1)) percentage -= 10;
                if (isValidCoordinate (xx, yy+1) && getByCoordinate (xx, yy+1)) percentage -= 10;
                if (Utility::randChance(percentage)) tile = TREE;
            }
        }
    }
}

void RuralGenerator::placePlayer()
{

}
