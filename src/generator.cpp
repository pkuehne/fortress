#include "generator.h"
#include "gameengine.h"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

void Generator::generate () {
    srand(time(0));

    bool playerPlaced = false;
    m_mapHeight = 50;
    m_mapWidth = 50;
    char map[m_mapHeight*m_mapWidth];
    memset (map, ' ', m_mapHeight*m_mapWidth);

    /*
    for (unsigned r = 0; r < m_rooms; r++) {
        while (!generateRoom (map));
    }
    */
    loadMap (map);

    for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
        for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
            if (map[yy*m_mapWidth+xx] == 'W') {
                m_engine->getEntities()->createWallPrefab (xx, yy);
            }
            if (map[yy*m_mapWidth+xx] == 'P' && !playerPlaced) {
                m_engine->getEntities()->createPlayerPrefab (xx, yy);
                m_engine->getEntities()->createTilePrefab (xx, yy);
                playerPlaced = true;
            }
            if (map[yy*m_mapWidth+xx] == 'O') {
                m_engine->getEntities()->createEnemyPrefab (xx, yy);
                m_engine->getEntities()->createTilePrefab (xx, yy);
            }
            if (map[yy*m_mapWidth+xx] == '.') {
                m_engine->getEntities()->createTilePrefab (xx, yy);
            }
        }
    }
}

bool Generator::generateRoom (char* map) {
    unsigned int xMid = rand() % (m_mapWidth-1) + 1;
    unsigned int yMid = rand() % (m_mapHeight-1) + 1;
    unsigned int length = rand() % 6 + 3;
    unsigned int height = rand() % 6 + 3;

    unsigned int startY = yMid - height;
    unsigned int startX = xMid - length;
    unsigned int endY = yMid + height;
    unsigned int endX = xMid + length;

    if (startY < 2 || startX < 2 || endY > m_mapHeight - 2 || endX > m_mapWidth - 2) {
        std::cout << "Failed dimensions" << std::endl;
        return false;
    }
    for (unsigned int yy = startY; yy <= endY; yy++) {
        if (map[yy*m_mapWidth+startX] == 'W' || map[yy*m_mapWidth+endX] == 'W') {
            std::cout << "Failed vertical wall check" << std::endl;
            return false;
        }
        map[yy*m_mapWidth+startX] = 'W';
        map[yy*m_mapWidth+endX] = 'W';
    }
    for (unsigned int xx = startX+1; xx <= endX-1; xx++) {
        if (map[startY*m_mapWidth+xx] == 'W' || map[endY*m_mapWidth+xx] == 'W') {
            std::cout << "Failed horizontal wall check" << std::endl;
            return false;
        }
        map[startY*m_mapWidth+xx] = 'W';
        map[endY*m_mapWidth+xx] = 'W';
    }
    for (unsigned int yy = startY+1; yy < endY; yy++) {
        for (unsigned int xx = startX+1; xx < endX; xx++) {
            map[yy*m_mapWidth+xx] = '.';
        }
    }
    map[yMid*m_mapWidth+xMid] = 'P';
    map[yMid*m_mapWidth+xMid+2] = 'O';
    map[(yMid+2)*m_mapWidth+xMid] = 'O';

    return true;
}

void Generator::loadMap (char* map)
{
    std::ifstream file ("../maps/test.map");
    char line[m_mapWidth];
    int lineCnt = 0;
    do {
        memset (line, ' ', sizeof (line));
        file.getline (line, sizeof (line));
        memcpy (map+(m_mapWidth*lineCnt), line, sizeof(line));
        lineCnt++;
    } while (file.gcount() > 0);
}
