#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "tile.h"

const int MAP_WIDTH = 65;
const int MAP_HEIGHT= 65;

class Map {
    public:
        Map();
        ~Map();
        const Tile& getTile (int x, int y) const;
        const Tile& getTile (int index) const;

        Tile& getTile (int x, int y);
        Tile& getTile (int index);

        int getMaxWidth() const { return MAP_WIDTH; }
        int getMaxHeight() const { return MAP_HEIGHT; }
        int getMapSize() const { return MAP_WIDTH*MAP_HEIGHT; }

        void getNeighbours (int index, int neighbours[4]);

        static int getIndex (int x, int y);
        static int getxAdj (int dir) { return Map::xAdj[dir]; }
        static int getyAdj (int dir) { return Map::yAdj[dir]; }
        static int getDirections () { return Map::dir; }

    private:
        Tile* m_tiles;

        static const int xAdj[];
        static const int yAdj[];
        static const int dir;
};
#endif
