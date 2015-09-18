#include <gmock/gmock.h>
#include <game_engine_interface.h>

class GameEngineMock : public GameEngineInterface
{
public:
    MOCK_METHOD0 (initialise, void());
    MOCK_METHOD0 (tick, void());
    MOCK_METHOD0 (quit, void());
    //MOCK_METHOD0 (start, void());
    MOCK_METHOD0 (isPlayerTurn, bool());
    MOCK_METHOD0 (swapTurn, void());
    MOCK_METHOD1 (raiseEvent, void (Event* event));
    MOCK_METHOD0 (getEntities, EntityManagerInterface*());
    MOCK_METHOD1 (loadMap, void (const std::string& mapName));
    MOCK_METHOD0 (getTick, unsigned long long ());
    MOCK_METHOD0 (getWindows, WindowManagerInterface*());
    MOCK_METHOD0 (getGraphics, GraphicsInterface* ());
    MOCK_METHOD1 (addSystem, void (GameSystemInterface* a_system));

    MOCK_METHOD1 (addMessage, void  (const Message& message) );
    MOCK_METHOD2 (addMessage, void  (const MessageType&, const std::string& message)) ;
    MOCK_METHOD0 (getMessages, std::vector<Message>& () );

    MOCK_METHOD1 (setLevel, void  (unsigned int level) );
    MOCK_METHOD0 (getLevel, unsigned int  () );

    MOCK_METHOD1 (setMaxLevel, void  (unsigned int level) );
    MOCK_METHOD0 (getMaxLevel, unsigned int  () );


};
