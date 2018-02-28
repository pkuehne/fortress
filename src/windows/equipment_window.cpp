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
    EntityId player = l->getWindow()->getState()->player();
    EquipmentComponent* equipment =
        l->getWindow()->getState()->components()->get<EquipmentComponent>(player);
    EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->getWindow());

    if (l->getName() == "lblRight")
        win->setSelectedItem(equipment->rightHandWieldable);
    if (l->getName() == "lblLeft")
        win->setSelectedItem(equipment->leftHandWieldable);
    if (l->getName() == "lblHead")
        win->setSelectedItem(equipment->headWearable);
    if (l->getName() == "lblFace")
        win->setSelectedItem(equipment->faceWearable);
    if (l->getName() == "lblChest")
        win->setSelectedItem(equipment->chestWearable);
    if (l->getName() == "lblArms")
        win->setSelectedItem(equipment->armsWearable);
    if (l->getName() == "lblHands")
        win->setSelectedItem(equipment->handsWearable);
    if (l->getName() == "lblLegs")
        win->setSelectedItem(equipment->legsWearable);
    if (l->getName() == "lblFeet")
        win->setSelectedItem(equipment->feetWearable);
    if (win->itemSelected()) {
        Label* s = win->getWidget<Label>("lblItemSelector");
        s->setY(l->getY());
        s->setVisible(true);
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

    createWidget<Label>("lblEquipment", 4, 2)->setText("Equipment");
    createWidget<Label>("lblRucksack", 16, 2)->setText("Rucksack");

    createWidget<Label>("lblWielding", 2, 4)->setText("Wielding");
    createWidget<Label>("lblWearing", 2, 8)->setText("Wearing");

    l = createWidget<Label>("lblRight", 4, 5);
    l->setText("Right:");
    l->setCommandChar(1);
    l->setCommandCharCallback(selectItem);

    l = createWidget<Label>("lblLeft", 4, 6);
    l->setText("Left :");
    l->setCommandChar(1);
    l->setCommandCharCallback(selectItem);

    l = createWidget<Label>("lblHead", 4, 9);
    l->setText("Head :");
    l->setCommandChar(1);
    l->setCommandCharCallback(selectItem);
    l = createWidget<Label>("lblFace", 4, 10);
    l->setText("Face :");
    l->setCommandChar(1);
    l->setCommandCharCallback(selectItem);
    l = createWidget<Label>("lblChest", 4, 11);
    l->setText("Chest:");
    l->setCommandChar(1);
    l->setCommandCharCallback(selectItem);
    l = createWidget<Label>("lblArms", 4, 12);
    l->setText("Arms :");
    l->setCommandChar(1);
    l->setCommandCharCallback(selectItem);
    l = createWidget<Label>("lblHands", 4, 13);
    l->setText("Hands:");
    l->setCommandChar(3);
    l->setCommandCharCallback(selectItem);
    l = createWidget<Label>("lblLegs", 4, 14);
    l->setText("Legs :");
    l->setCommandChar(2);
    l->setCommandCharCallback(selectItem);
    l = createWidget<Label>("lblFeet", 4, 15);
    l->setText("Feet :");
    l->setCommandChar(4);
    l->setCommandCharCallback(selectItem);

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
    l->setText(">");
    l->setForegroundColor(Color(RED));
    l = createWidget<Label>("lblItemSelector", 3, 5);
    l->setText(">");
    l->setForegroundColor(Color(RED));
    l->setVisible(false);

    l = createWidget<Label>("lblSelectItem", 2, 0);
    l->setText("Select item");
    l->setVerticalAlign(Widget::VerticalAlign::Centre);
    l->setHorizontalAlign(Widget::HorizontalAlign::Right);

    l = createWidget<Label>("lblSelectedItem", 29, 2);
    l->setText("");
    l->setVisible(false);

    l->setVisible(false);
    l = createWidget<Label>("lblConsume", 29, 3);
    l->setText("consume");
    l->setVerticalAlign(Widget::VerticalAlign::Bottom);
    l->setCommandChar(1);
    l->setCommandCharCallback([](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->getWindow());
        GameEngine* engine = win->getEngine();
        ConsumeItemEvent* event = new ConsumeItemEvent();
        event->entity = engine->state()->player();
        event->item = win->getSelectedItem();
        win->setSelectedItem(0);
        engine->raiseEvent (event);
        engine->swapTurn();
    });
    l->setVisible(false);

    l = createWidget<Label>("lblInspect", 29, 2);
    l->setText("inspect");
    l->setVerticalAlign(Widget::VerticalAlign::Bottom);
    l->setCommandChar(1);
    l->setCommandCharCallback([](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->getWindow());
        GameEngine* engine = win->getEngine();
        EntityId* l_target = new EntityId(win->getSelectedItem());
        engine->getWindows()->createWindow<InspectionWindow>(l_target);
    });
    l->setVisible(false);

    l = createWidget<Label>("lblUnequip", 29, 1);
    l->setText("unequip");
    l->setVerticalAlign(Widget::VerticalAlign::Bottom);
    l->setCommandChar(1);
    l->setCommandCharCallback([](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->getWindow());
        GameEngine* engine = win->getEngine();
        UnequipItemEvent* event = new UnequipItemEvent();
        event->entity = engine->state()->player();
        event->item = win->getSelectedItem();
        win->setSelectedItem(0);
        engine->raiseEvent (event);
        engine->swapTurn();
        win->updateItemNames();
    });
    l->setVisible(false);

    l = createWidget<Label>("lblEquip", 29, 1);
    l->setText("equip");
    l->setVerticalAlign(Widget::VerticalAlign::Bottom);
    l->setCommandChar(1);
    l->setCommandCharCallback([](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->getWindow());
        GameEngine* engine = win->getEngine();
        EquipItemEvent* event = new EquipItemEvent();
        event->entity = engine->state()->player();
        event->item = win->getSelectedItem();
        win->setSelectedItem(0);
        engine->raiseEvent (event);
        engine->swapTurn();
        win->updateItemNames();
    });
    l->setVisible(false);

    l = createWidget<Label>("lblDrop", 29, 0);
    l->setText("drop");
    l->setVerticalAlign(Widget::VerticalAlign::Bottom);
    l->setCommandChar(1);
    l->setCommandCharCallback([](Label* l) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(l->getWindow());
        GameEngine* engine = win->getEngine();
        DropEquipmentEvent* event = new DropEquipmentEvent();
        event->entity = engine->state()->player();
        event->item = win->getSelectedItem();
        win->setSelectedItem(0);
        engine->raiseEvent (event);
        engine->swapTurn();
        win->updateItemNames();
    });
    l->setVisible(false);
}

void EquipmentWindow::redraw() {
    EntityId player = getEngine()->state()->player();
    EquipmentComponent* equipment = getEngine()->state()->components()->get<EquipmentComponent>(player);

    if (m_selectedPage == 1) {
        for (size_t ii = 0; ii < equipment->carriedEquipment.size(); ii++) {
            if (equipment->carriedEquipment[ii] == m_selectedItem) {
                drawString (ii+4, 4, ">", Color (RED), Color (GREY));
            }
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
        getWidget<Label>("lblPageSelector")->setX(3 + (12*m_selectedPage));

        getWidget<Label>("lblWielding")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblWearing")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblRight")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblRightItem")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblLeft")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblLeftItem")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblHead")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblFace")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblChest")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblArms")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblHands")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblLegs")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblFeet")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblHeadItem")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblFaceItem")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblChestItem")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblArmsItem")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblHandsItem")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblLegsItem")->setVisible((m_selectedPage == 0));
        getWidget<Label>("lblFeetItem")->setVisible((m_selectedPage == 0));

        m_selectedItem = 0;
        getWidget<Label>("lblItemSelector")->setVisible(false);
    }

    getWidget<Label>("lblSelectItem")->setVisible((m_selectedItem == 0));
    getWidget<Label>("lblSelectedItem")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblConsume")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblInspect")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblDrop")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblUnequip")->setVisible((m_selectedItem > 0 && m_selectedPage == 0));
    getWidget<Label>("lblEquip")->setVisible((m_selectedItem > 0 && m_selectedPage == 1));

    updateItemNames();
}

void EquipmentWindow::updateItemNames()
{
    EntityId player = getState()->player();
    EquipmentComponent* equipment =
        getState()->components()->get<EquipmentComponent>(player);

    getWidget<Label>("lblRightItem")->setText(
            nameOrNothing (equipment->rightHandWieldable, getEngine()));
    getWidget<Label>("lblLeftItem")->setText(
            nameOrNothing (equipment->leftHandWieldable, getEngine()));
    getWidget<Label>("lblHeadItem")->setText(
            nameOrNothing (equipment->headWearable, getEngine()));
    getWidget<Label>("lblFaceItem")->setText(
            nameOrNothing (equipment->faceWearable, getEngine()));
    getWidget<Label>("lblChestItem")->setText(
            nameOrNothing (equipment->chestWearable, getEngine()));
    getWidget<Label>("lblArmsItem")->setText(
            nameOrNothing (equipment->armsWearable, getEngine()));
    getWidget<Label>("lblHandsItem")->setText(
            nameOrNothing (equipment->handsWearable, getEngine()));
    getWidget<Label>("lblLegsItem")->setText(
            nameOrNothing (equipment->legsWearable, getEngine()));
    getWidget<Label>("lblFeetItem")->setText(
            nameOrNothing (equipment->feetWearable, getEngine()));

    getWidget<Label>("lblSelectedItem")->setText(
            nameOrNothing (m_selectedItem, getEngine()));
}
