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
