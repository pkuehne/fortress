#include <gtest/gtest.h>

#include "../../src/windows/frame.h"
#include "../mocks/widget_mock.h"

using namespace ::testing;

TEST(Frame, realignCalledForChildren) {
    unsigned int x = 5;
    unsigned int y = 7;
    unsigned int width = 100;
    unsigned int height = 200;

    Frame frame;
    WidgetMock mock;
    frame.addChild(&mock);
    frame.setWidth(width);
    frame.setHeight(height);

    EXPECT_CALL(mock, realign(Eq(x), Eq(y), Eq(width), Eq(height)));

    frame.realign(x, y, width, height);
}

TEST(Frame, realignAccountsForBorderWidth) {
    unsigned int x = 5;
    unsigned int y = 7;
    unsigned int width = 100;
    unsigned int height = 200;

    Frame frame;
    WidgetMock mock;

    frame.setBorder();
    frame.addChild(&mock);
    frame.setWidth(width);
    frame.setHeight(height);

    EXPECT_CALL(mock,
                realign(Eq(x + 1), Eq(y + 1), Eq(width - 2), Eq(height - 2)));

    frame.realign(x, y, width, height);
}

TEST(Frame, realignAccountsForMargin) {
    unsigned int x = 5;
    unsigned int y = 7;
    unsigned int width = 100;
    unsigned int height = 200;

    Frame frame;
    WidgetMock mock;

    frame.setMargin();
    frame.addChild(&mock);
    frame.setWidth(width);
    frame.setHeight(height);

    EXPECT_CALL(mock,
                realign(Eq(x + 1), Eq(y + 1), Eq(width - 2), Eq(height - 2)));

    frame.realign(x, y, width, height);
}

TEST(Frame, renderPassedDownToChildren) {
    Frame frame;
    WidgetMock mock;

    frame.addChild(&mock);

    EXPECT_CALL(mock, render());

    frame.render();
}

TEST(Frame, keyPressPassedDownToChildren) {
    Frame frame;
    WidgetMock mock;

    frame.addChild(&mock);
    unsigned char key = '@';

    EXPECT_CALL(mock, keyPress(Eq(key)));

    frame.keyPress(key);
}

TEST(Frame, MergeBordersIgnoresOffsetsForOtherFrames) {
    Frame frame;
    Frame subFrame;

    frame.setBorder();
    frame.setMargin();
    frame.setMergeBorders();
    frame.addChild(&subFrame);

    unsigned int x = 5;
    unsigned int y = 7;
    unsigned int width = 100;
    unsigned int height = 200;

    frame.realign(x, y, width, height);
    EXPECT_EQ(subFrame.getXPos(), frame.getXPos());
    EXPECT_EQ(subFrame.getYPos(), frame.getYPos());
}