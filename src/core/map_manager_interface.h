#ifndef MAP_MANAGER_INTERFACE_H
#define MAP_MANAGER_INTERFACE_H

#include "tile.h"
#include "utility.h"

class GameEngineInterface;

class MapManagerInterface {
public:
    virtual ~MapManagerInterface() { }

    virtual Tile& getTile (unsigned int x, unsigned int y, unsigned int z) = 0;
    virtual Tile& getTile (const Location& location) = 0;
    virtual Tile& getTile (unsigned int index) = 0;

    virtual int map2index (unsigned int x, unsigned int y, unsigned int z) = 0;
    virtual int map2index (const Location& location) = 0;
    virtual void index2map (unsigned int index, unsigned int& x, unsigned int& y, unsigned int& z) = 0;
    virtual void index2map (unsigned int index, Location& loc) = 0;

    virtual bool isValidTile (unsigned int x, unsigned int y, unsigned int z) = 0;
    virtual bool isValidTile (unsigned int index) = 0;

    virtual unsigned int getMapHeight() = 0;
    virtual unsigned int getMapWidth() = 0;
    virtual unsigned int getMapDepth() = 0;

    virtual void resetMap (unsigned int area, unsigned int width, unsigned int height, unsigned int depth) = 0;

    virtual unsigned int getArea () = 0;
    virtual void setArea (unsigned int area) = 0;
    virtual unsigned int  getAreas() = 0;

    virtual Location location (const Location&, Direction direction) = 0;
    virtual EntityHolder findEntitiesAt (const Location& location) = 0;
    virtual EntityHolder findEntitiesNear (const Location& location, unsigned int radius) = 0;
};

#endif
