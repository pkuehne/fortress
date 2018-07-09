#include "../../src/core/utility.h"
#include "../../src/windows/text_entry.h"

#include "../mocks/graphics_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(TextEntry, CanSetAndGetText) {
    TextEntry entry;
    std::string testText("Fooo");

    entry.setText(testText);

    EXPECT_EQ(testText, entry.getText());
}

TEST(TextEntry, HasBlinkingCursor) {
    GraphicsMock graphics;
    TextEntry entry;
    entry.setGraphics(&graphics);

    EXPECT_CALL(graphics, drawString(Eq(0), Eq(0), StrEq("_"), _, _)).Times(1);

    // Run render twice, underscore should render only once!
    entry.render();
    entry.render();
}

TEST(TextEntry, renderShowsTextPlusCursor) {
    GraphicsMock graphics;
    TextEntry entry;
    entry.setGraphics(&graphics);
    entry.setText(std::string("Foo"));
    entry.setSensitive(false);

    EXPECT_CALL(graphics, drawString(Eq(0), Eq(0), StrEq("Foo"), _, _))
        .Times(2);
    EXPECT_CALL(graphics, drawString(Eq(0), Eq(3), StrEq("_"), _, _)).Times(0);

    // Run render twice, underscore should not!
    entry.render();
    entry.render();
}

TEST(TextEntry, renderShowsTextButNoCursorWhenNotSensitive) {
    GraphicsMock graphics;
    TextEntry entry;
    entry.setGraphics(&graphics);
    entry.setText(std::string("Foo"));

    EXPECT_CALL(graphics, drawString(Eq(0), Eq(0), StrEq("Foo"), _, _))
        .Times(2);
    EXPECT_CALL(graphics, drawString(Eq(0), Eq(3), StrEq("_"), _, _)).Times(1);

    // Run render twice, underscore should render only once!
    entry.render();
    entry.render();
}

TEST(TextEntry, KeyStrokesAreAppendedToText) {
    TextEntry entry;

    entry.keyPress('b');
    entry.keyPress('a');
    entry.keyPress('r');
    entry.keyPress('!');

    EXPECT_EQ(std::string("bar!"), entry.getText());
}

TEST(TextEntry, NonPrintableKeystrokesAreIgnored) {
    TextEntry entry;

    entry.keyPress('\0');
    entry.keyPress(KEY_DOWN);
    entry.keyPress(KEY_TAB);

    EXPECT_EQ(std::string(""), entry.getText());
}

TEST(TextEntry, BackspaceRemovesLastChar) {
    TextEntry entry;

    entry.keyPress('b');
    entry.keyPress('a');
    entry.keyPress('z');
    entry.keyPress(KEY_BACKSPACE);
    entry.keyPress('r');

    EXPECT_EQ(std::string("bar"), entry.getText());
}

TEST(TextEntry, BackspaceOnEmptyStringDoesNothing) {
    TextEntry entry;

    EXPECT_NO_THROW(entry.keyPress(KEY_BACKSPACE));

    EXPECT_EQ(std::string(""), entry.getText());
}

TEST(TextEntry, ReturnCallsCallback) {
    TextEntry entry;
    bool called = false;

    entry.setEnterCallback([&](TextEntry* e) { called = true; });

    entry.keyPress(KEY_ENTER);
    EXPECT_TRUE(called);
}