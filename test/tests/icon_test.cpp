#include "../../src/windows/icon.h"
#include "../mocks/graphics_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(Icon, renderUsesIconTileset)
{
    Icon icon;
    GraphicsMock graphics;

    icon.setGraphics(&graphics);
    icon.setIcon('x');

    EXPECT_CALL(graphics, drawTile(_,_,Eq('x'),_,_)).Times(1);

    icon.render();
}