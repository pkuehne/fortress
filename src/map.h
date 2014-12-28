#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include "tile.h"

class Map {
    public:
        Map();
        ~Map();

        void loadMap ();
        void resizeMap (int width, int height);
        const Tile& getTile (int x, int y) const;
        const Tile& getTile (int index) const;

        Tile& getTile (int x, int y);
        Tile& getTile (int index);
        
        void setMapSize (int width, int height) { s_mapWidth = width; s_mapHeight = height; }
        int getMapWidth() const { return s_mapWidth; }
        int getMapHeight() const { return s_mapHeight; }
        int getMapSize() const { return getMapWidth()*getMapHeight(); }

        void getNeighbours (int index, int neighbours[4]) const;

        static int getIndex (int x, int y);
        static int getxAdj (int dir) { return Map::xAdj[dir]; }
        static int getyAdj (int dir) { return Map::yAdj[dir]; }
        static int getDirections () { return Map::dir; }

        static const int xAdj[];
        static const int yAdj[];
        static const int dir;
        static int s_mapHeight;
        static int s_mapWidth;

    private:
        Tile* m_tiles;
};
#endif
