#include <gtest/gtest.h>
#include "../../src/windows/tab.h"
#include "../mocks/graphics_mock.h"
#include "../mocks/widget_mock.h"

using namespace ::testing;

TEST(Tab, AddingPageCreatesNewFrame)
{
    Tab tab;
    std::string title("Foo");
    tab.addPage(title);

    EXPECT_EQ(tab.getPages().size(), 1);
    EXPECT_EQ(tab.getPages()[0]->getTitle(), title);
}

TEST(Tab, RendersAllPageTitlesAndSelector)
{
    GraphicsMock graphics;
    Tab tab;
    tab.setGraphics(&graphics);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");
    std::string titleThree("Baz");

    tab.addPage(titleOne);
    tab.addPage(titleTwo);
    tab.addPage(titleThree);

    EXPECT_CALL(graphics, drawString(_, _, StrEq(titleOne.c_str()), _, _));
    EXPECT_CALL(graphics, drawString(_, _, StrEq(titleTwo.c_str()), _, _));
    EXPECT_CALL(graphics, drawString(_, _, StrEq(titleThree.c_str()), _, _));
    EXPECT_CALL(graphics, drawString(_, _, StrEq(">"), _, _));

    tab.render();
}

TEST(Tab, rendersOnlySelectedTab)
{
    WidgetMock wOne;
    WidgetMock wTwo;
    GraphicsMock graphics;

    Tab tab;
    tab.setGraphics(&graphics);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");

    tab.addPage(titleOne)->getFrame()->addChild(&wOne);
    tab.addPage(titleTwo)->getFrame()->addChild(&wTwo);

    EXPECT_CALL(graphics, drawString(_, _, _, _, _)).Times(AtLeast(1));
    EXPECT_CALL(wOne, render()).Times(1);
    EXPECT_CALL(wTwo, render()).Times(0);

    tab.render();
}

TEST(Tab, setsWindowOffsetForAllPages)
{
    WidgetMock wOne;
    WidgetMock wTwo;
    GraphicsMock graphics;

    Tab tab;
    tab.setGraphics(&graphics);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");

    tab.addPage(titleOne)->getFrame()->addChild(&wOne);
    tab.addPage(titleTwo)->getFrame()->addChild(&wTwo);

    unsigned int x = 20;
    unsigned int y = 30;
    EXPECT_CALL(wOne, setWindowOffsets(Eq(x), Eq(y))).Times(1);
    EXPECT_CALL(wTwo, setWindowOffsets(Eq(x), Eq(y))).Times(1);

    tab.setWindowOffsets(x, y);
}

TEST(Tab, callsRealingWidgetForAllPages)
{
    WidgetMock wOne;
    WidgetMock wTwo;
    GraphicsMock graphics;

    Tab tab;
    tab.setGraphics(&graphics);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");

    tab.addPage(titleOne)->getFrame()->addChild(&wOne);
    tab.addPage(titleTwo)->getFrame()->addChild(&wTwo);

    unsigned int width = 20;
    unsigned int height = 30;
    EXPECT_CALL(wOne, realignWidget(Eq(width), Eq(height))).Times(1);
    EXPECT_CALL(wTwo, realignWidget(Eq(width), Eq(height))).Times(1);

    tab.realignWidget(width, height);
}

TEST(Tab, passedOnKeyPressOnlyForSelectedFrame)
{
    WidgetMock wOne;
    WidgetMock wTwo;
    GraphicsMock graphics;

    Tab tab;
    tab.setGraphics(&graphics);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");

    tab.addPage(titleOne)->getFrame()->addChild(&wOne);
    tab.addPage(titleTwo)->getFrame()->addChild(&wTwo);

    unsigned char key = 'F';
    EXPECT_CALL(wOne, keyPress(Eq(key))).Times(1);
    EXPECT_CALL(wTwo, keyPress(Eq(key))).Times(0);

    tab.keyPress(key);
}

TEST(Tab, TabKeySwitchesBetweenTabs)
{
    Tab tab;

    std::string titleOne("Foor");
    std::string titleTwo("Bar");
    std::string titleThree("Baz");

    tab.addPage(titleOne);
    tab.addPage(titleTwo);
    tab.addPage(titleThree);

    EXPECT_EQ(tab.getSelection(), 0);

    tab.keyPress(KEY_TAB);
    EXPECT_EQ(tab.getSelection(), 1);

    tab.keyPress(KEY_TAB);
    EXPECT_EQ(tab.getSelection(), 2);

    tab.keyPress(KEY_TAB);
    EXPECT_EQ(tab.getSelection(), 0);
}

TEST(Tab, OneTabDoesNoSwitching)
{
    Tab tab;
    tab.addPage("page1");

    tab.keyPress(KEY_TAB);
    EXPECT_EQ(tab.getSelection(), 0);
}