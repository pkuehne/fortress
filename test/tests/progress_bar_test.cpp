#include <gtest/gtest.h>
#include "../../src/windows/progress_bar.h"
#include "../mocks/graphics_mock.h"

using namespace ::testing;

TEST(ProgressBar, 100PercentRendersProgressBarWidth)
{
    GraphicsMock graphics;

    ProgressBar bar;
    bar.setGraphics(&graphics);
    bar.setWidth(10);
    bar.setMaxValue(10);
    bar.setValue(10);

    EXPECT_CALL(graphics, drawString(_, _, _, _, _)).Times(bar.getWidth());

    bar.render();
}

TEST(ProgressBar, 0PercentRendersNothing)
{
    GraphicsMock graphics;

    ProgressBar bar;
    bar.setGraphics(&graphics);
    bar.setWidth(10);
    bar.setMaxValue(10);
    bar.setValue(0);

    EXPECT_CALL(graphics, drawString(_, _, _, _, _)).Times(0);

    bar.render();
}

TEST(ProgressBar, 50PercentRendersHalf)
{
    GraphicsMock graphics;

    ProgressBar bar;
    bar.setGraphics(&graphics);
    bar.setWidth(10);
    bar.setMaxValue(100);
    bar.setValue(50);

    EXPECT_CALL(graphics, drawString(_, _, _, _, _)).Times(5);

    bar.render();
}

TEST(ProgressBar, ValueAboveMaxOnlyRendersMax)
{
    GraphicsMock graphics;

    ProgressBar bar;
    bar.setGraphics(&graphics);
    bar.setWidth(10);
    bar.setMaxValue(100);
    bar.setValue(150);

    EXPECT_CALL(graphics, drawString(_, _, _, _, _)).Times(10);

    bar.render();
}