#include "rural_generator.h"
#include "utility.h"
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

    m_map = new unsigned char[m_mapHeight*m_mapWidth];
    memset (m_map, EMPTY, m_mapHeight*m_mapWidth);

    placeWoods();
    placePlayer();
    return true;
}

void RuralGenerator::createEntitiesFromMap()
{

}

void RuralGenerator::reset ()
{
    if (m_map) {
        delete[] m_map;
        m_map = 0;
    }
}

void RuralGenerator::placeWoods()
{
    unsigned int xOffset = Utility::randBetween (10, m_mapWidth-10);
    unsigned int yOffset = Utility::randBetween (10, m_mapHeight-10);

    for (unsigned int yy = yOffset-10; yy < yOffset+10; yOffset++) {
        for (unsigned int xx = xOffset-10; xx < xOffset+10; xOffset++) {
            if (isValid (xx, yy)) {
                unsigned char tile = getByCoordinate(xx,yy);
                if (tile == TREE) continue;
                tile = TREE;
            }
        }
    }



}

void RuralGenerator::placePlayer()
{

}
