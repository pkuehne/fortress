#include "../../src/core/utility.h"
#include "../../src/widgets/listbox.h"
#include "../mocks/graphics_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;
class ListBoxTest : public ::testing::Test {
public:
    void SetUp() {
        item1.setText("item1");
        item1.setValue(1);

        item2.setText("item2");
        item2.setValue(2);

        item3.setText("item3");
        item3.setValue(3);

        item4.setText("item4");
        item4.setValue(4);

        item5.setText("item5");
        item5.setValue(5);
        item5.setColor(Color(RED));

        box.addItem(item1);
        box.addItem(item2);
        box.addItem(item3);
        box.addItem(item4);
        box.addItem(item5);

        box.setSelection(0);
    }
    ListBox box;
    ListBoxItem item1;
    ListBoxItem item2;
    ListBoxItem item3;
    ListBoxItem item4;
    ListBoxItem item5;
};

TEST_F(ListBoxTest, pressingEnterInvokesCallback) {
    bool called = false;
    box.setItemSelectedCallback([&](ListBox* b) { called = true; });

    box.keyPress(KEY_ENTER);

    EXPECT_TRUE(called);
}

TEST_F(ListBoxTest, ScrollingUpDecrementsSelectedItem) {
    box.setSelection(1);

    box.keyPress('-');

    EXPECT_EQ(box.getSelection(), 0);
}

TEST_F(ListBoxTest, ScrollingUpBeyondFirstItemDoesNothing) {
    box.keyPress('+');

    EXPECT_EQ(box.getSelection(), 1);
}

TEST_F(ListBoxTest, ScrollingDownIncrementsSelection) {
    box.setSelection(4);

    box.keyPress('+');

    EXPECT_EQ(box.getSelection(), 4);
}

TEST_F(ListBoxTest, ClearingItemsRemovesAll) {
    EXPECT_NE(0, box.getItems().size());

    box.clearItems();

    EXPECT_EQ(0, box.getItems().size());
}

TEST_F(ListBoxTest, ClearingItemsResetsSelectionButDoesNotCallCallback) {
    box.setSelection(3);
    box.setItemSelectedCallback([](ListBox* b) { throw "Selected"; });

    EXPECT_NO_THROW(box.clearItems());
    EXPECT_EQ(0, box.getSelection());
}

TEST_F(ListBoxTest, AddingItemSetsItsIndex) {
    ListBoxItem item1;
    ListBoxItem item2;

    box.addItem(item1);
    box.addItem(item2);

    EXPECT_EQ(1, box.getItems()[1].getIndex());
}

TEST_F(ListBoxTest, getSelectedItemDoesJustThat) {
    box.setSelection(3);

    EXPECT_EQ(box.getSelectedItem().getIndex(), 3);
}

TEST_F(ListBoxTest, gettingSelectedItemFromEmptyBoxTHrows) {
    ListBox b;

    EXPECT_ANY_THROW(b.getSelectedItem());
}

TEST_F(ListBoxTest, settingSelectedItemCallsCallback) {
    // Given
    bool called = false;
    box.setItemSelectedCallback([&](ListBox* b) { called = true; });

    // When
    box.setSelection(3);

    // Then
    EXPECT_TRUE(called);
}

TEST_F(ListBoxTest, ItemsAreRenderedWithColour) {
    GraphicsMock graphics;
    box.setGraphics(&graphics);
    box.setHeight(10);       // give enough space
    box.setSensitive(false); // Hide the selector

    EXPECT_CALL(graphics,
                drawString(Eq(0), Eq(0), StrEq(item1.getText()), _, _))
        .Times(1);
    EXPECT_CALL(graphics,
                drawString(Eq(1), Eq(0), StrEq(item2.getText()), _, _))
        .Times(1);
    EXPECT_CALL(graphics,
                drawString(Eq(2), Eq(0), StrEq(item3.getText()), _, _))
        .Times(1);
    EXPECT_CALL(graphics,
                drawString(Eq(3), Eq(0), StrEq(item4.getText()), _, _))
        .Times(1);
    EXPECT_CALL(graphics, drawString(Eq(4), Eq(0), StrEq(item5.getText()),
                                     Eq(Color(RED)), _))
        .Times(1);

    box.render();
}

TEST_F(ListBoxTest, SelectorIsDrawnNextToSelectedItem) {
    GraphicsMock graphics;
    box.setGraphics(&graphics);

    EXPECT_CALL(graphics, drawString(Eq(0), Eq(0), StrEq(">"), _, _)).Times(1);
    EXPECT_CALL(graphics, drawString(_, Eq(1), StrNe(">"), _, _))
        .Times(AtLeast(1));

    box.render();
}

TEST_F(ListBoxTest, SelectorIsNotDrawnWhenListBoxIsNotSensitive) {
    GraphicsMock graphics;
    box.setGraphics(&graphics);
    box.setSensitive(false);

    EXPECT_CALL(graphics, drawString(Eq(0), Eq(0), StrEq(">"), _, _)).Times(0);
    EXPECT_CALL(graphics, drawString(_, Eq(0), StrNe(">"), _, _))
        .Times(AtLeast(1));

    box.render();
}

TEST_F(ListBoxTest, ScrollToEndMovesSelectionToLastItem) {
    box.setHeight(3);
    box.scrollToBottom();

    EXPECT_EQ(4, box.getSelection());
}