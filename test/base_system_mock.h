#include <game_system_interface.h>
#include <gtest/gtest.h>

class BaseSystemMock : public GameSystemInterface {
public:
    MOCK_METHOD1 (initialise, void (GameEngineInterface*));
    MOCK_METHOD1 (handleEvent, void (const Event* event));
    MOCK_METHOD0 (update, void ());

};
