#include "map_manager.h"
#include <gmock/gmock.h>

class MapManagerMock : public MapManager 
{
public:
    MOCK_METHOD1 (getTile, Tile& (const Location& location));
};
