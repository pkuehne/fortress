#include "equipment_window.h"
#include "game_engine.h"
#include "inspection_window.h"
#include "equipment_component.h"
#include "description_component.h"
#include "wearable_component.h"
#include "wieldable_component.h"

namespace {
    const char* nameOrNothing (EntityId item, GameEngine* engine) {
        DescriptionComponent* description = engine->state()->components()->get<DescriptionComponent>(item);
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
    EntityId player = getEngine()->state()->player();
    EquipmentComponent* equipment = getEngine()->state()->components()->get<EquipmentComponent>(player);

    if (m_selectedPage == 0) drawString (2, 3, ">", Color (RED), Color (GREY));
    drawString (2, 4, "Equipment", Color (GREY));
    if (m_selectedPage == 1) drawString (2, 15, ">", Color (RED), Color (GREY));
    drawString (2, 16, "Rucksack", Color (GREY));

    if (m_selectedPage == 0) {
        unsigned int pointer_loc = 0;
        drawString (4, 2, "Wielding");

        if (m_selectedItem && m_selectedItem == equipment->rightHandWieldable) pointer_loc = 5;
        drawCommandString (5, 4, "right:", 0);
        drawString (5, 11, nameOrNothing (equipment->rightHandWieldable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->leftHandWieldable) pointer_loc = 6;
        drawCommandString (6, 4, "left :", 0);
        drawString (6, 11, nameOrNothing (equipment->leftHandWieldable, getEngine()));

        drawString (8, 2, "Wearing");

        if (m_selectedItem && m_selectedItem == equipment->headWearable) pointer_loc = 9;
        drawCommandString (9, 4, "head :", 0);
        drawString (9, 11, nameOrNothing (equipment->headWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->faceWearable) pointer_loc = 10;
        drawCommandString (10, 4, "face :", 0);
        drawString (10, 11, nameOrNothing (equipment->faceWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->chestWearable) pointer_loc = 11;
        drawCommandString (11, 4, "chest:", 0);
        drawString (11, 11, nameOrNothing (equipment->chestWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->armsWearable) pointer_loc = 12;
        drawCommandString (12, 4, "arms :", 0);
        drawString (12, 11, nameOrNothing (equipment->armsWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->handsWearable) pointer_loc = 13;
        drawCommandString (13, 4, "hands:", 3);
        drawString (13, 11, nameOrNothing (equipment->handsWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->legsWearable) pointer_loc = 14;
        drawCommandString (14, 4, "legs :", 1);
        drawString (14, 11, nameOrNothing (equipment->legsWearable, getEngine()));

        if (m_selectedItem && m_selectedItem == equipment->feetWearable) pointer_loc = 15;
        drawCommandString (15, 4, "feet :", 3);
        drawString (15, 11, nameOrNothing (equipment->feetWearable, getEngine()));

        if (pointer_loc) {
            drawString(pointer_loc, 3, ">", Color(RED), Color(GREY));
        }

    } else {
        for (size_t ii = 0; ii < equipment->carriedEquipment.size(); ii++) {
            if (equipment->carriedEquipment[ii] == m_selectedItem) drawString (ii+4, 4, ">", Color (RED), Color (GREY));
            drawTile (ii+4, 5, ii+65, Color (GREEN), Color (GREY));
            drawString (ii+4, 7, nameOrNothing (equipment->carriedEquipment[ii], getEngine()));
        }
    }

    drawBorder (0, getWidth()-18, getHeight()-2, 16);

    if (m_selectedItem == 0) {
        drawString (getHeight()/2, getWidth()-14, "Select item");
    } else {
        drawString (2, getWidth()-16, nameOrNothing (m_selectedItem, getEngine()));

        drawCommandString(getHeight()-2, getWidth()-16, "drop item", 0);

        if (m_selectedPage == 0) {
            drawCommandString(getHeight()-3, getWidth()-16, "unequip", 0);
        } else {
            drawCommandString(getHeight()-3, getWidth()-16, "equip", 0);
        }

        drawCommandString(getHeight()-4, getWidth()-16, "inspect", 0);
        drawCommandString(getHeight()-5, getWidth()-16, "consume", 0);
    }
}

void EquipmentWindow::keyDown (unsigned char key) {
    Window::keyDown (key);
    EntityId player = getEngine()->state()->player();
    EquipmentComponent* equipment = getEngine()->state()->components()->get<EquipmentComponent>(player);

    if (key == KEY_ESC) {
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

        getEngine()->getWindows()->pushWindow (
            getEngine()->getWindows()->createWindow<InspectionWindow>(l_target));
    }
    if (m_selectedItem && key == 'd') {
        DropEquipmentEvent* event = new DropEquipmentEvent();
        event->entity = getEngine()->state()->player();
        event->item = m_selectedItem;
        m_selectedItem = 0;
        getEngine()->raiseEvent (event);
        getEngine()->swapTurn();
    }
    if (m_selectedItem && key == 'c') {
        ConsumeItemEvent* event = new ConsumeItemEvent();
        event->entity = getEngine()->state()->player();
        event->item = m_selectedItem;
        m_selectedItem = 0;
        getEngine()->raiseEvent (event);
        getEngine()->swapTurn();
    }
    if (m_selectedItem && m_selectedPage == 0 && key == 'u') {
        UnequipItemEvent* event = new UnequipItemEvent();
        event->entity = getEngine()->state()->player();
        event->item = m_selectedItem;
        m_selectedItem = 0;
        getEngine()->raiseEvent (event);
        getEngine()->swapTurn();
    }
    if (m_selectedItem && m_selectedPage == 1 && key == 'e') {
        EquipItemEvent* event = new EquipItemEvent();
        event->entity = getEngine()->state()->player();
        event->item = m_selectedItem;
        m_selectedItem = 0;
        getEngine()->raiseEvent (event);
        getEngine()->swapTurn();
    }

    if (key == KEY_TAB) {
        if (m_selectedPage == 1) {
            m_selectedPage = 0;
        } else {
            m_selectedPage = 1;
        }
        m_selectedItem = 0;
    }
}
