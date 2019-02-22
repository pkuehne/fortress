#include "../../src/widgets/progress_bar.h"
#include "../mocks/graphics_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(ProgressBar, 100PercentRendersProgressBarWidth) {
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    ProgressBar bar;
    bar.setGraphics(graphics);
    bar.setWidth(10);
    bar.setMaxValue(10);
    bar.setValue(10);

    EXPECT_CALL(*graphics, drawTile(_, _, _, _, _)).Times(bar.getWidth());

    bar.render();
}

TEST(ProgressBar, 0PercentRendersNothing) {
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    ProgressBar bar;
    bar.setGraphics(graphics);
    bar.setWidth(10);
    bar.setMaxValue(10);
    bar.setValue(0);

    EXPECT_CALL(*graphics, drawTile(_, _, _, _, _)).Times(0);

    bar.render();
}

TEST(ProgressBar, 50PercentRendersHalf) {
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    ProgressBar bar;
    bar.setGraphics(graphics);
    bar.setWidth(10);
    bar.setMaxValue(100);
    bar.setValue(50);

    EXPECT_CALL(*graphics, drawTile(_, _, _, _, _)).Times(5);

    bar.render();
}

TEST(ProgressBar, ValueAboveMaxOnlyRendersMax) {
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    ProgressBar bar;
    bar.setGraphics(graphics);
    bar.setWidth(10);
    bar.setMaxValue(100);
    bar.setValue(150);

    EXPECT_CALL(*graphics, drawTile(_, _, _, _, _)).Times(10);

    bar.render();
}

TEST(ProgressBar, DrawsAlongTheHorizontalAxis) {
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    ProgressBar bar;
    bar.setGraphics(graphics);
    bar.setWidth(5);
    bar.setMaxValue(5);
    bar.setValue(5);

    EXPECT_CALL(*graphics, drawTile(_, 0, _, _, _)).Times(1);
    EXPECT_CALL(*graphics, drawTile(_, 1, _, _, _)).Times(1);
    EXPECT_CALL(*graphics, drawTile(_, 2, _, _, _)).Times(1);
    EXPECT_CALL(*graphics, drawTile(_, 3, _, _, _)).Times(1);
    EXPECT_CALL(*graphics, drawTile(_, 4, _, _, _)).Times(1);

    bar.render();
}