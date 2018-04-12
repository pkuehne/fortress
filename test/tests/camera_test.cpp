// #include <gtest/gtest.h>
// #include <gmock/gmock.h>
// #include "../../src/windows/camera.h"
// #include "../mocks/game_state_mock.h"
// #include "../mocks/graphics_mock.h"

// using namespace ::testing;
// class CameraTest : public ::testing::Test
// {
// public:
//     void SetUp() { 
//         camera.setGraphics(&graphics);
//         camera.setGameState(&state);
//     }
//     void TearDown() { }

//     GraphicsMock    graphics;
//     GameStateMock   state;
//     Camera          camera;
// };

// DISABLED_TEST_F (CameraTest, renderSpritesCorrectlyOffsetsMap)
// {
//     camera.viewport().height = 1;
//     camera.viewport().width  = 1;

//     int x = 5;
//     int y = 6;
//     int z = 7;

//     Location loc (x, y, z);
//     camera.setMapOffset (x, y, z);

//     EXPECT_CALL (state, isValidTile(Eq(loc))).WillOnce(Return(false));
//     camera.renderSprites();
// }

// DISABLED_TEST_F (CameraTest, enabledFalseStopsRenderingFromBeingDone)
// {
//     camera.enabled() = false;
//     camera.viewport().height = 1;
//     camera.viewport().width  = 1;

//     EXPECT_CALL (state, isValidTile(_)).Times(0);
//     camera.render();
// }
