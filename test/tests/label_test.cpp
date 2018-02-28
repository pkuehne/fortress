#include <gtest/gtest.h>
#include "../../src/windows/label.h"
#include "../../src/core/utility.h"

using namespace ::testing;

TEST(LabelTest, pressingCommandCharInvokesCallback)
{
    Label l;
    l.setText("foo");
    l.setCommandChar(1);
    l.setCommandCharCallback([](Label *b) { throw "Selected"; });

    EXPECT_ANY_THROW(l.keyPress('f'));
}

TEST(LabelTest, pressingAnythingButCommandCharDoesntInvokeCallback)
{
    Label l;
    l.setText("foo");
    l.setCommandChar(1);
    l.setCommandCharCallback([](Label *b) { throw "Selected"; });

    EXPECT_NO_THROW(l.keyPress('o'));
}

TEST(LabelTest, pressingCommandCharDoesNotInvokeCallbackIfNotSensitive)
{
    Label l;
    l.setText("foo");
    l.setCommandChar(1);
    l.setCommandCharCallback([](Label *b) { throw "Selected"; });
    l.setSensitive(false);

    EXPECT_NO_THROW(l.keyPress('f'));
}

TEST(LabelTest, pressingCommandCharInvokesCallbackIfNotVisible)
{
    Label l;
    l.setText("foo");
    l.setCommandChar(1);
    l.setCommandCharCallback([](Label *b) { throw "Selected"; });
    l.setVisible(false);

    EXPECT_ANY_THROW(l.keyPress('f'));
}