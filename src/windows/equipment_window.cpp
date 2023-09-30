#include "equipment_window.h"
#include "../components/description_component.h"
#include "../components/equipment_component.h"
#include "../components/player_component.h"
#include "../components/wearable_component.h"
#include "../components/wieldable_component.h"
#include "../core/component_manager.h"
#include "../core/entity_manager.h"
#include "../widgets/label.h"
#include "../widgets/listbox.h"
#include "../widgets/tab.h"
#include "inspection_window.h"

const char* EquipmentWindow::nameOrNothing(EntityId item) {
    if (item == 0)
        return "<Nothing>";
    auto description =
        entities()->world().entity(item).get<DescriptionComponent>();
    if (description == 0)
        return "?Something?";
    return description->title.c_str();
}

void EquipmentWindow::selectItem(Label* l) {
    auto player = entities()->world().lookup("player");
    auto equipment = player.get<EquipmentComponent>();
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

    auto selectItem = [&](Label* l) { this->selectItem(l); };
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
            events()->fire<ConsumeItemEvent>(
                entities()->world().lookup("player").id(), getSelectedItem());
            setSelectedItem(0);

            events()->fire<EndTurnEvent>();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblInspect", 0, 2, actions)
        ->setText("inspect")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            EntityId item = getSelectedItem();
            events()->fire<AddWindowEvent<InspectionWindow>>(item);
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblUnequip", 0, 1, actions)
        ->setText("unequip")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            events()->fire<UnequipItemEvent>(
                entities()->world().lookup("player").id(),
                win->getSelectedItem());
            win->setSelectedItem(0);
            events()->fire<EndTurnEvent>();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblEquip", 0, 1, actions)
        ->setText("equip")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            events()->fire<EquipItemEvent>(
                entities()->world().lookup("player").id(),
                win->getSelectedItem());
            win->setSelectedItem(0);
            events()->fire<EndTurnEvent>();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setVisible(false);

    createWidget<Label>("lblDrop", 0, 0, actions)
        ->setText("drop")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            EquipmentWindow* win =
                dynamic_cast<EquipmentWindow*>(l->getWindow());
            events()->fire<DropEquipmentEvent>(
                entities()->world().lookup("player").id(),
                win->getSelectedItem());
            win->setSelectedItem(0);
            events()->fire<EndTurnEvent>();
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

    getWidget<Label>("lblSelectedItem")->setText(nameOrNothing(m_selectedItem));
}

void EquipmentWindow::nextTurn() { updateItemNames(); }

void EquipmentWindow::updateItemNames() {
    auto player = entities()->world().lookup("player");
    auto equipment = player.get<EquipmentComponent>();

    getWidget<Label>("lblRightItem")
        ->setText(nameOrNothing(equipment->rightHandWieldable));
    getWidget<Label>("lblLeftItem")
        ->setText(nameOrNothing(equipment->leftHandWieldable));
    getWidget<Label>("lblHeadItem")
        ->setText(nameOrNothing(equipment->headWearable));
    getWidget<Label>("lblFaceItem")
        ->setText(nameOrNothing(equipment->faceWearable));
    getWidget<Label>("lblChestItem")
        ->setText(nameOrNothing(equipment->chestWearable));
    getWidget<Label>("lblArmsItem")
        ->setText(nameOrNothing(equipment->armsWearable));
    getWidget<Label>("lblHandsItem")
        ->setText(nameOrNothing(equipment->handsWearable));
    getWidget<Label>("lblLegsItem")
        ->setText(nameOrNothing(equipment->legsWearable));
    getWidget<Label>("lblFeetItem")
        ->setText(nameOrNothing(equipment->feetWearable));

    ListBox* list = getWidget<ListBox>("lstRucksack");
    list->clearItems();

    for (unsigned int ii = 0; ii < equipment->carriedEquipment.size(); ii++) {
        ListBoxItem item;
        item.setText(nameOrNothing(equipment->carriedEquipment[ii]));
        item.setValue(equipment->carriedEquipment[ii]);
        list->addItem(item);
    }
}
