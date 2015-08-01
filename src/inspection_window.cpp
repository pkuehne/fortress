#include "inspection_window.h"
#include "gameengine.h"

void InspectionWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    if (key == 27) {
        getEngine()->getWindows()->popWindow();
    }
}

void InspectionWindow::gainFocus() {
    getEngine()->getGraphics()->clearArea (10, 10, 10, 25);
    getEngine()->getGraphics()->drawBorder (10, 10, 10, 25);

    getEngine()->getGraphics()->drawString (12, 12, "Description");

    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (!l_entity) return;
    std::cout << "Got id: " << *l_entity << std::endl;
}

void InspectionWindow::loseFocus() {
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (l_entity) delete l_entity;
}
