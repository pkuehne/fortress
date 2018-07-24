#include "dungeon_generator.h"
#include "../algos/algorithm.h"
#include "../components/connector_component.h"
#include "../components/sprite_component.h"
#include "../core/game_engine.h"
#include "../core/prefab_builder.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <glog/logging.h>
#include <iostream>

static unsigned int getDistance(const Location& start, const Location& end,
                                void* customData);
static int getPathCost(const Location& location, void* customData);
static unsigned int findNeighbours4(const Location& location,
                                    Location* neighbours, void* customData);
static unsigned int findNeighbours8(const Location& location,
                                    Location* neighbours, void* customData);

const char WALL = '#';
const char CORNER = 'C';
const char FLOOR = '.';
const char DOOR = 'D';
const char EMPTY = ' ';
const char RESTRICTED = 'X';
const char ORC = 'O';
const char UP = '<';
const char DOWN = '>';

void DungeonGenerator::reset() {
    GeneratorInterface::reset();

    m_startRoom = 0;
    m_rooms.clear();
}

bool DungeonGenerator::generate() {
    for (m_level = 0; m_level < m_maxDepth; m_level++) {
        reset();
        initMap(EMPTY);
        LOG(INFO) << "Creating level " << m_level << " of area " << m_area
                  << std::endl;
        if (!generateLevel())
            return false;
    }
    return true;
}

bool DungeonGenerator::generateLevel() {
    for (unsigned r = 0; r < m_roomTarget; r++) {
        bool success = false;
        int x = 0;
        do {
            success = generateRoom();
        } while (!success && x++ < 100);
        if (!success) {
            LOG(WARNING) << "Tried " << x << " times to create room: " << r
                         << std::endl;
            return false;
        }
    }
    for (size_t ii = 0; ii < m_rooms.size() - 1; ii++) {
        connectRooms(m_rooms[ii], m_rooms[ii + 1]);
    }

    placeUpStair();
    placeDownStair();
    placeOrcs();
    placeItems();
    createEntitiesFromMap();
    connectStairs();
    return true;
}

void DungeonGenerator::createEntity(const Location& location) {
    auto state = m_engine->state();

    auto createStair = [=](const Location& location, unsigned int& stair,
                           bool down) {
        stair = state->prefabs().create("stair", location);
        state->components()->get<SpriteComponent>(stair)->sprite =
            (30 + (down ? 1 : 0));
    };
    auto createOrc = [=](const Location& location) {
        if (m_createBoss && m_level == m_maxDepth - 1) {
            state->prefabs().create("troll", location);
            m_createBoss = false;
        } else {
            state->prefabs().create("orc", location);
        }
    };

    Tile& tile = state->tile(location);
    tile.setFloorMaterial(FloorMaterial::Rock);

    switch (getByCoordinate(location.x, location.y)) {
        case WALL:
        case CORNER:
            tile.setWallMaterial(WallMaterial::Rock);
            tile.overrideSpriteSymbol(wallSprite(location.x, location.y));
            break;
        case UP:
            createStair(location, m_upStair, false);
            break;
        case DOWN:
            if (m_level < m_maxDepth - 1 || m_downStairTarget) {
                createStair(location, m_downStair, true);
            }
            break;
        case ORC:
            createOrc(location);
            break;
        case DOOR:
            state->prefabs().create("door", location);
            break;
        case EMPTY:
        case FLOOR:
        case RESTRICTED:
            break;
        default:
            LOG(WARNING) << "Creating marker prefab at " << location
                         << std::endl;
            state->prefabs().create("marker", location);
            break;
    }
}

void DungeonGenerator::createEntitiesFromMap() {
    for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
        for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
            Location location;
            location.x = xx;
            location.y = yy;
            location.z = m_level;
            location.area = m_area;

            createEntity(location);
        }
    }
}

void DungeonGenerator::connectStairs() {
    auto state = m_engine->state();

    if (m_level == 0) {
        state->components()->get<ConnectorComponent>(m_upStair)->target =
            m_upStairTarget;
        m_upStairLink = m_upStair;
    } else {
        state->components()->get<ConnectorComponent>(m_upStair)->target =
            m_prevDownStair;
    }
    if (m_level == m_maxDepth - 1 && m_downStairTarget) {
        state->components()->get<ConnectorComponent>(m_downStair)->target =
            m_downStairTarget;
        m_downStairLink = m_downStair;
    }
    if (m_level > 0 && m_prevDownStair > 0) {
        state->components()->get<ConnectorComponent>(m_prevDownStair)->target =
            m_upStair;
    }
    m_prevDownStair = m_downStair;
}

bool DungeonGenerator::validateRoom(unsigned int width, unsigned int height,
                                    unsigned int left, unsigned int top) {
    if (left + width >= m_mapWidth || left < 1 || top + height >= m_mapHeight ||
        top < 1) {
        return false;
    }

    for (unsigned int yy = top - 2; yy <= top + height + 1; yy++) {
        for (unsigned int xx = left - 2; xx <= left + width + 1; xx++) {
            if (getByCoordinate(xx, yy) != EMPTY)
                return false;
        }
    }
    return true;
}

bool DungeonGenerator::generateRoom() {
    unsigned int width = Utility::randBetween(5, 10);
    unsigned int height = Utility::randBetween(5, 10);
    unsigned int left = Utility::randBetween(2, (m_mapWidth - width - 2));
    unsigned int top = Utility::randBetween(2, (m_mapHeight - height - 2));

    if (!validateRoom(width, height, left, top)) {
        return false;
    }

    Room l_room;
    l_room.x = left;
    l_room.y = top;
    l_room.width = width;
    l_room.height = height;
    l_room.midX = left + (width / 2);
    l_room.midY = top + (height / 2);
    l_room.index = CoordToIndex(l_room.midX, l_room.midY);
    m_rooms.push_back(l_room);

    auto mapSetter = [=](unsigned int x, unsigned int y, Room& room) {
        getByCoordinate(x, y) = FLOOR; // By default

        // Check whether this should be something else
        if (y < room.y || y >= room.y + room.height || x < room.x ||
            x >= room.x + room.width) {
            getByCoordinate(x, y) = RESTRICTED;
        } else if (y == room.y || y == room.y + room.height - 1 ||
                   x == room.x || x == room.x + room.width - 1) {
            getByCoordinate(x, y) = WALL; // It's a wall
            if ((y <= room.y + 1 || y >= room.y + room.height - 2) &&
                (x <= room.x + 1 || x >= room.x + room.width - 2)) {
                getByCoordinate(x, y) = CORNER; // Wait, actually a corner
            }
        }
    };

    for (unsigned int yy = top - 2; yy <= top + height + 1; yy++) {
        for (unsigned int xx = left - 2; xx <= left + width + 1; xx++) {
            mapSetter(xx, yy, l_room);
        }
    }

    return true;
}

void DungeonGenerator::connectRooms(Room& start, Room& end) {
    Algorithm algo;
    algo.setCustomData(this);
    algo.setCostFunction(getPathCost);
    algo.setDistanceFunction(getDistance);
    algo.setNeighbourFunction(findNeighbours4);
    algo.setNumNeighbours(4);

    PathVector l_path;
    Location startLoc(start.midX, start.midY, 0);
    Location endLoc(end.midX, end.midY, 0);
    algo.findPath(startLoc, endLoc, l_path);
    // std::cout << "Found a " << l_path.size() << " tile corridor from "
    //    << startLoc << " to " << endLoc
    //    << std::endl;

    for (size_t ii = 0; ii < l_path.size(); ii++) {
        // std::cout << "Step: " << l_path[ii] << std::endl;
        unsigned char& tile = getByCoordinate(l_path[ii].x, l_path[ii].y);

        // Create tiles and doors
        if (tile == WALL || tile == DOOR) {
            tile = DOOR;
        } else {
            tile = FLOOR;
        }
    }

    for (size_t ii = 0; ii < l_path.size(); ii++) {
        // Wall of neighbours if necessary
        // std::cout << "Checking neighbours of " << l_path[ii] << std::endl;
        Location neighbours[8];
        size_t count = findNeighbours8(l_path[ii], neighbours, this);
        for (size_t hh = 0; hh < count; hh++) {
            // std::cout << "Setting up neighbour " << neighbours[hh] <<
            // std::endl;
            unsigned char& adj =
                getByCoordinate(neighbours[hh].x, neighbours[hh].y);
            if (adj == EMPTY || adj == RESTRICTED) {
                adj = WALL;
            }
        }
    }
}

void DungeonGenerator::placeUpStair() {
    m_startRoom = Utility::randBetween(0, m_rooms.size() - 1);
    getByCoordinate(m_rooms[m_startRoom].midX, m_rooms[m_startRoom].midY) = UP;
}

void DungeonGenerator::placeDownStair() {
    if (m_rooms.size() < 2)
        return; // No point
    unsigned int room = m_startRoom;
    while (room == m_startRoom) {
        room = Utility::randBetween(0, m_rooms.size() - 1);
    }
    getByCoordinate(m_rooms[room].midX, m_rooms[room].midY) = DOWN;
}

void DungeonGenerator::placeOrcs() {
    if (m_rooms.size() < 2)
        return; // No point

    unsigned int numOrcs = Utility::randBetween(1, m_rooms.size() + m_level);
    for (size_t ii = 0; ii < numOrcs; ii++) {
        while (1) {
            unsigned int room = Utility::randBetween(0, m_rooms.size() - 1);
            if (m_startRoom == room) {
                continue;
            }
            unsigned int x, y;
            x = m_rooms[room].x +
                (Utility::randBetween(0, m_rooms[room].width - 2)) + 1;
            y = m_rooms[room].y +
                (Utility::randBetween(0, m_rooms[room].height - 2)) + 1;
            unsigned char& tile = getByCoordinate(x, y);
            if (tile == FLOOR) {
                tile = ORC;
                break;
            }
        }
    }
}
void DungeonGenerator::placeItem(const Location& location) {
    unsigned int type = Utility::randBetween(0, 100);
    if (type < 70) { // Potion
        m_engine->state()->prefabs().create("potion", location);
    } else if (type < 80) {
        m_engine->state()->prefabs().create("sword", location);
    } else if (type < 90) {
        m_engine->state()->prefabs().create("shield", location);
    } else if (type < 100) {
        m_engine->state()->prefabs().create("helmet", location);
    }
}

void DungeonGenerator::placeItems() {
    unsigned int maxItems = 1;
    maxItems += (m_rooms.size() > 3) ? m_rooms.size() - 3 : 0;
    maxItems += (m_level > 4) ? m_level - 4 : 0;

    unsigned int numItems = Utility::randBetween(0, maxItems);

    for (size_t ii = 0; ii < numItems; ii++) {
        unsigned int room = Utility::randBetween(0, m_rooms.size() - 1);
        unsigned int x, y;
        do {
            x = m_rooms[room].x +
                (Utility::randBetween(0, m_rooms[room].width - 2)) + 1;
            y = m_rooms[room].y +
                (Utility::randBetween(0, m_rooms[room].height - 2)) + 1;
        } while (getByCoordinate(x, y) != FLOOR);

        Location location;
        location.x = x;
        location.y = y;
        location.z = m_level;
        location.area = m_area;
        placeItem(location);
    }
}

int calculateSpriteKey(unsigned char left, unsigned char up,
                       unsigned char right, unsigned char down) {
    int sprite_key = 0;
    if (left == WALL || left == CORNER) {
        sprite_key |= 8;
    }
    if (up == WALL || up == CORNER) {
        sprite_key |= 4;
    }
    if (right == WALL || right == CORNER) {
        sprite_key |= 2;
    }
    if (down == WALL || down == CORNER) {
        sprite_key |= 1;
    }
    return sprite_key;
}

unsigned char spriteCharFromKey(int sprite_key) {
    static const unsigned char sprite[16] = {206, 210, 198, 201, 208, 186,
                                             200, 204, 181, 187, 205, 203,
                                             188, 185, 202, 206};

    return sprite[sprite_key];
}

unsigned char DungeonGenerator::wallSprite(unsigned int x, unsigned int y) {
    unsigned char left =
        isValidCoordinate(x - 1, y) ? getByCoordinate(x - 1, y) : 0;
    unsigned char up =
        isValidCoordinate(x, y - 1) ? getByCoordinate(x, y - 1) : 0;
    unsigned char right =
        isValidCoordinate(x + 1, y) ? getByCoordinate(x + 1, y) : 0;
    unsigned char down =
        isValidCoordinate(x, y + 1) ? getByCoordinate(x, y + 1) : 0;

    int sprite_key = calculateSpriteKey(left, up, right, down);
    return spriteCharFromKey(sprite_key);
}

static int getPathCost(const Location& location, void* customData) {
    DungeonGenerator* l_gen = static_cast<DungeonGenerator*>(customData);
    unsigned char point = l_gen->getByCoordinate(location.x, location.y);
    unsigned int cost = 0;
    switch (point) {
        case EMPTY:
            cost = 3;
            break;
        case WALL:
        case RESTRICTED:
        case DOOR:
            cost = 5;
            break;
        case FLOOR:
            cost = 0;
            break;
        case CORNER:
            cost = 999;
            break;
        default:
            cost = 999;
            break;
    }
    // std::cout << "Returning cost: " << cost << std::endl;
    return cost;
}

static unsigned int findNeighbours4(const Location& location,
                                    Location* neighbours, void* customData) {
    DungeonGenerator* l_gen = static_cast<DungeonGenerator*>(customData);

    unsigned int count = 0;

    if (l_gen->isValidCoordinate(location.x - 1, location.y)) {
        neighbours[count++] = Location(location.x - 1, location.y, 0);
    }
    if (l_gen->isValidCoordinate(location.x + 1, location.y)) {
        neighbours[count++] = Location(location.x + 1, location.y, 0);
    }
    if (l_gen->isValidCoordinate(location.x, location.y - 1)) {
        neighbours[count++] = Location(location.x, location.y - 1, 0);
    }
    if (l_gen->isValidCoordinate(location.x, location.y + 1)) {
        neighbours[count++] = Location(location.x, location.y + 1, 0);
    } // std::cout << "Return " << count << " neightbours" << std::endl;

    return count;
}

static unsigned int findNeighbours8(const Location& location,
                                    Location* neighbours, void* customData) {
    DungeonGenerator* l_gen = static_cast<DungeonGenerator*>(customData);
    unsigned int count = 0;

    count = findNeighbours4(location, neighbours, customData);
    if (l_gen->isValidCoordinate(location.x - 1, location.y - 1)) {
        neighbours[count++] = Location(location.x - 1, location.y - 1, 0);
    }
    if (l_gen->isValidCoordinate(location.x + 1, location.y - 1)) {
        neighbours[count++] = Location(location.x + 1, location.y - 1, 0);
    }
    if (l_gen->isValidCoordinate(location.x - 1, location.y + 1)) {
        neighbours[count++] = Location(location.x - 1, location.y + 1, 0);
    }
    if (l_gen->isValidCoordinate(location.x + 1, location.y + 1)) {
        neighbours[count++] = Location(location.x + 1, location.y + 1, 0);
    }
    // std::cout << "Return " << count << " neightbours" << std::endl;

    return count;
}

static unsigned int getDistance(const Location& start, const Location& end,
                                void* customData) {
    // std::cout << "Returning distance: " << distance << std::endl;
    int xdist = start.x - end.x;
    int ydist = start.y - end.y;
    return (abs(xdist) + abs(ydist));
}
