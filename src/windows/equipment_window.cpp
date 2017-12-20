#include "equipment_window.h"
#include "inspection_window.h"
#include "../core/game_engine.h"
#include "../components/equipment_component.h"
#include "../components/description_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"

namespace {
const char* nameOrNothing (EntityId item, GameEngine* engine) {
    DescriptionComponent* description = engine->state()->components()->get<DescriptionComponent>(item);
    if (item == 0) return "<Nothing>";
    if (description == 0) return "?Something?";
    return description->title.c_str();
}

void selectItem(Label* l) {
    EntityId player = l->window->getState()->player();
    EquipmentComponent* equipment =
        l->window->getState()->components()->get<EquipmentComponent>(player);
    EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->window);

    if (l->name() == "lblRight")
        win->setSelectedItem(equipment->rightHandWieldable);
    if (l->name() == "lblLeft")
        win->setSelectedItem(equipment->leftHandWieldable);
    if (l->name() == "lblHead")
        win->setSelectedItem(equipment->headWearable);
    if (l->name() == "lblFace")
        win->setSelectedItem(equipment->faceWearable);
    if (l->name() == "lblChest")
        win->setSelectedItem(equipment->chestWearable);
    if (l->name() == "lblArms")
        win->setSelectedItem(equipment->armsWearable);
    if (l->name() == "lblHands")
        win->setSelectedItem(equipment->handsWearable);
    if (l->name() == "lblLegs")
        win->setSelectedItem(equipment->legsWearable);
    if (l->name() == "lblFeet")
        win->setSelectedItem(equipment->feetWearable);
    if (win->itemSelected()) {
        Label* s = win->getWidget<Label>("lblItemSelector");
        s->y = l->y;
        s->visible() = true;
    }
}

} // Close namespace

void EquipmentWindow::setup () {
    int width  = 45;
    int height = 17;

    setTitle ("Equipment");
    setDimensions (0, 0, width, height);
    m_selectedItem = 0;
    m_selectedPage = 0;
}


void EquipmentWindow::registerWidgets()
{
    Label* l = nullptr;

    createWidget<Label>("lblEquipment", 4, 2)->text("Equipment");
    createWidget<Label>("lblRucksack", 16, 2)->text("Rucksack");

    createWidget<Label>("lblWielding", 2, 4)->text("Wielding");
    createWidget<Label>("lblWearing", 2, 8)->text("Wearing");

    l = createWidget<Label>("lblRight", 4, 5);
    l->text("Right:");
    l->commandChar = 1;
    l->onCommandChar = selectItem;

    l = createWidget<Label>("lblLeft", 4, 6);
    l->text("Left :");
    l->commandChar = 1;
    l->onCommandChar = selectItem;

    l = createWidget<Label>("lblHead", 4, 9);
    l->text("Head :");
    l->commandChar = 1;
    l->onCommandChar = selectItem;
    l = createWidget<Label>("lblFace", 4, 10);
    l->text("Face :");
    l->commandChar = 1;
    l->onCommandChar = selectItem;
    l = createWidget<Label>("lblChest", 4, 11);
    l->text("Chest:");
    l->commandChar = 1;
    l->onCommandChar = selectItem;
    l = createWidget<Label>("lblArms", 4, 12);
    l->text("Arms :");
    l->commandChar = 1;
    l->onCommandChar = selectItem;
    l = createWidget<Label>("lblHands", 4, 13);
    l->text("Hands:");
    l->commandChar = 3;
    l->onCommandChar = selectItem;
    l = createWidget<Label>("lblLegs", 4, 14);
    l->text("Legs :");
    l->commandChar = 2;
    l->onCommandChar = selectItem;
    l = createWidget<Label>("lblFeet", 4, 15);
    l->text("Feet :");
    l->commandChar = 4;
    l->onCommandChar = selectItem;

    createWidget<Label>("lblLeftItem", 11, 6);
    createWidget<Label>("lblRightItem", 11, 5);
    createWidget<Label>("lblHeadItem",  11,  9);
    createWidget<Label>("lblFaceItem",  11, 10);
    createWidget<Label>("lblChestItem", 11, 11);
    createWidget<Label>("lblArmsItem",  11, 12);
    createWidget<Label>("lblHandsItem", 11, 13);
    createWidget<Label>("lblLegsItem",  11, 14);
    createWidget<Label>("lblFeetItem",  11, 15);

    l = createWidget<Label>("lblPageSelector", 3, 2);
    l->text(">");
    l->fg = Color(RED);
    l = createWidget<Label>("lblItemSelector", 3, 5);
    l->text(">");
    l->fg = Color(RED);
    l->visible() = false;

    l = createWidget<Label>("lblSelectItem", 2, 0);
    l->text("Select item");
    l->vAlign = Widget::VerticalAlign::Centre;
    l->hAlign = Widget::HorizontalAlign::Right;

    l = createWidget<Label>("lblSelectedItem", 29, 2);
    l->text("");
    l->visible() = false;

    l->visible() = false;
    l = createWidget<Label>("lblConsume", 29, 3);
    l->text("consume");
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->commandChar = 1;
    l->onCommandChar = [](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->window);
        GameEngine* engine = win->getEngine();
        ConsumeItemEvent* event = new ConsumeItemEvent();
        event->entity = engine->state()->player();
        event->item = win->getSelectedItem();
        win->setSelectedItem(0);
        engine->raiseEvent (event);
        engine->swapTurn();
    };
    l->visible() = false;

    l = createWidget<Label>("lblInspect", 29, 2);
    l->text("inspect");
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->commandChar = 1;
    l->onCommandChar = [](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->window);
        GameEngine* engine = win->getEngine();
        EntityId* l_target = new EntityId(win->getSelectedItem());
        engine->getWindows()->createWindow<InspectionWindow>(l_target);
    };
    l->visible() = false;

    l = createWidget<Label>("lblUnequip", 29, 1);
    l->text("unequip");
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->commandChar = 1;
    l->onCommandChar = [](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->window);
        GameEngine* engine = win->getEngine();
        UnequipItemEvent* event = new UnequipItemEvent();
        event->entity = engine->state()->player();
        event->item = win->getSelectedItem();
        win->setSelectedItem(0);
        engine->raiseEvent (event);
        engine->swapTurn();
        win->updateItemNames();
    };
    l->visible() = false;

    l = createWidget<Label>("lblEquip", 29, 1);
    l->text("equip");
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->commandChar = 1;
    l->onCommandChar = [](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->window);
        GameEngine* engine = win->getEngine();
        EquipItemEvent* event = new EquipItemEvent();
        event->entity = engine->state()->player();
        event->item = win->getSelectedItem();
        win->setSelectedItem(0);
        engine->raiseEvent (event);
        engine->swapTurn();
        win->updateItemNames();
    };
    l->visible() = false;

    l = createWidget<Label>("lblDrop", 29, 0);
    l->text("drop");
    l->vAlign = Widget::VerticalAlign::Bottom;
    l->commandChar = 1;
    l->onCommandChar = [](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->window);
        GameEngine* engine = win->getEngine();
        DropEquipmentEvent* event = new DropEquipmentEvent();
        event->entity = engine->state()->player();
        event->item = win->getSelectedItem();
        win->setSelectedItem(0);
        engine->raiseEvent (event);
        engine->swapTurn();
        win->updateItemNames();
    };
    l->visible() = false;
}

void EquipmentWindow::redraw() {
    EntityId player = getEngine()->state()->player();
    EquipmentComponent* equipment = getEngine()->state()->components()->get<EquipmentComponent>(player);

    if (m_selectedPage == 1) {
        for (size_t ii = 0; ii < equipment->carriedEquipment.size(); ii++) {
            if (equipment->carriedEquipment[ii] == m_selectedItem) drawString (ii+4, 4, ">", Color (RED), Color (GREY));
            drawTile (ii+4, 5, ii+65, Color (GREEN), Color (GREY));
            drawString (ii+4, 7, nameOrNothing (equipment->carriedEquipment[ii], getEngine()));
        }
    }

    drawBorder (0, getWidth()-18, getHeight()-2, 16);
}

void EquipmentWindow::keyDown (unsigned char key)
{
    Window::keyDown (key);

    if (key == KEY_ESC) {
        getEngine()->getWindows()->popWindow();
        return;
    }

    if (key == KEY_TAB) {
        m_selectedPage = (m_selectedPage == 0) ? 1 : 0;
        getWidget<Label>("lblPageSelector")->x = 3 + (12*m_selectedPage);

        getWidget<Label>("lblWielding")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblWearing")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblRight")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblRightItem")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblLeft")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblLeftItem")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblHead")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblFace")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblChest")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblArms")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblHands")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblLegs")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblFeet")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblHeadItem")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblFaceItem")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblChestItem")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblArmsItem")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblHandsItem")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblLegsItem")->visible() = (m_selectedPage == 0);
        getWidget<Label>("lblFeetItem")->visible() = (m_selectedPage == 0);

        m_selectedItem = 0;
        getWidget<Label>("lblItemSelector")->visible() = false;
    }

    getWidget<Label>("lblSelectItem")->visible() = (m_selectedItem == 0);
    getWidget<Label>("lblSelectedItem")->visible() = (m_selectedItem > 0);
    getWidget<Label>("lblConsume")->visible() = (m_selectedItem > 0);
    getWidget<Label>("lblInspect")->visible() = (m_selectedItem > 0);
    getWidget<Label>("lblDrop")->visible() = (m_selectedItem > 0);
    getWidget<Label>("lblUnequip")->visible() = (m_selectedItem > 0 && m_selectedPage == 0);
    getWidget<Label>("lblEquip")->visible() = (m_selectedItem > 0 && m_selectedPage == 1);

    updateItemNames();
}

void EquipmentWindow::updateItemNames()
{
    EntityId player = getState()->player();
    EquipmentComponent* equipment =
        getState()->components()->get<EquipmentComponent>(player);

    getWidget<Label>("lblRightItem")->text(
            nameOrNothing (equipment->rightHandWieldable, getEngine()));
    getWidget<Label>("lblLeftItem")->text(
            nameOrNothing (equipment->leftHandWieldable, getEngine()));
    getWidget<Label>("lblHeadItem")->text(
            nameOrNothing (equipment->headWearable, getEngine()));
    getWidget<Label>("lblFaceItem")->text(
            nameOrNothing (equipment->faceWearable, getEngine()));
    getWidget<Label>("lblChestItem")->text(
            nameOrNothing (equipment->chestWearable, getEngine()));
    getWidget<Label>("lblArmsItem")->text(
            nameOrNothing (equipment->armsWearable, getEngine()));
    getWidget<Label>("lblHandsItem")->text(
            nameOrNothing (equipment->handsWearable, getEngine()));
    getWidget<Label>("lblLegsItem")->text(
            nameOrNothing (equipment->legsWearable, getEngine()));
    getWidget<Label>("lblFeetItem")->text(
            nameOrNothing (equipment->feetWearable, getEngine()));

    getWidget<Label>("lblSelectedItem")->text(
            nameOrNothing (m_selectedItem, getEngine()));
}
