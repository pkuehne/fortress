#include "inspection_window.h"
#include "gameengine.h"

void InspectionWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    if (key == 27) {
        getEngine()->getWindows()->popWindow();
    }
}

void InspectionWindow::gainFocus() {
    getEngine()->getGraphics()->clearArea (10, 10, 10, 30);
    getEngine()->getGraphics()->drawBorder (10, 10, 10, 30);

    getEngine()->getGraphics()->drawString (12, 12, "Description: ");

    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (!l_entity) return;
    std::cout << "Got id: " << *l_entity << std::endl;

    DescriptionComponent* l_description = getEngine()->getEntities()->getDescriptions()->get(*l_entity);
    if (!l_description) return;

    getEngine()->getGraphics()->drawString (12, 25, l_description->title.c_str());
    getEngine()->getGraphics()->drawString (14, 12, l_description->text.c_str());


}

void InspectionWindow::loseFocus() {
    EntityId* l_entity = static_cast<EntityId*>(getArgs());
    if (l_entity) delete l_entity;
}
