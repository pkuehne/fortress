#include "rural_generator.h"
#include "../components/sprite_component.h"
#include "../core/game_engine.h"
#include "../core/prefab_builder.h"
#include "../core/utility.h"
#include <cstring>
#include <glog/logging.h>
#include <iostream>
#include <map>

const unsigned char EMPTY = '.';
const unsigned char TREE = 'T';
const unsigned char LINK = '>';
const unsigned char HUMAN = 'H';
const unsigned char APPLE = 'A';

bool RuralGenerator::generate() {
    reset();
    initMap(EMPTY);

    LOG(INFO) << "Generating rural area" << std::endl;
    placeWoods();
    placePlayer();
    placeDungeonStairs();
    placeApples();
    placeForester();
    createEntitiesFromMap();
    LOG(INFO) << "Done generating area" << std::endl;
    return true;
}

void RuralGenerator::createEntitiesFromMap() {
    EntityId l_entity = 0;
    Location location;

    PrefabBuilder prefabs(m_engine->state());
    for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
        for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
            location.x = xx;
            location.y = yy;
            location.z = 0;
            location.area = m_area;
            m_engine->state()->tile(location).getFloor().setMaterial(
                Material::Grass);
            switch (getByCoordinate(xx, yy)) {
                case EMPTY:
                    break;
                case TREE:
                    l_entity = prefabs.createTreePrefab(location);
                    break;
                case LINK:
                    l_entity = prefabs.createStairPrefab(STAIR_DOWN, location);
                    m_areaLinks.push_back(l_entity);
                    break;
                case HUMAN:
                    l_entity = prefabs.createForesterPrefab(location);
                    break;
                case APPLE:
                    l_entity = prefabs.createApplePrefab(location);
                    break;
                default:
                    break;
            }
        }
    }
    location.x = m_mapWidth / 2;
    location.y = m_mapHeight / 2;
    location.z = 0;
    location.area = m_area;
    prefabs.createPlayerPrefab(location);
}

void RuralGenerator::reset() { GeneratorInterface::reset(); }

void RuralGenerator::placeWoods() {
    for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
        for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
            if (isValidCoordinate(xx, yy)) {
                unsigned char& tile = getByCoordinate(xx, yy);
                if (tile == TREE)
                    continue;
                unsigned int percentage = 30;
                if (isValidCoordinate(xx - 1, yy) &&
                    getByCoordinate(xx - 1, yy) == TREE)
                    percentage -= 10;
                if (isValidCoordinate(xx + 1, yy) &&
                    getByCoordinate(xx + 1, yy) == TREE)
                    percentage -= 10;
                if (isValidCoordinate(xx, yy - 1) &&
                    getByCoordinate(xx, yy - 1) == TREE)
                    percentage -= 10;
                if (isValidCoordinate(xx, yy + 1) &&
                    getByCoordinate(xx, yy + 1) == TREE)
                    percentage -= 10;
                if (Utility::randChance(percentage))
                    tile = TREE;
            }
        }
    }
}

void RuralGenerator::placePlayer() {}

void RuralGenerator::placeDungeonStairs() {
    unsigned int numStairs = Utility::randBetween(1, 5);

    for (unsigned int ii = 0; ii < numStairs; ii++) {
        unsigned int x = Utility::randBetween(0, m_mapWidth);
        unsigned int y = Utility::randBetween(0, m_mapHeight);
        if (isValidCoordinate(x, y)) {
            getByCoordinate(x, y) = LINK;
        }
    }
}

void RuralGenerator::placeForester() {
    unsigned int numTries = 50;
    for (unsigned int ii = 0; ii < numTries; ii++) {
        unsigned int x = Utility::randBetween(0, m_mapWidth);
        unsigned int y = Utility::randBetween(0, m_mapHeight);
        if (isValidCoordinate(x, y)) {
            if (getByCoordinate(x, y) == EMPTY) {
                getByCoordinate(x, y) = HUMAN;
                break;
            }
        }
    }
}

void RuralGenerator::placeApples() {
    unsigned int numApples = 10;
    unsigned int numTries = 50;

    while (numApples && numTries) {
        numTries--;
        unsigned int x = Utility::randBetween(0, m_mapWidth);
        unsigned int y = Utility::randBetween(0, m_mapHeight);
        if (isValidCoordinate(x, y)) {
            if (getByCoordinate(x, y) == EMPTY) {
                getByCoordinate(x, y) = APPLE;
                numApples--;
            }
        }
    }
}