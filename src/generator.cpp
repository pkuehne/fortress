#include "generator.h"
#include "gameengine.h"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>

static bool generateRoom (GEN_PARAMS params, char*);

void generateDungeon (GameEngineInterface* a_engine, GEN_PARAMS params) {
    srand(time(0));

    bool playerPlaced = false;
    char map[params.height*params.width];
    memset (map, ' ', params.height*params.width);

    for (unsigned r = 0; r < params.rooms; r++) {
        while (!generateRoom (params, map));
    }

    for (unsigned int yy = 0; yy < params.height; yy++) {
        for (unsigned int xx = 0; xx < params.width; xx++) {
            if (map[yy*params.width+xx] == 'W') {
                a_engine->getEntities().createWallPrefab (yy, xx);
            }
            if (map[yy*params.width+xx] == 'P' && !playerPlaced) {
                a_engine->getEntities().createPlayerPrefab (yy, xx);
                playerPlaced = true;
            }
            if (map[yy*params.width+xx] == 'M') {
                a_engine->getEntities().createEnemyPrefab (yy, xx);
            }
            if (map[yy*params.width+xx] == '.') {
                a_engine->getEntities().createTilePrefab (yy, xx);
            }
        }
    }
}

bool generateRoom (GEN_PARAMS params, char* map) {
    unsigned int xMid = rand() % (params.width-1) + 1;
    unsigned int yMid = rand() % (params.height-1) + 1;
    unsigned int length = rand() % 6 + 3;
    unsigned int height = rand() % 6 + 3;

    unsigned int startY = yMid - height;
    unsigned int startX = xMid - length;
    unsigned int endY = yMid + height;
    unsigned int endX = xMid + length;

    if (startY < 2 || startX < 2 || endY > params.height - 2 || endX > params.width - 2) {
        std::cout << "Failed dimensions" << std::endl;
        return false;
    }
    for (unsigned int yy = startY; yy <= endY; yy++) {
        if (map[yy*params.width+startX] == 'W' || map[yy*params.width+endX] == 'W') {
            std::cout << "Failed vertical wall check" << std::endl;
            return false;
        }
        map[yy*params.width+startX] = 'W';
        map[yy*params.width+endX] = 'W';
    }
    for (unsigned int xx = startX+1; xx <= endX-1; xx++) {
        if (map[startY*params.width+xx] == 'W' || map[endY*params.width+xx] == 'W') {
            std::cout << "Failed horizontal wall check" << std::endl;
            return false;
        }
        map[startY*params.width+xx] = 'W';
        map[endY*params.width+xx] = 'W';
    }
    for (unsigned int yy = startY+1; yy < endY; yy++) {
        for (unsigned int xx = startX+1; xx < endX; xx++) {
            map[yy*params.width+xx] = '.';
        }
    }
    map[yMid*params.width+xMid] = 'P';
    map[yMid*params.width+xMid+2] = 'M';

    return true;
}
