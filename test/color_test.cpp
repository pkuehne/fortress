#include <gtest/gtest.h>
#include <color.h>

TEST (Color, DefaultConstructor)
{
    Color color;

    EXPECT_EQ(0, color.Red());
    EXPECT_EQ(0, color.Green());
    EXPECT_EQ(0, color.Blue());
}

TEST (Color, RGBConstructor)
{
    int red     = 10;
    int green   = 20;
    int blue    = 30;
    Color color (red, green, blue);

    EXPECT_EQ(red, color.Red());
    EXPECT_EQ(green, color.Green());
    EXPECT_EQ(blue, color.Blue());
}

TEST (Color, EnumConstructor)
{
    Color color (RED);

    EXPECT_EQ(1, color.Red());
    EXPECT_EQ(0, color.Green());
    EXPECT_EQ(0, color.Blue());
}

TEST (Color, EnumColorsAreCorrect)
{
    Color red (RED);
    Color green (GREEN);
    Color blue (BLUE);
    Color white (WHITE);
    Color black (BLACK);
    Color grey (GREY);

    EXPECT_EQ(1, red.Red());
    EXPECT_EQ(0, red.Green());
    EXPECT_EQ(0, red.Blue());

    EXPECT_EQ(0, green.Red());
    EXPECT_EQ(1, green.Green());
    EXPECT_EQ(0, green.Blue());

    EXPECT_EQ(0, blue.Red());
    EXPECT_EQ(0, blue.Green());
    EXPECT_EQ(1, blue.Blue());

    EXPECT_EQ(1, white.Red());
    EXPECT_EQ(1, white.Green());
    EXPECT_EQ(1, white.Blue());

    EXPECT_EQ(0, black.Red());
    EXPECT_EQ(0, black.Green());
    EXPECT_EQ(0, black.Blue());

    EXPECT_EQ(0.5, grey.Red());
    EXPECT_EQ(0.5, grey.Green());
    EXPECT_EQ(0.5, grey.Blue());

}
