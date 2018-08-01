#include "../../src/core/utility.h"
#include "../../src/widgets/text_entry.h"

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
    // Given
    TextEntry entry;
    entry.setWidth(10);

    // When
    entry.keyPress('b');
    entry.keyPress('a');
    entry.keyPress('r');
    entry.keyPress('!');

    // Then
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
    // Given
    TextEntry entry;
    entry.setWidth(10);

    // When
    entry.keyPress('b');
    entry.keyPress('a');
    entry.keyPress('z');
    entry.keyPress(KEY_BACKSPACE);
    entry.keyPress('r');

    // Then
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

TEST(TextEntry, SuffixIsDrawn) {
    // Given
    GraphicsMock graphics;
    TextEntry entry;
    entry.setGraphics(&graphics);
    entry.setText(std::string("Foo"));
    entry.setSuffix(std::string("Bar"));

    // Then
    EXPECT_CALL(graphics, drawString(Eq(0), Eq(0), StrEq("Foo"), _, _))
        .Times(2);
    EXPECT_CALL(graphics, drawString(Eq(0), Eq(4), StrEq("Bar"), _, _))
        .Times(2);
    EXPECT_CALL(graphics, drawString(Eq(0), Eq(3), StrEq("_"), _, _)).Times(1);

    // When
    // Run render twice, underscore should not!
    entry.render();
    entry.render();
}

TEST(TextEntry, SuffixIsDrawnWithoutCursorSpaceIfNotSensitive) {
    // Given
    GraphicsMock graphics;
    TextEntry entry;
    entry.setGraphics(&graphics);
    entry.setText(std::string("Foo"));
    entry.setSuffix(std::string("Bar"));
    entry.setSensitive(false);

    // Then
    EXPECT_CALL(graphics, drawString(Eq(0), Eq(0), StrEq("Foo"), _, _))
        .Times(2);
    EXPECT_CALL(graphics, drawString(Eq(0), Eq(3), StrEq("Bar"), _, _))
        .Times(2);

    // When
    // Run render twice, underscore should not!
    entry.render();
    entry.render();
}

TEST(TextEntry, SuffixIsNotPartOfString) {
    // Given
    TextEntry entry;
    entry.setWidth(10);
    entry.setSuffix("bar");

    // When
    entry.keyPress('f');
    entry.keyPress('o');
    entry.keyPress('o');

    // Then
    EXPECT_EQ(std::string("foo"), entry.getText());
}

TEST(TextEntry, StringWidthIsLimitedToWidgetWidthMinusOneForCursor) {
    // Given
    TextEntry entry;
    entry.setWidth(4);

    // When
    entry.keyPress('f');
    entry.keyPress('o');
    entry.keyPress('o');
    entry.keyPress('o');

    // Then
    EXPECT_EQ(std::string("foo"), entry.getText());
}

TEST(TextEntry, StringWidthIsLimitedToWidgetWidthMinusOneForCursorAndSuffix) {
    // Given
    TextEntry entry;
    entry.setWidth(7);
    entry.setSuffix(std::string("bar"));

    // When
    entry.keyPress('f');
    entry.keyPress('o');
    entry.keyPress('o');
    entry.keyPress('o');

    // Then
    EXPECT_EQ(std::string("foo"), entry.getText());
}