#include "map_window.h"
#include "../components/droppable_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/health_component.h"
#include "../components/logmessage_component.h"
#include "../components/npc_component.h"
#include "../components/player_component.h"
#include "../core/component_manager.h"
#include "../core/entity_manager.h"
#include "../core/event.h"
#include "../core/event_manager.h"
#include "../widgets/camera.h"
#include "../widgets/frame.h"
#include "../widgets/label.h"
#include "../widgets/listbox.h"
#include "../widgets/progress_bar.h"
#include "debug_window.h"
#include "equipment_window.h"
#include "escape_window.h"
#include "inspection_window.h"
#include "interaction_window.h"
#include "quest_window.h"
#include "window.h"

void MapWindow::setup() {
    setTitle("Map");
    setFullscreen();

    m_sidebarWidth = 20;
    m_messagesHeight = 9;

    m_action = 'm';
}

void MapWindow::registerWidgets() {
    getWidget<Frame>("frmBase")->setMergeBorders();

    Frame* sidebar = createWidget<Frame>("frmSidebar", 0, 0);
    sidebar->setBorder()
        ->setMargin()
        ->setWidth(m_sidebarWidth + 1)
        ->setHeightStretchMargin(0)
        ->setHorizontalAlign(Widget::HorizontalAlign::Right);
    createWidget<Label>("lblHealth", 0, 0, sidebar)->setText("Health:");
    createWidget<ProgressBar>("pgbHealth", 8, 0, sidebar)
        ->setMaxValue(10)
        ->setWidth(9);
    createWidget<Label>("lblHunger", 0, 1, sidebar)->setText("Hunger:");
    createWidget<ProgressBar>("pgbHunger", 8, 1, sidebar)
        ->setMaxValue(10)
        ->setWidth(9);
    createWidget<Label>("lblThirst", 0, 2, sidebar)->setText("Thirst:");
    createWidget<ProgressBar>("pgbThirst", 8, 2, sidebar)
        ->setMaxValue(10)
        ->setWidth(9);

    createWidget<Label>("lblSkipTurn", 1, 0, sidebar)
        ->setText("Skip Turn (.)")
        ->setCommandChar(12)
        ->setCommandCharCallback(
            [&](Label* l) { events()->fire<EndTurnEvent>(); })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblEquipment", 1, 2, sidebar)
        ->setText("View Equipment")
        ->setCommandChar(6)
        ->setCommandCharCallback([&](Label* l) {
            events()->fire<AddWindowEvent<EquipmentWindow>>();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblQuests", 1, 3, sidebar)
        ->setText("View Quests")
        ->setCommandChar(6)
        ->setCommandCharCallback(
            [&](Label* l) { events()->fire<AddWindowEvent<QuestWindow>>(); })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);

    createWidget<Label>("lblInteract", 1, 5, sidebar)
        ->setText("interact (wasd)")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label* l) {
            MapWindow* win = dynamic_cast<MapWindow*>(l->getWindow());
            win->setAction('i', l->getY());
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);

    createWidget<Label>("lblAttack", 1, 6, sidebar)
        ->setText("attack (wasd)")
        ->setCommandChar(6)
        ->setCommandCharCallback([](Label* l) {
            MapWindow* win = dynamic_cast<MapWindow*>(l->getWindow());
            win->setAction('k', l->getY());
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblMove", 1, 7, sidebar)
        ->setText("move (wasd)")
        ->setCommandChar(1)
        ->setCommandCharCallback([](Label* l) {
            MapWindow* win = dynamic_cast<MapWindow*>(l->getWindow());
            win->setAction('m', l->getY());
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblAction", 0, 7, sidebar)
        ->setText(">")
        ->setForegroundColor(Color(RED))
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);

    Frame* messages = createWidget<Frame>("frmMessages", 0, 0);
    messages->setBorder()
        ->setMargin()
        ->setWidthStretchMargin(m_sidebarWidth)
        ->setHeight(m_messagesHeight);
    createWidget<ListBox>("lstMessages", 0, 0, messages)
        ->setWidthStretchMargin(0)
        ->setHeightStretchMargin(0)
        ->setSensitive(false);

    createWidget<Camera>("camCamera", 0, m_messagesHeight)
        ->setManagerRefs(entities(), components(), map())
        ->setHeightStretchMargin(0)
        ->setWidthStretchMargin(m_sidebarWidth);

    createWidget<Label>("lblTileSizeIncr", 0, 0)
        ->setText("]")
        ->setCommandChar(1)
        ->setCommandCharCallback(
            [this](Label* l) { this->events()->fire<UpdateTileSizeEvent>(1); })
        ->setVisible(false);
    createWidget<Label>("lblTileSizeDecr", 0, 0)
        ->setText("[")
        ->setCommandChar(1)
        ->setCommandCharCallback(
            [this](Label* l) { this->events()->fire<UpdateTileSizeEvent>(-1); })
        ->setVisible(false);
    createWidget<Label>("lblDebugWindow", 0, 0)
        ->setText("`")
        ->setCommandChar(1)
        ->setCommandCharCallback(
            [&](Label* l) { events()->fire<AddWindowEvent<DebugWindow>>(); })
        ->setVisible(false);

    events()->fire<EndTurnEvent>();
}

void MapWindow::setAction(char action, unsigned int yPos) {
    m_action = action;
    getWidget<Label>("lblAction")->setY(yPos);
    resize();
}

void updateLocation(unsigned char key, Location& location) {
    if (key == 'w') {
        location.y--;
    } else if (key == 'a') {
        location.x--;
    } else if (key == 's') {
        location.y++;
    } else if (key == 'd') {
        location.x++;
    }
}

void MapWindow::keyPress(unsigned char key) {
    auto player = components()->getUnique<PlayerComponent>();
    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        Location oldLocation = entities()->getLocation(player.id);
        Location newLocation = oldLocation;
        updateLocation(key, newLocation);

        if (m_action == 'm') {
            events()->fire<MoveEntityEvent>(player.id, newLocation);

            events()->fire<EndTurnEvent>();
        } else if (m_action == 'k') {
            EntityHolder l_entities = map()->findEntitiesAt(newLocation);
            for (EntityId entity : l_entities) {
                events()->fire<AttackEntityEvent>(player.id, entity);
            }
            events()->fire<EndTurnEvent>();
        } else if (m_action == 'i') {
            EntityHolder l_entities = map()->findEntitiesAt(newLocation);
            if (l_entities.size() > 0) {
                events()->fire<AddWindowEvent<InteractionWindow>>(l_entities);
            }
        }
        m_action = 'm';
    } else if (key == KEY_ESC) {
        events()->fire<AddWindowEvent<EscapeWindow>>();
    }
    // std::cout << "Key: " << key << std::endl;
}

void MapWindow::nextTurn() {
    auto player = components()->getUnique<PlayerComponent>();
    if (player.id == 0) {
        return;
    }
    HealthComponent* l_health = components()->get<HealthComponent>(player.id);
    if (!l_health) {
        throw std::string("Player must have a health component!");
    }
    getWidget<ProgressBar>("pgbHealth")->setValue(l_health->health);
    getWidget<ProgressBar>("pgbHunger")->setValue(l_health->hunger);
    getWidget<ProgressBar>("pgbThirst")->setValue(l_health->thirst);

    auto l_messages = components()->get<LogMessageComponent>(player.id);
    if (!l_messages) {
        return;
    }
    ListBox* list = getWidget<ListBox>("lstMessages");
    list->clearItems();
    for (auto message : l_messages->messages) {
        ListBoxItem item;
        item.setText(message.message);
        item.setColor(Color(WHITE));
        list->addItem(item);
    }
    list->scrollToBottom();
}