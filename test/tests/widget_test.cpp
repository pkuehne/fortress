#include<gtest/gtest.h>
#include "../../src/windows/widget.h"
#include "../mocks/graphics_mock.h"

using namespace ::testing;

TEST(Widget, drawBorderUsesWidgetWidthAndHeightWhenSetToZero)
{
    Widget w;
    GraphicsMock graphics;
    w.setGraphics(&graphics);

    unsigned int x = 5;
    unsigned int y = 7;
    unsigned int width = 10;
    unsigned int height = 20;

    w.setWindowOffsets(x, y);
    w.setWidth(width);
    w.setHeight(height);
    w.realignWidget(100, 200);

    EXPECT_CALL(graphics, drawBorder(Eq(y), Eq(x), Eq(height-2), Eq(width-2)));

    w.drawBorder();
}