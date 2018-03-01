#include <gtest/gtest.h>
#include "../../src/windows/numeric_entry.h"
#include "../mocks/graphics_mock.h"

using namespace ::testing;

TEST(NumericEntry, drawsNumber)
{
    GraphicsMock graphics;
    NumericEntry num;

    const char* text = nullptr;
    EXPECT_CALL(graphics, drawString(_,_,_,_,_)).WillOnce(SaveArg<2>(&text));

    num.setGraphics(&graphics);
    num.setNumber(23);

    num.render();

    EXPECT_STREQ("23", text);
}

TEST(NumericEntry, PlusKeyIncreases)
{
    NumericEntry num;
    num.setNumber(23);

    num.keyDown('+');

    EXPECT_EQ(num.getNumber(), 24);
}

TEST(NumericEntry, MinusKeyIncreases)
{
    NumericEntry num;
    num.setNumber(23);

    num.keyDown('-');

    EXPECT_EQ(num.getNumber(), 22);
}