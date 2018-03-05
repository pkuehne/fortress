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

TEST(Frame, realignWidgetSubtractsBorderWidth)
{
    Frame frame;
    WidgetMock mock;

    frame.setBorder(true);
    frame.addChild(&mock);
    unsigned int width = 5;
    unsigned int height = 7;

    EXPECT_CALL(mock, realignWidget(Eq(width-2),Eq(height-2)));

    frame.realignWidget(width, height);
}

TEST(Frame, realignWidgetSubtractsMargin)
{
    Frame frame;
    WidgetMock mock;

    frame.setMargin(10);
    frame.addChild(&mock);
    unsigned int width = 5;
    unsigned int height = 7;

    EXPECT_CALL(mock, realignWidget(Eq(width-20),Eq(height-20)));

    frame.realignWidget(width, height);
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

TEST(Frame, EnablingBorderIncreasesWindowOffsetForChildren)
{
    Frame frame;
    WidgetMock mock;
    frame.setBorder(true);
    frame.addChild(&mock);
    unsigned int x = 5;
    unsigned int y = 7;

    EXPECT_CALL(mock, setWindowOffsets(Eq(x + 1), Eq(y + 1)));

    frame.setWindowOffsets(x, y);
}

TEST(Frame, WindoOffsetIncreasesByMarginSize)
{
    Frame frame;
    WidgetMock mock;
    frame.setMargin(10);
    frame.addChild(&mock);
    unsigned int x = 5;
    unsigned int y = 7;

    EXPECT_CALL(mock, setWindowOffsets(Eq(x + 10), Eq(y + 10)));

    frame.setWindowOffsets(x, y);
}