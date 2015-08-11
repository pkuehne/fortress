#include "generator.h"
#include "gameengine.h"
#include "algorithm.h"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

static unsigned int getDistance (unsigned int start, unsigned int end, void* customData);
static unsigned int getPathCost (unsigned char point, void* customData);
static unsigned int findNeighbours (unsigned int index, unsigned int* neighbours, void* customData);

void Generator::generate () {
    srand(time(0));

    unsigned int x, y;
    IndexToCoord (202, x, y);
    std::cout << "x = 2, y = 4, index = " << CoordToIndex (2, 4) << std::endl;
    std::cout << "index = 202, x = " << x << ", y = " << y << std::endl;

    m_map = new unsigned char[m_mapHeight*m_mapWidth];
    memset (m_map, ' ', m_mapHeight*m_mapWidth);

    for (unsigned r = 0; r < m_roomTarget; r++) {
        while (!generateRoom ());
    }
    for (size_t ii = 0; ii < 1 || ii < m_rooms.size()-1; ii++) {
        connectRooms (m_rooms[ii], m_rooms[ii+1]);
    }
    ///loadMap ();
    createEntitiesFromMap();
}

void Generator::createEntitiesFromMap () {
    for (unsigned int yy = 0; yy < m_mapHeight; yy++) {
        for (unsigned int xx = 0; xx < m_mapWidth; xx++) {
            switch (getByCoordinate(xx, yy)) {
                case 'W':
                //case 'C':
                    m_engine->getEntities()->createWallPrefab (xx, yy);
                    break;
                case 'P':
                    m_engine->getEntities()->createPlayerPrefab (xx, yy);
                    m_engine->getEntities()->createTilePrefab (xx, yy);
                    break;
                case 'O':
                    m_engine->getEntities()->createEnemyPrefab (xx, yy);
                    m_engine->getEntities()->createTilePrefab (xx, yy);
                    break;
                case '.':
                    m_engine->getEntities()->createTilePrefab (xx, yy);
                    break;
                default:
                    EntityId l_entity = m_engine->getEntities()->createMarkerPrefab (xx, yy);
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

    for (unsigned int yy = top-1; yy <= top+height; yy++) {
        for (unsigned int xx = left-1; xx <= left+width; xx++) {
            if (getByCoordinate (xx, yy) != ' ') return false;
        }
    }

    for (unsigned int yy = top-1; yy <= top+height; yy++) {
        for (unsigned int xx = left-1; xx <= left+width; xx++) {
            if (yy == top-1 || yy == top+height || xx == left-1 || xx == left+width) {
                getByCoordinate(xx, yy) = '1';
            } else if (yy == top || yy == top+height-1 || xx == left || xx == left+width-1) {
                if ((yy <= top+1 || yy >= top+height-2) && (xx <= left+1 || xx >= left+width-2)) {
                    getByCoordinate(xx, yy) = 'C';
                } else {
                    getByCoordinate(xx, yy) = 'W';
                }
            } else {
                getByCoordinate(xx, yy) = '.';
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

    if (!m_playerPlaced) {
        getByCoordinate(l_room.midX, l_room.midY) = 'P';
        //m_map[(top+height/2)*m_mapWidth+(left+width/2)] = 'P';
        m_playerPlaced = true;
    }

    return true;
}

void Generator::connectRooms (Room& start, Room& end)
{
    Algorithm algo;
    algo.setCustomData (this);
    algo.setCostFunction (getPathCost);
    algo.setDistanceFunction (getDistance);
    algo.setNeighbourFunction (findNeighbours);
    algo.setNumNeighbours (4);

    PathVector l_path;
    algo.findPath (start.index, end.index, l_path);
    std::cout << "Found a " << l_path.size() << " tile corridor" << std::endl;
    for (size_t ii = 0; ii < l_path.size(); ii++) {
        getByIndex(l_path[ii]) = '#';
    }
}

void Generator::loadMap ()
{
    std::ifstream file ("../maps/test.map");
    char line[m_mapWidth];
    int lineCnt = 0;
    do {
        memset (line, ' ', sizeof (line));
        file.getline (line, sizeof (line));
        memcpy (m_map+(m_mapWidth*lineCnt), line, sizeof(line));
        lineCnt++;
    } while (file.gcount() > 0);
}

unsigned int getPathCost (unsigned char point, void* customData)
{
    switch (point) {
        case ' ':
            return 2;
        case 'W':
        case '1':
            return 5;
        case '.':
            return 0;
        case 'C':
            return 999;
        default:
            return 10;
    }
}

unsigned int findNeighbours (unsigned int index, unsigned int* neighbours, void* customData)
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

    return count;
}

unsigned int getDistance (unsigned int start, unsigned int end, void* customData)
{
    Generator* l_gen = static_cast<Generator*> (customData);
    unsigned int startX, startY;
    unsigned int endX, endY;
    l_gen->IndexToCoord (start, startX, startY);
    l_gen->IndexToCoord (end, endX, endY);
    return (abs (startX-endX)+abs(startY-endY));
}
