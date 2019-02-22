#include "../../src/widgets/tab.h"
#include "../mocks/graphics_mock.h"
#include "../mocks/widget_mock.h"
#include <gtest/gtest.h>

using namespace ::testing;

TEST(Tab, AddingPageCreatesNewFrame) {
    unsigned int width = 100;
    unsigned int height = 200;
    Tab tab;
    tab.setWidth(width);
    tab.setHeight(height);

    std::string title("Foo");
    tab.addPage(title);

    EXPECT_EQ(tab.getPages().size(), 1);
    EXPECT_EQ(tab.getPages()[0]->getTitle(), title);
}

TEST(Tab, RendersAllPageTitlesAndSelector) {
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();
    Tab tab;
    tab.setGraphics(graphics);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");
    std::string titleThree("Baz");

    tab.addPage(titleOne);
    tab.addPage(titleTwo);
    tab.addPage(titleThree);

    EXPECT_CALL(*graphics, drawString(_, _, StrEq(titleOne.c_str()), _, _));
    EXPECT_CALL(*graphics, drawString(_, _, StrEq(titleTwo.c_str()), _, _));
    EXPECT_CALL(*graphics, drawString(_, _, StrEq(titleThree.c_str()), _, _));
    EXPECT_CALL(*graphics, drawString(_, _, StrEq(">"), _, _));

    tab.render();
}

TEST(Tab, rendersOnlySelectedTab) {
    WidgetMock wOne;
    WidgetMock wTwo;
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    Tab tab;
    tab.setGraphics(graphics);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");

    tab.addPage(titleOne)->getFrame()->addChild(&wOne);
    tab.addPage(titleTwo)->getFrame()->addChild(&wTwo);

    EXPECT_CALL(*graphics, drawString(_, _, _, _, _)).Times(AtLeast(1));
    EXPECT_CALL(wOne, render()).Times(1);
    EXPECT_CALL(wTwo, render()).Times(0);

    tab.render();
}

TEST(Tab, setsYOffsetForAllPagesToAccountForPageNames) {
    unsigned int x = 20;
    unsigned int y = 30;
    unsigned int width = 100;
    unsigned int height = 200;

    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    Tab tab;
    tab.setGraphics(graphics);
    tab.setHeight(height);
    tab.setWidth(width);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");

    Frame* frame1 = tab.addPage(titleOne)->getFrame();
    Frame* frame2 = tab.addPage(titleTwo)->getFrame();

    tab.realign(x, y, width, height);
    EXPECT_EQ(frame1->getXPos(), tab.getXPos());
    EXPECT_EQ(frame1->getYPos(), tab.getYPos() + 2);
    EXPECT_EQ(frame1->getWidth(), tab.getWidth());
    EXPECT_EQ(frame1->getHeight(), tab.getHeight() - 2);

    EXPECT_EQ(frame2->getXPos(), tab.getXPos());
    EXPECT_EQ(frame2->getYPos(), tab.getYPos() + 2);
}

TEST(Tab, passedOnKeyPressOnlyForSelectedFrame) {
    WidgetMock wOne;
    WidgetMock wTwo;
    std::shared_ptr<GraphicsMock> graphics = std::make_shared<GraphicsMock>();

    Tab tab;
    tab.setGraphics(graphics);

    std::string titleOne("Foor");
    std::string titleTwo("Bar");

    tab.addPage(titleOne)->getFrame()->addChild(&wOne);
    tab.addPage(titleTwo)->getFrame()->addChild(&wTwo);

    unsigned char key = 'F';
    EXPECT_CALL(wOne, keyPress(Eq(key))).Times(1);
    EXPECT_CALL(wTwo, keyPress(Eq(key))).Times(0);

    tab.keyPress(key);
}

TEST(Tab, TabKeySwitchesBetweenTabs) {
    Tab tab;

    std::string titleOne("Foor");
    std::string titleTwo("Bar");
    std::string titleThree("Baz");

    tab.addPage(titleOne);
    tab.addPage(titleTwo);
    tab.addPage(titleThree);

    EXPECT_EQ(tab.getCurrentPage(), 0);

    tab.keyPress(KEY_TAB);
    EXPECT_EQ(tab.getCurrentPage(), 1);

    tab.keyPress(KEY_TAB);
    EXPECT_EQ(tab.getCurrentPage(), 2);

    tab.keyPress(KEY_TAB);
    EXPECT_EQ(tab.getCurrentPage(), 0);
}

TEST(Tab, OneTabDoesNoSwitching) {
    Tab tab;
    tab.addPage("page1");

    tab.keyPress(KEY_TAB);
    EXPECT_EQ(tab.getCurrentPage(), 0);
}

TEST(Tab, SwitchingPagesByKeyCallsCallback) {
    Tab tab;

    tab.addPage("Foo");
    tab.addPage("Bar");
    tab.setPageSwitchCallback([](Tab* t) { throw "Selected"; });

    EXPECT_ANY_THROW(tab.keyPress(KEY_TAB));
}

TEST(Tab, SwitchingPagesBySettingCallsCallback) {
    Tab tab;

    tab.addPage("Foo");
    tab.addPage("Bar");
    tab.setPageSwitchCallback([](Tab* t) { throw "Selected"; });

    EXPECT_ANY_THROW(tab.setCurrentPage(1));
}

TEST(Tab, SwitchingPagesToSamePageDoesNotCallCallback) {
    Tab tab;

    tab.addPage("Foo");
    tab.addPage("Bar");
    tab.setPageSwitchCallback([](Tab* t) { throw "Selected"; });

    EXPECT_NO_THROW(tab.setCurrentPage(0));
}

TEST(Tab, SinglePageDoesNotCallCallback) {
    Tab tab;

    tab.addPage("Foo");
    tab.setPageSwitchCallback([](Tab* t) { throw "Selected"; });

    EXPECT_NO_THROW(tab.keyPress(KEY_TAB));
}