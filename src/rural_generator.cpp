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
    static unsigned int offset = 0;
    unsigned int seed = time(0) + offset++;
    //srand(1439294983);
    srand (seed);

    reset();
    initMap (EMPTY);

    std::cout << "Generating rural area" << std::endl;
    for (unsigned int ii = 0; ii < 5; ii++) {
        placeWoods();
    }
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
                    m_engine->getComponents()->get<SpriteComponent>(l_entity)->fgColor = Color (GREEN);
                    break;
                case TREE:
                default:
                    l_entity = m_engine->getEntities()->createWallPrefab (location);
                    m_engine->getComponents()->get<SpriteComponent>(l_entity)->sprite = getByCoordinate (xx, yy);
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
    unsigned int xOffset = Utility::randBetween (10, m_mapWidth-10);
    unsigned int yOffset = Utility::randBetween (10, m_mapHeight-10);
    for (unsigned int yy = yOffset-10; yy < yOffset+10; yy++) {
        for (unsigned int xx = xOffset-10; xx < xOffset+10; xx++) {
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
