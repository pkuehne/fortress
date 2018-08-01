#include "../../src/widgets/text_block.h"
#include <gtest/gtest.h>

TEST(TextBlock, fitsAllTextOnOneLineWhenTextSizeLessThanWidth) {
    TextBlock block;
    block.setWidth(6);
    block.setText("12345");

    EXPECT_EQ(block.getHeight(), 1);
}

TEST(TextBlock, TwoWordsSplitOverTwoLinesIfTheyDontFit) {
    TextBlock block;
    block.setWidth(6);
    block.setText("12345 12345");

    EXPECT_EQ(block.getHeight(), 2);
}

TEST(TextBlock, WhenWidthIsChangedTextIsReWrapped) {
    TextBlock block;
    block.setWidth(6);
    block.setText("12345 12345 67890 67890");

    EXPECT_EQ(block.getHeight(), 4);

    block.setWidth(12);
    EXPECT_EQ(block.getHeight(), 2);
}
