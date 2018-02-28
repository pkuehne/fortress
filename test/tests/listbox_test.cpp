#include <gtest/gtest.h>
#include "../../src/windows/listbox.h"
#include "../../src/core/utility.h"

using namespace ::testing;
class ListBoxTest : public ::testing::Test
{
  public:
    void SetUp()
    {
        box.items.push_back("item1");
        box.items.push_back("item2");
        box.items.push_back("item3");
        box.items.push_back("item4");
        box.items.push_back("item5");

        box.setSelectedItem(0);
    }
    ListBox box;
};

TEST_F(ListBoxTest, pressingEnterInvokesCallback)
{
    box.onItemSelected = [](ListBox *b) { throw "Selected"; };

    EXPECT_ANY_THROW(box.keyPress(KEY_ENTER));
}

TEST_F(ListBoxTest, ScrollingUpDecrementsSelectedItem)
{
    box.setSelectedItem(1);

    box.keyPress('-');

    EXPECT_EQ(box.getSelectedItem(), 0);
}

TEST_F(ListBoxTest, ScrollingUpBeyondFirstItemDoesNothing)
{
    box.keyPress('+');

    EXPECT_EQ(box.getSelectedItem(), 1);
}

TEST_F(ListBoxTest, ScrollingDownIncrementsSelection)
{
    box.setSelectedItem(4);

    box.keyPress('+');

    EXPECT_EQ(box.getSelectedItem(), 4);
}