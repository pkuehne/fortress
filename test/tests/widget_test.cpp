#include<gtest/gtest.h>
#include "../src/windows/widget.h"

using namespace ::testing;

TEST (Widget, callsCBOnKeyPressWhenSet)
{
    KeyFunc func = [](unsigned char c) { throw "Pass"; };

    Widget w;
    w.onKeyPress = func;
    EXPECT_ANY_THROW(w.keyDown('x'));
}

TEST (Widget, noThrowWhenKeyPressHandlerIsNotSet)
{
    Widget w;
    w.onKeyPress = nullptr;
    EXPECT_NO_THROW(w.keyDown('x'));
}
