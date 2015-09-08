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
    m_selectedItem = 0;
    m_selectedPage = 0;
}

void EquipmentWindow::resize() {

    int width  = 45;
    int height = 17;

    setDimensions (0, 0, width, height);
}

void EquipmentWindow::redraw() {
    EntityId player = getEngine()->getEntities()->getPlayer();
    EquipmentComponent* equipment = getEngine()->getEntities()->getEquipments()->get(player);

    if (m_selectedPage == 0) drawTile (2, 3, '>', Color (RED), Color (GREY));
    drawString (2, 4, "Equipment", Color (GREY));
    if (m_selectedPage == 1) drawTile (2, 15, '>', Color (RED), Color (GREY));
    drawString (2, 16, "Rucksack", Color (GREY));

    if (m_selectedPage == 0) {

        drawString (4, 2, "Wielding");

        if (m_selectedItem && m_selectedItem == equipment->rightHandWieldable) drawTile (5, 3, '>', Color (RED), Color (GREY));
        drawString (5, 4, "r", Color (GREEN));
        drawString (5, 5, "ight:");
        drawString (5, 11, nameOrNothing (equipment->rightHandWieldable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->leftHandWieldable) drawTile (6, 3, '>', Color (RED), Color (GREY));
        drawString (6, 4, "l", Color (GREEN));
        drawString (6, 5, "eft :");
        drawString (6, 11, nameOrNothing (equipment->leftHandWieldable, getEngine()));

        drawString (8, 2, "Wearing");

        if (m_selectedItem && m_selectedItem == equipment->headWearable) drawTile (9, 3, '>', Color (RED), Color (GREY));
        drawString (9, 4, "h", Color (GREEN));
        drawString (9, 5, "ead :");
        drawString (9, 11, nameOrNothing (equipment->headWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->faceWearable) drawTile (10, 3, '>', Color (RED), Color (GREY));
        drawString (10, 4, "f", Color (GREEN));
        drawString (10, 5, "ace :");
        drawString (10, 11, nameOrNothing (equipment->faceWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->chestWearable) drawTile (11, 3, '>', Color (RED), Color (GREY));
        drawString (11, 4, "c", Color (GREEN));
        drawString (11, 5, "hest:");
        drawString (11, 11, nameOrNothing (equipment->chestWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->armsWearable) drawTile (12, 3, '>', Color (RED), Color (GREY));
        drawString (12, 4, "a", Color (GREEN));
        drawString (12, 5, "rms :");
        drawString (12, 11, nameOrNothing (equipment->armsWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->handsWearable) drawTile (13, 3, '>', Color (RED), Color (GREY));
        drawString (13, 4, "hands:");
        drawString (13, 7, "d", Color (GREEN));
        drawString (13, 11, nameOrNothing (equipment->handsWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->legsWearable) drawTile (14, 3, '>', Color (RED), Color (GREY));
        drawString (14, 4, "legs :");
        drawString (14, 5, "e", Color (GREEN));
        drawString (14, 11, nameOrNothing (equipment->legsWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->feetWearable) drawTile (15, 3, '>', Color (RED), Color (GREY));
        drawString (15, 4, "feet :");
        drawString (15, 7, "t", Color (GREEN));
        drawString (15, 11, nameOrNothing (equipment->feetWearable, getEngine()));

    } else {
        for (size_t ii = 0; ii < equipment->carriedEquipment.size(); ii++) {
            if (equipment->carriedEquipment[ii] == m_selectedItem) drawTile (ii+4, 4, '>', Color (RED), Color (GREY));
            drawTile (ii+4, 5, ii+65, Color (GREEN), Color (GREY));
            drawString (ii+4, 7, nameOrNothing (equipment->carriedEquipment[ii], getEngine()));
        }
    }

    drawBorder (0, getWidth()-18, getHeight()-2, 16);

    if (m_selectedItem == 0) {
        drawString (getHeight()/2, getWidth()-14, "Select item");
    } else {
        drawString (2, getWidth()-16, nameOrNothing (m_selectedItem, getEngine()));

        drawString (getHeight()-2, getWidth()-16, "d", Color (GREEN));
        drawString (getHeight()-2, getWidth()-15, "rop item");

        if (m_selectedPage == 0) {
            drawString (getHeight()-3, getWidth()-16, "u", Color (GREEN));
            drawString (getHeight()-3, getWidth()-15, "nequip");
        } else {
            drawString (getHeight()-3, getWidth()-16, "e", Color (GREEN));
            drawString (getHeight()-3, getWidth()-15, "quip");
        }

        drawString (getHeight()-4, getWidth()-16, "i", Color (GREEN));
        drawString (getHeight()-4, getWidth()-15, "nspect");
    }


}

void EquipmentWindow::keyDown (unsigned char key) {
    Window::keyDown (key);
    EntityId player = getEngine()->getEntities()->getPlayer();
    EquipmentComponent* equipment = getEngine()->getEntities()->getEquipments()->get(player);

    if (key == ESC) {
        getEngine()->getWindows()->popWindow();
    }

    if (m_selectedPage == 0) {
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
    } else {
        if (key >= 'A' && key <= 'Z') {
            m_selectedItem = equipment->carriedEquipment[key-65];
        }
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
    if (m_selectedItem && m_selectedPage == 0 && key == 'u') {
        UnequipItemEvent* event = new UnequipItemEvent();
        event->entity = getEngine()->getEntities()->getPlayer();
        event->item = m_selectedItem;
        m_selectedItem = 0;
        getEngine()->raiseEvent (event);
    }
    if (m_selectedItem && m_selectedPage == 1 && key == 'e') {
        EquipItemEvent* event = new EquipItemEvent();
        event->entity = getEngine()->getEntities()->getPlayer();
        event->item = m_selectedItem;
        m_selectedItem = 0;
        getEngine()->raiseEvent (event);
    }

    if (key == TAB) {
        if (m_selectedPage == 1) {
            m_selectedPage = 0;
        } else {
            m_selectedPage = 1;
        }
        m_selectedItem = 0;
    }
}
