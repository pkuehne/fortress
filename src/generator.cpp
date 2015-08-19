#include "generator.h"
#include "gameengine.h"
#include "algorithm.h"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

static unsigned int getDistance (unsigned int start, unsigned int end, void* customData);
static unsigned int getPathCost (unsigned int index, void* customData);
static unsigned int findNeighbours4 (unsigned int index, unsigned int* neighbours, void* customData);
static unsigned int findNeighbours8 (unsigned int index, unsigned int* neighbours, void* customData);

const char WALL     = '#';
const char CORNER   = 'C';
const char FLOOR    = '.';
const char DOOR     = 'D';
const char EMPTY    = ' ';
const char RESTRICTED = 'X';
const char ORC      = 'O';
const char UP       = '<';
const char DOWN     = '>';

void Generator::reset () {
    m_startRoom = 0;
    m_rooms.clear();

    if (m_map) {
        delete[] m_map;
        m_map = 0;
    }

}

void Generator::generate () {
    unsigned int seed = time(0) + m_engine->getLevel();
    //srand(1439294983);
    srand (seed);

    m_map = new unsigned char[m_mapHeight*m_mapWidth];
    memset (m_map, EMPTY, m_mapHeight*m_mapWidth);

    for (unsigned r = 0; r < m_roomTarget; r++) {
        while (!generateRoom ());
    }
    for (size_t ii = 0; ii < m_rooms.size()-1; ii++) {
        connectRooms (m_rooms[ii], m_rooms[ii+1]);
    }

    placeUpStair();
    placeDownStair();
    placeOrcs();
    ///loadMap ();
    createEntitiesFromMap();
    reset();
    std::cout << "Created with seed " << seed << std::endl;
}

void Generator::createEntitiesFromMap () {
    EntityId l_entity = 0;

    for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
        for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
            switch (getByCoordinate(xx, yy)) {
                case WALL:
                case CORNER:
                    l_entity = m_engine->getEntities()->createWallPrefab (xx, yy);
                    m_engine->getEntities()->getSprites()->get(l_entity)->sprite = WALL;
                    break;
                case UP:
                    m_engine->getEntities()->createStairPrefab (STAIR_UP, xx, yy);
                    if (m_engine->getLevel() == 1) m_engine->getEntities()->createPlayerPrefab (xx, yy);
                    break;
                case DOWN:
                    m_engine->getEntities()->createStairPrefab (STAIR_DOWN, xx, yy);
                    break;
                case ORC:
                    m_engine->getEntities()->createEnemyPrefab (xx, yy);
                    m_engine->getEntities()->createTilePrefab (xx, yy);
                    break;
                case FLOOR:
                    m_engine->getEntities()->createTilePrefab (xx, yy);
                    break;
                case RESTRICTED:
                    break;
                default:
                    l_entity = m_engine->getEntities()->createMarkerPrefab (xx, yy);
                    m_engine->getEntities()->getSprites()->get(l_entity)->sprite = getByCoordinate (xx, yy);
                    break;
            }
        }
    }
}

bool Generator::generateRoom () {
    unsigned int width  = rand() % 6 + 5;
    unsigned int height = rand() % 6 + 5;
    unsigned int left   = rand() % (m_mapWidth - width - 1) + 2;
    unsigned int top    = rand() % (m_mapHeight - height - 1) + 2;

    if (left+width >= m_mapWidth || left < 1 ||
        top+height >= m_mapHeight || top < 1) {
            return false;
    }

    for (unsigned int yy = top-2; yy <= top+height+1; yy++) {
        for (unsigned int xx = left-2; xx <= left+width+1; xx++) {
            if (getByCoordinate (xx, yy) != EMPTY) return false;
        }
    }

    for (unsigned int yy = top-2; yy <= top+height+1; yy++) {
        for (unsigned int xx = left-2; xx <= left+width+1; xx++) {
            if (yy < top || yy >= top+height || xx < left || xx >= left+width) {
                getByCoordinate(xx, yy) = RESTRICTED;
            } else if (yy == top || yy == top+height-1 || xx == left || xx == left+width-1) {
                if ((yy <= top+1 || yy >= top+height-2) && (xx <= left+1 || xx >= left+width-2)) {
                    getByCoordinate(xx, yy) = CORNER;
                } else {
                    getByCoordinate(xx, yy) = WALL;
                }
            } else {
                getByCoordinate(xx, yy) = FLOOR;
            }
        }
    }

    Room l_room;
    l_room.x = left;
    l_room.y = top;
    l_room.width = width;
    l_room.height = height;
    l_room.midX = left + (width/2);
    l_room.midY = top + (height/2);
    l_room.index = CoordToIndex (l_room.midX, l_room.midY);
    m_rooms.push_back (l_room);

/*
    if (!m_playerPlaced) {
        getByCoordinate(l_room.midX, l_room.midY) = 'P';
        //m_map[(top+height/2)*m_mapWidth+(left+width/2)] = 'P';
        m_playerPlaced = true;
    }
*/
    return true;
}

void Generator::connectRooms (Room& start, Room& end)
{
    Algorithm algo;
    algo.setCustomData (this);
    algo.setCostFunction (getPathCost);
    algo.setDistanceFunction (getDistance);
    algo.setNeighbourFunction (findNeighbours4);
    algo.setNumNeighbours (4);

    PathVector l_path;
    algo.findPath (start.index, end.index, l_path);
    //std::cout << "Found a " << l_path.size() << " tile corridor" << std::endl;

    for (size_t ii = 0; ii < l_path.size(); ii++) {
        unsigned char& tile = getByIndex(l_path[ii]);
        unsigned int x, y;
        IndexToCoord (l_path[ii], x, y);

        // Create tiles and doors
        if (tile == WALL || tile == DOOR) {
            tile = DOOR;
        } else {
            tile = FLOOR;
        }
    }

    for (size_t ii = 0; ii < l_path.size(); ii++) {
        // Wall of neighbours if necessary
        unsigned int neighbours[8] = {0};
        size_t count = findNeighbours8 (l_path[ii], neighbours, this);
        for (size_t ii = 0; ii < count; ii++) {
            unsigned char& adj = getByIndex (neighbours[ii]);
            if (adj == EMPTY || adj == RESTRICTED) {
                adj = WALL;
            }
        }
    }
}

void Generator::placeUpStair()
{
    m_startRoom = rand() % m_rooms.size();
    getByCoordinate (m_rooms[m_startRoom].midX, m_rooms[m_startRoom].midY) = UP;
}

void Generator::placeDownStair()
{
    if (m_rooms.size() < 2) return; // No point
    unsigned int room = m_startRoom;
    while (room == m_startRoom) room = rand() % m_rooms.size();
    getByCoordinate (m_rooms[room].midX, m_rooms[room].midY) = DOWN;
}

void Generator::placeOrcs()
{
    if (m_rooms.size() < 2) return; // No point

    unsigned int numOrcs = rand() % (m_rooms.size() -1) + 1;
    for (size_t ii = 0; ii < numOrcs; ii++) {
        unsigned int room = 0;
        while (1) {
            room = rand() % m_rooms.size();
            if (m_startRoom == room) continue;
            unsigned int x, y;
            x = m_rooms[room].x + (rand() % m_rooms[room].width-2) + 1;
            y = m_rooms[room].y + (rand() % m_rooms[room].height-2) + 1;
            unsigned char& tile = getByCoordinate (x, y);
            if (tile == FLOOR) {
                tile = ORC;
                break;
            }
        }
    }
}

void Generator::loadMap ()
{
    std::ifstream file ("../maps/test.map");
    char line[m_mapWidth];
    int lineCnt = 0;
    do {
        memset (line, EMPTY, sizeof (line));
        file.getline (line, sizeof (line));
        memcpy (m_map+(m_mapWidth*lineCnt), line, sizeof(line));
        lineCnt++;
    } while (file.gcount() > 0);
}

unsigned int getPathCost (unsigned int index, void* customData)
{
    Generator* l_gen = static_cast<Generator*> (customData);
    unsigned char point = l_gen->getByIndex(index);
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
    //std::cout << "Returning cost: " << cost << std::endl;
    return cost;
}

unsigned int findNeighbours4 (unsigned int index, unsigned int* neighbours, void* customData)
{
    Generator* l_gen = static_cast<Generator*> (customData);
    unsigned int indexX, indexY;
    l_gen->IndexToCoord (index, indexX, indexY);

    unsigned int count = 0;

    if (l_gen->isValidCoordinate (indexX-1, indexY))
        neighbours[count++] = l_gen->CoordToIndex (indexX-1, indexY);
    if (l_gen->isValidCoordinate (indexX+1, indexY))
        neighbours[count++] = l_gen->CoordToIndex (indexX+1, indexY);
    if (l_gen->isValidCoordinate (indexX, indexY-1))
        neighbours[count++] = l_gen->CoordToIndex (indexX, indexY-1);
    if (l_gen->isValidCoordinate (indexX, indexY+1))
        neighbours[count++] = l_gen->CoordToIndex (indexX, indexY+1);
    //std::cout << "Return " << count << " neightbours" << std::endl;

    return count;
}

unsigned int findNeighbours8 (unsigned int index, unsigned int* neighbours, void* customData)
{
    Generator* l_gen = static_cast<Generator*> (customData);
    unsigned int indexX, indexY;
    l_gen->IndexToCoord (index, indexX, indexY);

    unsigned int count = 0;

    if (l_gen->isValidCoordinate (indexX-1, indexY))
        neighbours[count++] = l_gen->CoordToIndex (indexX-1, indexY);
    if (l_gen->isValidCoordinate (indexX+1, indexY))
        neighbours[count++] = l_gen->CoordToIndex (indexX+1, indexY);
    if (l_gen->isValidCoordinate (indexX, indexY-1))
        neighbours[count++] = l_gen->CoordToIndex (indexX, indexY-1);
    if (l_gen->isValidCoordinate (indexX, indexY+1))
        neighbours[count++] = l_gen->CoordToIndex (indexX, indexY+1);
    if (l_gen->isValidCoordinate (indexX-1, indexY-1))
        neighbours[count++] = l_gen->CoordToIndex (indexX-1, indexY-1);
    if (l_gen->isValidCoordinate (indexX+1, indexY-1))
        neighbours[count++] = l_gen->CoordToIndex (indexX+1, indexY-1);
    if (l_gen->isValidCoordinate (indexX-1, indexY+1))
        neighbours[count++] = l_gen->CoordToIndex (indexX-1, indexY+1);
    if (l_gen->isValidCoordinate (indexX+1, indexY+1))
        neighbours[count++] = l_gen->CoordToIndex (indexX+1, indexY+1);

    //std::cout << "Return " << count << " neightbours" << std::endl;

    return count;
}

unsigned int getDistance (unsigned int start, unsigned int end, void* customData)
{
    Generator* l_gen = static_cast<Generator*> (customData);
    unsigned int startX, startY;
    unsigned int endX, endY;
    unsigned int distance = 0;
    l_gen->IndexToCoord (start, startX, startY);
    l_gen->IndexToCoord (end, endX, endY);
    distance = (abs (startX-endX)+abs(startY-endY));
    //std::cout << "Returning distance: " << distance << std::endl;
    return distance;
}
