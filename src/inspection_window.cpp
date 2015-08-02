#include "inspection_window.h"
#include "gameengine.h"

void InspectionWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    if (key == 27) {
        getEngine()->getWindows()->popWindow();
    }
}

void InspectionWindow::resize() {
    int width = 30;
    int height = 7;

    setDimensions (0, 0, width, height);
}

void InspectionWindow::redraw() {

//    int x = getXOffset();
//    int y = getYOffset();

    //getEngine()->getGraphics()->calculateWindowOffsetsFromCentre (height, width, x, y);
    //getEngine()->getGraphics()->clearArea (y, x, height, width);
    //getEngine()->getGraphics()->drawBorder (y, x, height, width);

    drawString (2, 2, "Description: ");

    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (!l_entity) return;

    DescriptionComponent* l_description = getEngine()->getEntities()->getDescriptions()->get(*l_entity);
    if (!l_description) return;

    drawString (2, 15, l_description->title.c_str());
    drawString (4,  2, l_description->text.c_str());
}

void InspectionWindow::gainFocus() {
    setTitle ("What?");
}

void InspectionWindow::loseFocus() {
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (l_entity) delete l_entity;
}
