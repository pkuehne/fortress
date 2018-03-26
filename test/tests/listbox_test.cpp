#include <gtest/gtest.h>
#include "../../src/windows/listbox.h"
#include "../../src/core/utility.h"

using namespace ::testing;
class ListBoxTest : public ::testing::Test
{
  public:
    void SetUp()
    {
        ListBoxItem item1;
        item1.setText("item1");
        item1.setValue(1);

        ListBoxItem item2;
        item1.setText("item2");
        item1.setValue(2);
        
        ListBoxItem item3;
        item1.setText("item3");
        item1.setValue(3);
        
        ListBoxItem item4;
        item1.setText("item4");
        item1.setValue(4);
        
        ListBoxItem item5;
        item1.setText("item5");
        item1.setValue(5);
        
        box.addItem(item1);
        box.addItem(item2);
        box.addItem(item3);
        box.addItem(item4);
        box.addItem(item5);

        box.setSelection(0);
    }
    ListBox box;
};

TEST_F(ListBoxTest, pressingEnterInvokesCallback)
{
    box.setItemSelectedCallback([](ListBox *b) { throw "Selected"; });

    EXPECT_ANY_THROW(box.keyPress(KEY_ENTER));
}

TEST_F(ListBoxTest, ScrollingUpDecrementsSelectedItem)
{
    box.setSelection(1);

    box.keyPress('-');

    EXPECT_EQ(box.getSelection(), 0);
}

TEST_F(ListBoxTest, ScrollingUpBeyondFirstItemDoesNothing)
{
    box.keyPress('+');

    EXPECT_EQ(box.getSelection(), 1);
}

TEST_F(ListBoxTest, ScrollingDownIncrementsSelection)
{
    box.setSelection(4);

    box.keyPress('+');

    EXPECT_EQ(box.getSelection(), 4);
}

TEST_F(ListBoxTest, ClearingItemsRemovesAll)
{
    EXPECT_NE(0, box.getItems().size());

    box.clearItems();

    EXPECT_EQ(0, box.getItems().size());
}

TEST_F(ListBoxTest, ClearingItemsResetsSelectionButDoesNotCallCallback)
{
    box.setSelection(3);
    box.setItemSelectedCallback([](ListBox *b) { throw "Selected"; });

    EXPECT_NO_THROW(box.clearItems());
    EXPECT_EQ(0, box.getSelection());
}

TEST_F(ListBoxTest, AddingItemSetsItsIndex)
{
    ListBoxItem item1;
    ListBoxItem item2;

    box.addItem(item1);
    box.addItem(item2);

    EXPECT_EQ(1, box.getItems()[1].getIndex());
}

TEST_F(ListBoxTest, getSelectedItemDoesJustThat)
{
    box.setSelection(3);

    EXPECT_EQ(box.getSelectedItem().getIndex(), 3);
}

TEST_F(ListBoxTest, gettingSelectedItemFromEmptyBoxTHrows)
{
    ListBox b;

    EXPECT_ANY_THROW(b.getSelectedItem());
}