#include "splash_window.h"
#include "main_window.h"
#include "../core/game_engine.h"
#include "../core/graphics.h"
#include "icon.h"
#include "label.h"

void SplashWindow::setup()
{
    setFullscreen();
}

void SplashWindow::registerWidgets()
{
    int xOffset = getEngine()->getGraphics()->getScreenWidth() / 2 - 25;
    int yOffset = getEngine()->getGraphics()->getScreenHeight() / 2;
    unsigned char tile = 178;

    createWidget<Label>("lblWelcome", -2, -3)
        ->setText("Welcome to")
        ->setHorizontalAlign(Widget::HorizontalAlign::Centre)
        ->setVerticalAlign(Widget::VerticalAlign::Centre);

    // 'F'
    createWidget<Icon>("icon00", xOffset + 0, yOffset + 0)->setIcon(tile);
    createWidget<Icon>("icon10", xOffset + 1, yOffset + 0)->setIcon(tile);
    createWidget<Icon>("icon20", xOffset + 2, yOffset + 0)->setIcon(tile);
    createWidget<Icon>("icon30", xOffset + 3, yOffset + 0)->setIcon(tile);

    createWidget<Icon>("icon01", xOffset + 0, yOffset + 1)->setIcon(tile);
    createWidget<Icon>("icon02", xOffset + 0, yOffset + 2)->setIcon(tile);

    createWidget<Icon>("icon03", xOffset + 0, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon13", xOffset + 1, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon23", xOffset + 2, yOffset + 3)->setIcon(tile);

    createWidget<Icon>("icon04", xOffset + 0, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon05", xOffset + 0, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon06", xOffset + 0, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon07", xOffset + 0, yOffset + 7)->setIcon(tile);

    // 'O'
    createWidget<Icon>("icon53", xOffset + 5, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon54", xOffset + 5, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon55", xOffset + 5, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon56", xOffset + 5, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon57", xOffset + 5, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon83", xOffset + 8, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon84", xOffset + 8, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon85", xOffset + 8, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon86", xOffset + 8, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon87", xOffset + 8, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon64", xOffset + 6, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon67", xOffset + 6, yOffset + 7)->setIcon(tile);
    createWidget<Icon>("icon73", xOffset + 7, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon77", xOffset + 7, yOffset + 7)->setIcon(tile);

    // 'r'
    createWidget<Icon>("icon113", xOffset + 11, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon114", xOffset + 11, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon115", xOffset + 11, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon116", xOffset + 11, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon117", xOffset + 11, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon123", xOffset + 12, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon133", xOffset + 13, yOffset + 3)->setIcon(tile);

    // 't'
    createWidget<Icon>("icon170", xOffset + 17, yOffset + 0)->setIcon(tile);
    createWidget<Icon>("icon171", xOffset + 17, yOffset + 1)->setIcon(tile);
    createWidget<Icon>("icon172", xOffset + 17, yOffset + 2)->setIcon(tile);
    createWidget<Icon>("icon173", xOffset + 17, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon174", xOffset + 17, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon175", xOffset + 17, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon176", xOffset + 17, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon177", xOffset + 17, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon165", xOffset + 16, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon183", xOffset + 18, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon187", xOffset + 18, yOffset + 7)->setIcon(tile);

    // 'r'
    createWidget<Icon>("icon213", xOffset + 21, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon214", xOffset + 21, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon215", xOffset + 21, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon216", xOffset + 21, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon217", xOffset + 21, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon223", xOffset + 22, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon233", xOffset + 23, yOffset + 3)->setIcon(tile);

    // 'e'
    createWidget<Icon>("icon263", xOffset + 26, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon264", xOffset + 26, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon265", xOffset + 26, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon266", xOffset + 26, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon267", xOffset + 26, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon293", xOffset + 29, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon294", xOffset + 29, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon295", xOffset + 29, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon297", xOffset + 29, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon275", xOffset + 27, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon285", xOffset + 28, yOffset + 5)->setIcon(tile);

    createWidget<Icon>("icon273", xOffset + 27, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon283", xOffset + 28, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon277", xOffset + 27, yOffset + 7)->setIcon(tile);
    createWidget<Icon>("icon287", xOffset + 28, yOffset + 7)->setIcon(tile);

    // 's'
    createWidget<Icon>("icon323", xOffset + 32, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon324", xOffset + 32, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon325", xOffset + 32, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon327", xOffset + 32, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon343", xOffset + 34, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon345", xOffset + 34, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon346", xOffset + 34, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon347", xOffset + 34, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon333", xOffset + 33, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon335", xOffset + 33, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon337", xOffset + 33, yOffset + 7)->setIcon(tile);

    // 's'
    createWidget<Icon>("icon373", xOffset + 37, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon374", xOffset + 37, yOffset + 4)->setIcon(tile);
    createWidget<Icon>("icon375", xOffset + 37, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon377", xOffset + 37, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon393", xOffset + 39, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon395", xOffset + 39, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon396", xOffset + 39, yOffset + 6)->setIcon(tile);
    createWidget<Icon>("icon397", xOffset + 39, yOffset + 7)->setIcon(tile);

    createWidget<Icon>("icon383", xOffset + 38, yOffset + 3)->setIcon(tile);
    createWidget<Icon>("icon385", xOffset + 38, yOffset + 5)->setIcon(tile);
    createWidget<Icon>("icon387", xOffset + 38, yOffset + 7)->setIcon(tile);
}

void SplashWindow::keyDown(unsigned char key)
{
    MainWindow *l_win = new MainWindow();
    l_win->initialise(getEngine());

    getEngine()->getWindows()->replaceAllWindows(l_win);
}
