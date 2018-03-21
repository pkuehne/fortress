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

TEST(Frame, SetsOwnPositionAsWindowOffset)
{
    Frame frame;
    WidgetMock mock;

    unsigned int height = 20;
    unsigned int width = 30;


    frame.setWindowOffsets(0, 0);
    frame.setX(10);
    frame.setHorizontalAlign(Widget::HorizontalAlign::Right);
    frame.addChild(&mock);

    EXPECT_CALL(mock, setWindowOffsets(Eq(20), Eq(0)));
    frame.realignWidget(width, height);

    EXPECT_EQ(frame.getXPos(), width - frame.getX());
}

TEST(Frame, SettingWindowOffsetOnChildrenIncludesBorderAndMargin)
{
    Frame frame;
    WidgetMock mock;

    unsigned int height = 20;
    unsigned int width = 30;


    frame.setWindowOffsets(0, 0);
    frame.setX(10);
    frame.setHorizontalAlign(Widget::HorizontalAlign::Right);
    frame.setBorder();
    frame.setMargin();
    frame.addChild(&mock);

    EXPECT_CALL(mock, setWindowOffsets(Eq(22), Eq(2)));
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

TEST(Frame, MergeBordersIgnoresOffsetsForOtherFrames)
{
    Frame frame;
    Frame subFrame;

    frame.setBorder();
    frame.setMargin();
    frame.setMergeBorders();
    frame.addChild(&subFrame);

    unsigned int x = 5;
    unsigned int y = 7;

    frame.setWindowOffsets(x, y);
    frame.realignWidget(20, 20);

    EXPECT_EQ(subFrame.getXPos(), x);
    EXPECT_EQ(subFrame.getYPos(), y);
}