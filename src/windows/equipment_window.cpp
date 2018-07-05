#include "equipment_window.h"
#include "../components/description_component.h"
#include "../components/equipment_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"
#include "../core/game_engine.h"
#include "inspection_window.h"
#include "label.h"
#include "listbox.h"
#include "tab.h"

namespace {
const char* nameOrNothing(EntityId item, GameEngine* engine) {
    DescriptionComponent* description =
        engine->state()->components()->get<DescriptionComponent>(item);
    if (item == 0)
        return "<Nothing>";
    if (description == 0)
        return "?Something?";
    return description->title.c_str();
}

void selectItem(Label* l) {
    EntityId player = l->getWindow()->getState()->player();
    EquipmentComponent* equipment =
        l->getWindow()->getState()->components()->get<EquipmentComponent>(
            player);
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
    win->updateItemNames();
}

} // namespace

void EquipmentWindow::setup() {
    int width = 45;
    int height = 17;

    setTitle("Equipment");
    setHeight(height);
    setWidth(width);
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
    m_selectedItem = 0;
}

void EquipmentWindow::registerWidgets() {
    getWidget<Frame>("frmBase")->setMergeBorders();

    Tab* tab = createWidget<Tab>("tabEquipment", 1, 1);

    tab->setPageSwitchCallback([](Tab* t) {
        EquipmentWindow* win = dynamic_cast<EquipmentWindow*>(t->getWindow());

        if (t->getCurrentPage() == 0) {
            win->setSelectedItem(0);
        } else {
            ListBox* l = t->getWindow()->getWidget<ListBox>("lstRucksack");
            if (l->getItems().size()) {
                win->setSelectedItem(l->getSelectedItem().getValue());
            }
        }
        win->updateItemNames();
    });
    Frame* equipment = tab->addPage("Equipment")->getFrame();
    equipment->setMargin();

    createWidget<Label>("lblWielding", 0, 0, equipment)->setText("Wielding");
    createWidget<Label>("lblWearing", 0, 4, equipment)->setText("Wearing");

    createWidget<Label>("lblRight", 2, 1, equipment)
        ->setText("Right:")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblLeft", 2, 2, equipment)
        ->setText("Left :")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);

    createWidget<Label>("lblHead", 2, 5, equipment)
        ->setText("Head :")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblFace", 2, 6, equipment)
        ->setText("Face :")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblChest", 2, 7, equipment)
        ->setText("Chest:")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblArms", 2, 8, equipment)
        ->setText("Arms :")
        ->setCommandChar(1)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblHands", 2, 9, equipment)
        ->setText("Hands:")
        ->setCommandChar(3)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblLegs", 2, 10, equipment)
        ->setText("Legs :")
        ->setCommandChar(2)
        ->setCommandCharCallback(selectItem);
    createWidget<Label>("lblFeet", 2, 11, equipment)
        ->setText("Feet :")
        ->setCommandChar(4)
        ->setCommandCharCallback(selectItem);

    createWidget<Label>("lblRightItem", 9, 1, equipment);
    createWidget<Label>("lblLeftItem", 9, 2, equipment);
    createWidget<Label>("lblHeadItem", 9, 5, equipment);
    createWidget<Label>("lblFaceItem", 9, 6, equipment);
    createWidget<Label>("lblChestItem", 9, 7, equipment);
    createWidget<Label>("lblArmsItem", 9, 8, equipment);
    createWidget<Label>("lblHandsItem", 9, 9, equipment);
    createWidget<Label>("lblLegsItem", 9, 10, equipment);
    createWidget<Label>("lblFeetItem", 9, 11, equipment);

    createWidget<Label>("lblItemSelector", 1, 1, equipment)
        ->setText(">")
        ->setForegroundColor(Color(RED))
        ->setVisible(false);

    Widget* actions = createWidget<Frame>("frmActions", 0, 0)
                          ->setBorder()
                          ->setMargin()
                          ->setWidth(15)
                          ->setHeight(17)
                          ->setHorizontalAlign(Widget::HorizontalAlign::Right);

    createWidget<Label>("lblSelectItem", 0, 0, actions)
        ->setText("Select item")
        ->setVerticalAlign(Widget::VerticalAlign::Centre)
        ->setHorizontalAlign(Widget::HorizontalAlign::Left);

    createWidget<Label>("lblSelectedItem", 0, 2, actions)
        ->setText("")
        ->setVisible(false);

    createWidget<Label>("lblConsume", 0, 3, actions)
        ->setText("consume")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            GameEngine* engine = win->getEngine();

            ConsumeItemEvent* event = new ConsumeItemEvent();
            event->entity = getState()->player();
            event->item = getSelectedItem();
            setSelectedItem(0);
            getEngine()->raiseEvent(event);
            engine->swapTurn();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblInspect", 0, 2, actions)
        ->setText("inspect")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            GameEngine* engine = win->getEngine();
            auto args = std::make_shared<InspectionWindowArgs>();
            args->entity = win->getSelectedItem();
            engine->getWindows()->createWindow<InspectionWindow>(args);
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblUnequip", 0, 1, actions)
        ->setText("unequip")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            GameEngine* engine = win->getEngine();
            UnequipItemEvent* event = new UnequipItemEvent();
            event->entity = engine->state()->player();
            event->item = win->getSelectedItem();
            win->setSelectedItem(0);
            engine->raiseEvent(event);
            engine->swapTurn();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblEquip", 0, 1, actions)
        ->setText("equip")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            GameEngine* engine = win->getEngine();
            EquipItemEvent* event = new EquipItemEvent();
            event->entity = engine->state()->player();
            event->item = win->getSelectedItem();
            win->setSelectedItem(0);
            engine->raiseEvent(event);
            engine->swapTurn();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblDrop", 0, 0, actions)
        ->setText("drop")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            GameEngine* engine = win->getEngine();
            DropEquipmentEvent* event = new DropEquipmentEvent();
            event->entity = engine->state()->player();
            event->item = win->getSelectedItem();
            win->setSelectedItem(0);
            engine->raiseEvent(event);
            engine->swapTurn();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    Frame* rucksack = tab->addPage("Rucksack")->getFrame();
    createWidget<ListBox>("lstRucksack", 0, 0, rucksack)
        ->setItemSelectedCallback([](ListBox* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            win->setSelectedItem(l->getSelectedItem().getValue());
        })
        ->setHeight(10);

    updateItemNames();
}

void EquipmentWindow::setSelectedItem(EntityId item) {
    m_selectedItem = item;

    Tab* tab = getWidget<Tab>("tabEquipment");

    getWidget<Label>("lblItemSelector")->setVisible(m_selectedItem > 0);
    getWidget<Label>("lblSelectItem")->setVisible((m_selectedItem == 0));
    getWidget<Label>("lblSelectedItem")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblConsume")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblInspect")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblDrop")->setVisible((m_selectedItem > 0));
    getWidget<Label>("lblUnequip")
        ->setVisible((m_selectedItem > 0 && tab->getCurrentPage() == 0));
    getWidget<Label>("lblEquip")
        ->setVisible((m_selectedItem > 0 && tab->getCurrentPage() == 1));

    getWidget<Label>("lblSelectedItem")
        ->setText(nameOrNothing(m_selectedItem, getEngine()));
}

void EquipmentWindow::nextTurn() { updateItemNames(); }

void EquipmentWindow::updateItemNames() {
    EntityId player = getState()->player();
    EquipmentComponent* equipment =
        getState()->components()->get<EquipmentComponent>(player);

    getWidget<Label>("lblRightItem")
        ->setText(nameOrNothing(equipment->rightHandWieldable, getEngine()));
    getWidget<Label>("lblLeftItem")
        ->setText(nameOrNothing(equipment->leftHandWieldable, getEngine()));
    getWidget<Label>("lblHeadItem")
        ->setText(nameOrNothing(equipment->headWearable, getEngine()));
    getWidget<Label>("lblFaceItem")
        ->setText(nameOrNothing(equipment->faceWearable, getEngine()));
    getWidget<Label>("lblChestItem")
        ->setText(nameOrNothing(equipment->chestWearable, getEngine()));
    getWidget<Label>("lblArmsItem")
        ->setText(nameOrNothing(equipment->armsWearable, getEngine()));
    getWidget<Label>("lblHandsItem")
        ->setText(nameOrNothing(equipment->handsWearable, getEngine()));
    getWidget<Label>("lblLegsItem")
        ->setText(nameOrNothing(equipment->legsWearable, getEngine()));
    getWidget<Label>("lblFeetItem")
        ->setText(nameOrNothing(equipment->feetWearable, getEngine()));

    ListBox* list = getWidget<ListBox>("lstRucksack");
    list->clearItems();

    EquipmentComponent* carried =
        getEngine()->state()->components()->get<EquipmentComponent>(player);
    for (unsigned int ii = 0; ii < carried->carriedEquipment.size(); ii++) {
        ListBoxItem item;
        item.setText(nameOrNothing(carried->carriedEquipment[ii], getEngine()));
        item.setValue(carried->carriedEquipment[ii]);
        list->addItem(item);
    }
}
