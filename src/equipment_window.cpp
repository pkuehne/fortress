#include "equipment_window.h"
#include "gameengine.h"
#include "inspection_window.h"

namespace {
    const char* nameOrNothing (EntityId item, GameEngineInterface* engine) {
        DescriptionComponent* description = engine->getEntities()->getDescriptions()->get(item);
        if (item == 0) return "<Nothing>";
        if (description == 0) return "?Something?";
        return description->title.c_str();
    }
}

void EquipmentWindow::gainFocus () {
    setTitle ("Equipment");
}

void EquipmentWindow::resize() {

    int width  = 45;
    int height = 15;

    setDimensions (0, 0, width, height);

}

void EquipmentWindow::redraw() {
    EntityId player = getEngine()->getEntities()->getPlayer();
    EquipmentComponent* equipment = getEngine()->getEntities()->getEquipments()->get(player);

    drawString (2, 2, "Wielding");

    if (m_selectedItem == equipment->rightHandWieldable) drawTile (3, 3, '>', Color (RED), Color (GREY));
    drawString (3, 4, "r", Color (GREEN));
    drawString (3, 5, "ight:");
    drawString (3, 11, nameOrNothing (equipment->rightHandWieldable, getEngine()));

    if (m_selectedItem == equipment->leftHandWieldable) drawTile (4, 3, '>', Color (RED), Color (GREY));
    drawString (4, 4, "l", Color (GREEN));
    drawString (4, 5, "eft :");
    drawString (4, 11, nameOrNothing (equipment->leftHandWieldable, getEngine()));

    drawString (6, 2, "Wearing");

    if (m_selectedItem && m_selectedItem == equipment->headWearable) drawTile (7, 3, '>', Color (RED), Color (GREY));
    drawString (7, 4, "h", Color (GREEN));
    drawString (7, 5, "ead :");
    drawString (7, 11, nameOrNothing (equipment->headWearable, getEngine()));

    if (m_selectedItem && m_selectedItem == equipment->faceWearable) drawTile (8, 3, '>', Color (RED), Color (GREY));
    drawString (8, 4, "f", Color (GREEN));
    drawString (8, 5, "ace :");
    drawString (8, 11, nameOrNothing (equipment->faceWearable, getEngine()));

    if (m_selectedItem && m_selectedItem == equipment->chestWearable) drawTile (9, 3, '>', Color (RED), Color (GREY));
    drawString (9, 4, "c", Color (GREEN));
    drawString (9, 5, "hest:");
    drawString (9, 11, nameOrNothing (equipment->chestWearable, getEngine()));

    if (m_selectedItem && m_selectedItem == equipment->armsWearable) drawTile (10, 3, '>', Color (RED), Color (GREY));
    drawString (10, 4, "a", Color (GREEN));
    drawString (10, 5, "rms :");
    drawString (10, 11, nameOrNothing (equipment->armsWearable, getEngine()));

    if (m_selectedItem && m_selectedItem == equipment->handsWearable) drawTile (11, 3, '>', Color (RED), Color (GREY));
    drawString (11, 4, "hands:");
    drawString (11, 7, "d", Color (GREEN));
    drawString (11, 11, nameOrNothing (equipment->handsWearable, getEngine()));

    if (m_selectedItem && m_selectedItem == equipment->legsWearable) drawTile (12, 3, '>', Color (RED), Color (GREY));
    drawString (12, 4, "legs :");
    drawString (12, 5, "e", Color (GREEN));
    drawString (12, 11, nameOrNothing (equipment->legsWearable, getEngine()));

    if (m_selectedItem && m_selectedItem == equipment->feetWearable) drawTile (13, 3, '>', Color (RED), Color (GREY));
    drawString (13, 4, "feet :");
    drawString (13, 7, "t", Color (GREEN));
    drawString (13, 11, nameOrNothing (equipment->feetWearable, getEngine()));


    drawBorder (0, getWidth()-18, getHeight()-2, 16);

    if (m_selectedItem == 0) {
        drawString (getHeight()/2, getWidth()-14, "Select item");
    } else {
        drawString (2, getWidth()-16, nameOrNothing (m_selectedItem, getEngine()));

        drawString (getHeight()-2, getWidth()-16, "d", Color (GREEN));
        drawString (getHeight()-2, getWidth()-15, "rop item");

        drawString (getHeight()-3, getWidth()-16, "u", Color (GREEN));
        drawString (getHeight()-3, getWidth()-15, "nequip");

        drawString (getHeight()-4, getWidth()-16, "i", Color (GREEN));
        drawString (getHeight()-4, getWidth()-15, "nspect");
    }


}

void EquipmentWindow::keyDown (unsigned char key) {
    Window::keyDown (key);
    EntityId player = getEngine()->getEntities()->getPlayer();
    EquipmentComponent* equipment = getEngine()->getEntities()->getEquipments()->get(player);

    if (key == 27) {
        getEngine()->getWindows()->popWindow();
    }

    switch (key) {
        case 'r': m_selectedItem = equipment->rightHandWieldable; break;
        case 'l': m_selectedItem = equipment->leftHandWieldable; break;
        case 'h': m_selectedItem = equipment->headWearable; break;
        case 'f': m_selectedItem = equipment->faceWearable; break;
        case 'a': m_selectedItem = equipment->armsWearable; break;
        case 'c': m_selectedItem = equipment->chestWearable; break;
        case 'e': m_selectedItem = equipment->legsWearable; break;
        case 't': m_selectedItem = equipment->feetWearable; break;
    }

    if (m_selectedItem && key == 'i') {
        EntityId* l_target = new EntityId(m_selectedItem);

        InspectionWindow* l_win = new InspectionWindow();
        l_win->initialise(getEngine(), l_target);
        getEngine()->getWindows()->pushWindow (l_win);
    }
    if (m_selectedItem && key == 'd') {
        DropEquipmentEvent* event = new DropEquipmentEvent();
        event->entity = getEngine()->getEntities()->getPlayer();
        event->item = m_selectedItem;
        m_selectedItem = 0;
        getEngine()->raiseEvent (event);
    }
    if (m_selectedItem && key == 'u') {

    }
}
