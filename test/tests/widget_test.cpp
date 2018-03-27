#include <gtest/gtest.h>
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

    w.setWidth(width);
    w.setHeight(height);
    w.realign(x, y, width, height);

    EXPECT_CALL(graphics, drawBorder(Eq(y), Eq(x), Eq(height - 2), Eq(width - 2)));

    w.drawBorder();
}

TEST(Widget, realignVerticalTopSetsRelativePlusOrigin)
{
    Widget w;
    w.setY(5);
    w.setVerticalAlign(Widget::VerticalAlign::Top);

    w.realign(0, 10, 0, 100);

    EXPECT_EQ(w.getYPos(), 15);
}

TEST(Widget, realignVerticalCentreSetsMiddleOfWidgetOnMiddleOfScreen)
{
    Widget w;
    w.setY(0);
    w.setHeight(6);
    w.setVerticalAlign(Widget::VerticalAlign::Centre);

    w.realign(0, 10, 0, 100);

    EXPECT_EQ(w.getYPos(), 57);
}

TEST(Widget, realignVerticalBottomSetsTopOfWidgetItsHeightAwayFromBottom)
{
    Widget w;
    w.setY(0);
    w.setHeight(6);
    w.setVerticalAlign(Widget::VerticalAlign::Bottom);

    w.realign(0, 10, 0, 100);

    EXPECT_EQ(w.getYPos(), 104);
}

TEST(Widget, realignHorizontalTopSetsRelativePlusOrigin)
{
    Widget w;
    w.setX(5);
    w.setHorizontalAlign(Widget::HorizontalAlign::Left);

    w.realign(10, 0, 100, 0);

    EXPECT_EQ(w.getXPos(), 15);
}

TEST(Widget, realignHorizontalCentreSetsMiddleOfWidgetOnMiddleOfScreen)
{
    Widget w;
    w.setX(0);
    w.setWidth(6);
    w.setHorizontalAlign(Widget::HorizontalAlign::Centre);

    w.realign(10, 0, 100, 0);

    EXPECT_EQ(w.getXPos(), 57);
}

TEST(Widget, realignHorizontalBottomSetsLeftOfWidgetItsWidthAwayFromRight)
{
    Widget w;
    w.setX(0);
    w.setWidth(6);
    w.setHorizontalAlign(Widget::HorizontalAlign::Right);

    w.realign(10, 0, 100, 0);

    EXPECT_EQ(w.getXPos(), 104);
}