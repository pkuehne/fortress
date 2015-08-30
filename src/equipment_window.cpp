#include "equipment_window.h"
#include "gameengine.h"

void EquipmentWindow::gainFocus () {
    setTitle ("Equipment");
}

void EquipmentWindow::resize() {

    int width = 30;
    int height = 7;

    setDimensions (0, 0, width, height);

}

void EquipmentWindow::redraw() {
    
}

void EquipmentWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    if (key == 27) {
        getEngine()->getWindows()->popWindow();
    }
}
