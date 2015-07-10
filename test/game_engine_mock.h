#include <gmock/gmock.h>
#include <game_engine_interface.h>

class GameEngineMock : public GameEngineInterface
{
public:
    MOCK_METHOD0 (initialise, void());
    MOCK_METHOD0 (tick, void());
    MOCK_METHOD0 (start, void());
    MOCK_METHOD0 (isPaused, bool&());
    MOCK_METHOD1 (raiseEvent, void (Event* event));
    MOCK_METHOD0 (getEntities, EntityManager&());
    MOCK_METHOD1 (loadMap, void (const std::string& mapName));
    MOCK_METHOD0 (getTick, unsigned long long ());
    MOCK_METHOD0 (getWindows, WindowManager*());
    MOCK_METHOD0 (getGraphics, GraphicsInterface* ());
};
