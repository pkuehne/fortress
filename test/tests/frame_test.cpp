#include <gtest/gtest.h>

#include "../../src/windows/frame.h"
#include "../mocks/widget_mock.h"

using namespace ::testing;

TEST(Frame, setWinowOffsetsPassedDownToChildren)
{
    Frame frame;
    WidgetMock mock;

    frame.addChild(&mock);
    unsigned int x = 5;
    unsigned int y = 7;

    EXPECT_CALL(mock, setWindowOffsets(Eq(x), Eq(y)));

    frame.setWindowOffsets(x, y);
}

TEST(Frame, realignWidgetPassedDownToChildren)
{
    Frame frame;
    WidgetMock mock;

    frame.addChild(&mock);
    unsigned int x = 5;
    unsigned int y = 7;

    EXPECT_CALL(mock, realignWidget(Eq(x-2), Eq(y-2)));

    frame.realignWidget(x, y);
}

TEST(Frame, renderPassedDownToChildren)
{
    Frame frame;
    WidgetMock mock;

    frame.addChild(&mock);

    EXPECT_CALL(mock, render());

    frame.render();
}

TEST(Frame, keyPressPassedDownToChildren)
{
    Frame frame;
    WidgetMock mock;

    frame.addChild(&mock);
    unsigned char key = '@';

    EXPECT_CALL(mock, keyPress(Eq(key)));

    frame.keyPress(key);
}