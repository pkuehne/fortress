#include "rural_generator_system.h"
#include "../core/utility.h"
#include <cstring>
#include <iostream>
#include <map>
#include <spdlog/spdlog.h>

// const unsigned char EMPTY = '.';
// const unsigned char TREE = 'T';
// const unsigned char LINK = '>';
// const unsigned char HUMAN = 'H';
// const unsigned char APPLE = 'A';
// const unsigned char DOG = 'D';

// void RuralGenerator::registerHandlers() {
//     // auto generateHandler = [this](auto event) { this->generate(); };
//     // events()->subscribe<GenerateRuralMapEvent>(generateHandler);
// }

// EntityId RuralGenerator::createPrefab(const std::string& type,
//                                       Location& location) {
//     EntityId entity = entities()->createEntity(location);
//     events()->raise(std::make_shared<InstantiatePrefabEvent>(entity, type));
//     return entity;
// }

// bool RuralGenerator::generate() {
//     reset();
//     initMap(EMPTY);

//     placeWoods();
//     placePlayer();
//     placeDungeonStairs();
//     placeApples();
//     placeForester();
//     createEntitiesFromMap();
//     LOG(INFO) << "Done generating area" << std::endl;
//     return true;
// }

// void RuralGenerator::createEntitiesFromMap() {
//     EntityId l_entity = 0;
//     Location location;

//     for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
//         for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
//             location.x = xx;
//             location.y = yy;
//             location.z = 0;
//             location.area = m_area;
//             map()->getTile(location).setFloorMaterial(FloorMaterial::Grass);
//             switch (getByCoordinate(xx, yy)) {
//                 case EMPTY:
//                     break;
//                 case TREE:
//                     createPrefab("tree", location);
//                     break;
//                 case LINK:
//                     l_entity = createPrefab("stair", location);
//                     m_areaLinks.push_back(l_entity);
//                     break;
//                 case HUMAN:
//                     createPrefab("forester", location);
//                     break;
//                 case DOG:
//                     createPrefab("dog", location);
//                     break;
//                 case APPLE:
//                     createPrefab("apple", location);
//                     break;
//                 default:
//                     break;
//             }
//         }
//     }
//     location.x = m_mapWidth / 2;
//     location.y = m_mapHeight / 2;
//     location.z = 0;
//     location.area = m_area;
//     createPrefab("player", location);
// }

// void RuralGenerator::reset() { GeneratorInterface::reset(); }

// void RuralGenerator::placeWoods() {
//     for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
//         for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
//             if (isValidCoordinate(xx, yy)) {
//                 unsigned char& tile = getByCoordinate(xx, yy);
//                 if (tile == TREE)
//                     continue;
//                 unsigned int percentage = 30;
//                 if (isValidCoordinate(xx - 1, yy) &&
//                     getByCoordinate(xx - 1, yy) == TREE)
//                     percentage -= 10;
//                 if (isValidCoordinate(xx + 1, yy) &&
//                     getByCoordinate(xx + 1, yy) == TREE)
//                     percentage -= 10;
//                 if (isValidCoordinate(xx, yy - 1) &&
//                     getByCoordinate(xx, yy - 1) == TREE)
//                     percentage -= 10;
//                 if (isValidCoordinate(xx, yy + 1) &&
//                     getByCoordinate(xx, yy + 1) == TREE)
//                     percentage -= 10;
//                 if (Utility::randChance(percentage))
//                     tile = TREE;
//             }
//         }
//     }
// }

// void RuralGenerator::placePlayer() {}

// void RuralGenerator::placeDungeonStairs() {
//     unsigned int numStairs = Utility::randBetween(1, 5);

//     for (unsigned int ii = 0; ii < numStairs; ii++) {
//         unsigned int x = Utility::randBetween(0, m_mapWidth);
//         unsigned int y = Utility::randBetween(0, m_mapHeight);
//         if (isValidCoordinate(x, y)) {
//             getByCoordinate(x, y) = LINK;
//         }
//     }
// }

// void RuralGenerator::placeForester() {
//     unsigned int numTries = 50;
//     unsigned int x = 0;
//     unsigned int y = 0;

//     for (unsigned int ii = 0; ii < numTries; ii++) {
//         x = Utility::randBetween(0, m_mapWidth);
//         y = Utility::randBetween(0, m_mapHeight);
//         if (isValidCoordinate(x, y)) {
//             if (getByCoordinate(x, y) == EMPTY) {
//                 getByCoordinate(x, y) = HUMAN;
//                 break;
//             }
//         }
//     }

//     // Place the dog too
//     bool dogPlaced = false;
//     auto checkAndPlace = [&](int x, int y) {
//         if (!dogPlaced && isValidCoordinate(x, y)) {
//             if (getByCoordinate(x, y) == EMPTY) {
//                 getByCoordinate(x, y) = DOG;
//                 dogPlaced = true;
//             }
//         }
//     };
//     for (unsigned int xx = 0; xx < 10 && !dogPlaced; xx++) {
//         for (unsigned int yy = 0; yy < 10 && !dogPlaced; yy++) {
//             checkAndPlace(x + xx, y + yy);
//             checkAndPlace(x - xx, y + yy);
//             checkAndPlace(x + xx, y - yy);
//             checkAndPlace(x - xx, y - yy);
//         }
//     }
// }

// void RuralGenerator::placeApples() {
//     unsigned int numApples = 10;
//     unsigned int numTries = 50;

//     while (numApples && numTries) {
//         numTries--;
//         unsigned int x = Utility::randBetween(0, m_mapWidth);
//         unsigned int y = Utility::randBetween(0, m_mapHeight);
//         if (isValidCoordinate(x, y)) {
//             if (getByCoordinate(x, y) == EMPTY) {
//                 getByCoordinate(x, y) = APPLE;
//                 numApples--;
//             }
//         }
//     }
// }