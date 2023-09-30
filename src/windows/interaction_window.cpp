#include "interaction_window.h"
#include "../components/debug_component.h"
#include "../components/equipment_component.h"
#include "../components/key_component.h"
#include "../components/player_component.h"
#include "../core/component_manager.h"
#include "../core/entity_manager.h"
#include "../core/event_manager.h"
#include "../core/yaml_converter.h"
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
    bool debug = entities()->world().lookup("player").has<DebugComponent>();

    getWidget<Frame>("frmBase")->setMergeBorders();

    Frame* frmEntityList = createWidget<Frame>("frmEntityList", 0, 0);
    ListBox* lstEntities =
        createWidget<ListBox>("lstEntities", 0, 0, frmEntityList);
    lstEntities->setItemSelectedCallback(std::bind(
        &InteractionWindow::listSelection, this, std::placeholders::_1));
    lstEntities->setWidthStretchMargin(0)->setHeightStretchMargin(0);
    lstEntities->clearItems();

    for (EntityId entity : m_inputEntities) {
        auto e = entities()->world().entity(entity);

        ComponentStore store;
        store.desc = e.has<DescriptionComponent>()
                         ? e.get_mut<DescriptionComponent>()
                         : nullptr;
        store.open = e.has<OpenableComponent>() ? e.get_mut<OpenableComponent>()
                                                : nullptr;
        store.drop = e.has<DroppableComponent>()
                         ? e.get_mut<DroppableComponent>()
                         : nullptr;
        store.npc = e.has<NpcComponent>() ? e.get_mut<NpcComponent>() : nullptr;

        std::string title = store.desc ? store.desc->title : "<Unknown>";
        if (debug) {
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
            events()->fire<AddWindowEvent<InspectionWindow>>(entity);
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
                events()->fire<CloseEntityEvent>(entity);
            } else if (store.open->locked) {
                events()->fire<AddLogMessageEvent>("It's locked!");
            } else {
                events()->fire<OpenEntityEvent>(entity);
            }
            events()->fire<EndTurnEvent>();
        })
        ->setSensitive(false);
    createWidget<Label>("txtTalk", descriptionWidth, 3)
        ->setText("talk")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            ListBox* lstEntities = this->getWidget<ListBox>("lstEntities");
            EntityId entity = m_entities[lstEntities->getSelection()];
            auto player = entities()->world().lookup("player");
            events()->fire<StartConversationEvent>(player.id(), entity);
        })
        ->setSensitive(false);
    createWidget<Label>("txtDrop", descriptionWidth, 4)
        ->setText("pickup")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            ListBox* lstEntities = this->getWidget<ListBox>("lstEntities");
            EntityId entity = m_entities[lstEntities->getSelection()];
            auto player = entities()->world().lookup("player");
            events()->fire<PickupEquipmentEvent>(player.id(), entity);
            events()->fire<EndTurnEvent>();
        })
        ->setSensitive(false);
    createWidget<Label>("txtLock", descriptionWidth, 5)
        ->setText("lock")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            Defer d([this]() { this->events()->fire<EndTurnEvent>(); });
            ListBox* lstEntities = this->getWidget<ListBox>("lstEntities");
            EntityId lock = m_entities[lstEntities->getSelection()];
            auto player = entities()->world().lookup("player");
            auto equipment = player.get<EquipmentComponent>();
            if (!equipment) {
                events()->fire<AddLogMessageEvent>(
                    "You don't carry any equipement");
                return;
            }
            const ComponentStore& store =
                m_components[lstEntities->getSelection()];

            for (auto e : equipment->carriedEquipment) {
                auto item = entities()->world().entity(e);
                if (item.has<KeyComponent>()) {
                    if (store.open->locked) {
                        events()->fire<UnlockEntityEvent>(item, lock);
                    } else {
                        events()->fire<LockEntityEvent>(item, lock);
                    }
                    return;
                }
            }
            events()->fire<AddLogMessageEvent>(
                "None of your equipment can be used as a key");
        })
        ->setSensitive(false);
    createWidget<Label>("txtDump", descriptionWidth, 6)
        ->setText("dump")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            YamlConverter converter(entities(), components());
            YAML::Node node;
            ListBox* lstEntities = getWidget<ListBox>("lstEntities");
            EntityId entity = m_entities[lstEntities->getSelection()];

            converter.encodeEntity(node, entity);
            std::cout << node << std::endl;
            events()->fire<AddLogMessageEvent>(
                "Entity " + std::to_string(entity) + " dumped to stdout");
            events()->fire<EndTurnEvent>();
        })
        ->setSensitive(true)
        ->setVisible(debug);

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