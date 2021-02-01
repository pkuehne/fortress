#include "interaction_window.h"
#include "../components/debug_component.h"
#include "../components/equipment_component.h"
#include "../components/key_component.h"
#include "../components/player_component.h"
#include "../core/component_manager.h"
#include "../core/entity_manager.h"
#include "../core/event_manager.h"
#include "../widgets/frame.h"
#include "../widgets/label.h"
#include "../widgets/listbox.h"
#include "dialog_window.h"
#include "inspection_window.h"

void InteractionWindow::setup() {
    setTitle("Interact");
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void InteractionWindow::registerWidgets() {
    unsigned int descriptionWidth = 5;
    const unsigned int commandWidth = 10;
    const unsigned int windowHeight = 10;

    getWidget<Frame>("frmBase")->setMergeBorders();

    Frame* frmEntityList = createWidget<Frame>("frmEntityList", 0, 0);
    ListBox* lstEntities =
        createWidget<ListBox>("lstEntities", 0, 0, frmEntityList);
    lstEntities->setItemSelectedCallback(std::bind(
        &InteractionWindow::listSelection, this, std::placeholders::_1));
    lstEntities->setWidthStretchMargin(0)->setHeightStretchMargin(0);
    lstEntities->clearItems();

    for (EntityId entity : m_inputEntities) {
        ComponentStore store;
        store.desc = components()->get<DescriptionComponent>(entity);
        store.open = components()->get<OpenableComponent>(entity);
        store.drop = components()->get<DroppableComponent>(entity);
        store.npc = components()->get<NpcComponent>(entity);
        auto debug = components()->getUnique<DebugComponent>().component;

        std::string title = store.desc ? store.desc->title : "<Unknown>";
        if (debug != nullptr) {
            title.append(" (" + std::to_string(entity) + ")");
        }
        descriptionWidth = title.length() > descriptionWidth ? title.length()
                                                             : descriptionWidth;

        ListBoxItem item;
        item.setText(title);
        lstEntities->addItem(item);
        m_entities.push_back(entity);
        m_components.push_back(store);
    }

    descriptionWidth += 5;
    frmEntityList->setMargin()
        ->setBorder()
        ->setWidth(descriptionWidth)
        ->setHeight(windowHeight);

    createWidget<Label>("txtInspect", descriptionWidth, 1)
        ->setText("inspect")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            ListBox* lstEntities = this->getWidget<ListBox>("lstEntities");
            EntityId entity = m_entities[lstEntities->getSelection()];
            events()->fire(std::make_shared<RegisterWindowEvent>(
                std::make_shared<InspectionWindow>(entity)));
        })
        ->setSensitive(false);
    createWidget<Label>("txtOpen", descriptionWidth, 2)
        ->setText("open")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            ListBox* lstEntities = this->getWidget<ListBox>("lstEntities");
            EntityId entity = m_entities[lstEntities->getSelection()];
            const ComponentStore& store =
                m_components[lstEntities->getSelection()];

            if (store.open->open) {
                events()->fire(std::make_shared<CloseEntityEvent>(entity));
            } else if (store.open->locked) {
                events()->fire(
                    std::make_shared<AddLogMessageEvent>("It's locked!"));
            } else {
                events()->fire(std::make_shared<OpenEntityEvent>(entity));
            }
            events()->fire(std::make_shared<EndTurnEvent>());
        })
        ->setSensitive(false);
    createWidget<Label>("txtTalk", descriptionWidth, 3)
        ->setText("talk")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            ListBox* lstEntities = this->getWidget<ListBox>("lstEntities");
            EntityId entity = m_entities[lstEntities->getSelection()];
            auto player = components()->getUnique<PlayerComponent>();
            events()->fire(
                std::make_shared<StartConversationEvent>(player.id, entity));
        })
        ->setSensitive(false);
    createWidget<Label>("txtDrop", descriptionWidth, 4)
        ->setText("pickup")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            ListBox* lstEntities = this->getWidget<ListBox>("lstEntities");
            EntityId entity = m_entities[lstEntities->getSelection()];
            auto player = components()->getUnique<PlayerComponent>();
            events()->fire(
                std::make_shared<PickupEquipmentEvent>(player.id, entity));
            events()->fire(std::make_shared<EndTurnEvent>());
        })
        ->setSensitive(false);
    createWidget<Label>("txtLock", descriptionWidth, 5)
        ->setText("lock")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            Defer d([this]() {
                this->events()->fire(std::make_shared<EndTurnEvent>());
            });
            ListBox* lstEntities = this->getWidget<ListBox>("lstEntities");
            EntityId lock = m_entities[lstEntities->getSelection()];
            auto player = components()->getUnique<PlayerComponent>();
            auto equipment = components()->get<EquipmentComponent>(player.id);
            if (!equipment) {
                events()->fire(std::make_shared<AddLogMessageEvent>(
                    "You don't carry any equipement"));
                return;
            }
            const ComponentStore& store =
                m_components[lstEntities->getSelection()];

            for (auto item : equipment->carriedEquipment) {
                if (components()->get<KeyComponent>(item)) {
                    if (store.open->locked) {
                        events()->fire(
                            std::make_shared<UnlockEntityEvent>(item, lock));
                    } else {
                        events()->fire(
                            std::make_shared<LockEntityEvent>(item, lock));
                    }
                    return;
                }
            }
            events()->fire(std::make_shared<AddLogMessageEvent>(
                "None of your equipment can be used as a key"));
        })
        ->setSensitive(false);

    setHeight(windowHeight);
    setWidth(descriptionWidth + commandWidth);
    lstEntities->setSelection(0);
}

void InteractionWindow::updateScreen() {
    ListBox* lstEntities = getWidget<ListBox>("lstEntities");
    Label* txtInspect = getWidget<Label>("txtInspect");
    Label* txtOpen = getWidget<Label>("txtOpen");
    Label* txtDrop = getWidget<Label>("txtDrop");
    Label* txtTalk = getWidget<Label>("txtTalk");
    Label* txtLock = getWidget<Label>("txtLock");

    const ComponentStore& store = m_components[lstEntities->getSelection()];

    txtInspect->setSensitive(store.desc != nullptr);
    txtOpen->setSensitive(store.open != nullptr);
    txtDrop->setSensitive(store.drop != nullptr);
    txtTalk->setSensitive(store.npc != nullptr);
    txtLock->setSensitive(store.open != nullptr);

    if (store.desc) {
        setTitle(store.desc->title);
    }
    if (store.open) {
        txtOpen->setText(store.open->open ? "close" : "open");
        txtLock->setText(store.open->locked ? "unlock" : "lock");
    }
}

void InteractionWindow::listSelection(ListBox* box) { updateScreen(); }

void InteractionWindow::nextTurn() { updateScreen(); }