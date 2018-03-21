#include "equipment_window.h"
#include "inspection_window.h"
#include "label.h"
#include "tab.h"
#include "listbox.h"
#include "../core/game_engine.h"
#include "../components/equipment_component.h"
#include "../components/description_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"

namespace
{
const char *nameOrNothing(EntityId item, GameEngine *engine)
{
    DescriptionComponent *description = engine->state()->components()->get<DescriptionComponent>(item);
    if (item == 0)
        return "<Nothing>";
    if (description == 0)
        return "?Something?";
    return description->title.c_str();
}

void selectItem(Label *l)
{
    EntityId player = l->getWindow()->getState()->player();
    EquipmentComponent *equipment =
        l->getWindow()->getState()->components()->get<EquipmentComponent>(player);
    EquipmentWindow *win = dynamic_cast<EquipmentWindow *>(l->getWindow());

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
    if (win->itemSelected())
    {
        Label *s = win->getWidget<Label>("lblItemSelector");
        s->setY(l->getY());
        s->setVisible(true);
    }
}

} // Close namespace

void EquipmentWindow::setup()
{
    int width = 45;
    int height = 17;

    setTitle("Equipment");
    setHeight(height);
    setWidth(width);
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
    m_selectedItem = 0;
}

void EquipmentWindow::registerWidgets()
{
    Tab *tab = createWidget<Tab>("tabEquipment", 1, 1);
    tab->setPageSwitchCallback([](Tab *t) {
        dynamic_cast<EquipmentWindow *>(t->getWindow())->setSelectedItem(0);
    });
    Frame *equipment = tab->addPage("Equipment")->getFrame();

    createWidget<Label>("lblWielding", 2, 4, equipment)->setText("Wielding");
    createWidget<Label>("lblWearing", 2, 8, equipment)->setText("Wearing");

    createWidget<Label>("lblRight", 4, 5, equipment)
        ->setText("Right:")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblLeft", 4, 6, equipment)
        ->setText("Left :")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);

    createWidget<Label>("lblHead", 4, 9, equipment)
        ->setText("Head :")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblFace", 4, 10, equipment)
        ->setText("Face :")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblChest", 4, 11, equipment)
        ->setText("Chest:")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblArms", 4, 12, equipment)
        ->setText("Arms :")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblHands", 4, 13, equipment)
        ->setText("Hands:")
        ->setCommandChar(3)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblLegs", 4, 14, equipment)
        ->setText("Legs :")
        ->setCommandChar(2)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblFeet", 4, 15, equipment)
        ->setText("Feet :")
        ->setCommandChar(4)
        ->setCommandCharCallback(selectItem);

    createWidget<Label>("lblLeftItem", 11, 6, equipment);
    createWidget<Label>("lblRightItem", 11, 5, equipment);
    createWidget<Label>("lblHeadItem", 11, 9, equipment);
    createWidget<Label>("lblFaceItem", 11, 10, equipment);
    createWidget<Label>("lblChestItem", 11, 11, equipment);
    createWidget<Label>("lblArmsItem", 11, 12, equipment);
    createWidget<Label>("lblHandsItem", 11, 13, equipment);
    createWidget<Label>("lblLegsItem", 11, 14, equipment);
    createWidget<Label>("lblFeetItem", 11, 15, equipment);

    createWidget<Label>("lblItemSelector", 3, 5, equipment)
        ->setText(">")
        ->setForegroundColor(Color(RED))
        ->setVisible(false);

    createWidget<Label>("lblSelectItem", 2, 0, equipment)
        ->setText("Select item")
        ->setVerticalAlign(Widget::VerticalAlign::Centre)
        ->setHorizontalAlign(Widget::HorizontalAlign::Right);

    createWidget<Label>("lblSelectedItem", 29, 2, equipment)
        ->setText("")
        ->setVisible(false);

    createWidget<Label>("lblConsume", 29, 3)
        ->setText("consume")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label *l) {
            EquipmentWindow *win = dynamic_cast<EquipmentWindow *>(l->getWindow());
            GameEngine *engine = win->getEngine();
            ConsumeItemEvent *event = new ConsumeItemEvent();
            event->entity = engine->state()->player();
            event->item = win->getSelectedItem();
            win->setSelectedItem(0);
            engine->raiseEvent(event);
            engine->swapTurn();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblInspect", 29, 2)
        ->setText("inspect")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label *l) {
            EquipmentWindow *win = dynamic_cast<EquipmentWindow *>(l->getWindow());
            GameEngine *engine = win->getEngine();
            EntityId *l_target = new EntityId(win->getSelectedItem());
            engine->getWindows()->createWindow<InspectionWindow>(l_target);
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblUnequip", 29, 1)
        ->setText("unequip")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label *l) {
            EquipmentWindow *win = dynamic_cast<EquipmentWindow *>(l->getWindow());
            GameEngine *engine = win->getEngine();
            UnequipItemEvent *event = new UnequipItemEvent();
            event->entity = engine->state()->player();
            event->item = win->getSelectedItem();
            win->setSelectedItem(0);
            engine->raiseEvent(event);
            engine->swapTurn();
            win->updateItemNames();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblEquip", 29, 1)
        ->setText("equip")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label *l) {
            EquipmentWindow *win = dynamic_cast<EquipmentWindow *>(l->getWindow());
            GameEngine *engine = win->getEngine();
            EquipItemEvent *event = new EquipItemEvent();
            event->entity = engine->state()->player();
            event->item = win->getSelectedItem();
            win->setSelectedItem(0);
            engine->raiseEvent(event);
            engine->swapTurn();
            win->updateItemNames();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblDrop", 29, 0)
        ->setText("drop")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label *l) {
            EquipmentWindow *win = dynamic_cast<EquipmentWindow *>(l->getWindow());
            GameEngine *engine = win->getEngine();
            DropEquipmentEvent *event = new DropEquipmentEvent();
            event->entity = engine->state()->player();
            event->item = win->getSelectedItem();
            win->setSelectedItem(0);
            engine->raiseEvent(event);
            engine->swapTurn();
            win->updateItemNames();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    Frame *rucksack = tab->addPage("Rucksack")->getFrame();
    createWidget<ListBox>("lstRucksack", 1, 3, rucksack);

    updateItemNames();
}

void EquipmentWindow::setSelectedItem(EntityId item)
{
    m_selectedItem = item;

    Tab *tab = getWidget<Tab>("tabEquipment");

    getWidget<Label>("lblSelectItem")->setVisible((m_selectedItem == 0));
    getWidget<Label>("lblSelectedItem")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblConsume")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblInspect")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblDrop")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblUnequip")->setVisible((m_selectedItem > 0 && tab->getSelection() == 0));
    getWidget<Label>("lblEquip")->setVisible((m_selectedItem > 0 && tab->getSelection() == 1));

    updateItemNames();
}

void EquipmentWindow::updateItemNames()
{
    EntityId player = getState()->player();
    EquipmentComponent *equipment =
        getState()->components()->get<EquipmentComponent>(player);

    getWidget<Label>("lblRightItem")->setText(nameOrNothing(equipment->rightHandWieldable, getEngine()));
    getWidget<Label>("lblLeftItem")->setText(nameOrNothing(equipment->leftHandWieldable, getEngine()));
    getWidget<Label>("lblHeadItem")->setText(nameOrNothing(equipment->headWearable, getEngine()));
    getWidget<Label>("lblFaceItem")->setText(nameOrNothing(equipment->faceWearable, getEngine()));
    getWidget<Label>("lblChestItem")->setText(nameOrNothing(equipment->chestWearable, getEngine()));
    getWidget<Label>("lblArmsItem")->setText(nameOrNothing(equipment->armsWearable, getEngine()));
    getWidget<Label>("lblHandsItem")->setText(nameOrNothing(equipment->handsWearable, getEngine()));
    getWidget<Label>("lblLegsItem")->setText(nameOrNothing(equipment->legsWearable, getEngine()));
    getWidget<Label>("lblFeetItem")->setText(nameOrNothing(equipment->feetWearable, getEngine()));

    getWidget<Label>("lblSelectedItem")->setText(nameOrNothing(m_selectedItem, getEngine()));

    ListBox *list = getWidget<ListBox>("lstRucksack");

    EquipmentComponent *carried = getEngine()->state()->components()->get<EquipmentComponent>(player);
    for (unsigned int ii = 0; ii < carried->carriedEquipment.size(); ii++)
    {
        list->items.push_back(nameOrNothing(carried->carriedEquipment[ii], getEngine()));
    }
}
