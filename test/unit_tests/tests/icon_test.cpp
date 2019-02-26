#include "../../src/widgets/icon.h"
#include "../mocks/graphics_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(Icon, renderUsesIconTileset) {
    Icon icon;
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    icon.setGraphics(graphics);
    icon.setIcon('F');

    EXPECT_CALL(*graphics, drawTile(_, _, Eq('F'), _, _)).Times(1);

    icon.render();
}