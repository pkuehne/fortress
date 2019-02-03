#include "map_window.h"
#include "../algos/fov_algorithm.h"
#include "../components/droppable_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/health_component.h"
#include "../components/logmessage_component.h"
#include "../components/npc_component.h"
#include "../core/event.h"
#include "../core/game_engine.h"
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
            [&](Label* l) { l->getWindow()->getEngine()->swapTurn(); })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblEquipment", 1, 2, sidebar)
        ->setText("View Equipment")
        ->setCommandChar(6)
        ->setCommandCharCallback([&](Label* l) {
            events()->raise(std::make_shared<RegisterWindowEvent>(
                std::make_shared<EquipmentWindow>()));
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblQuests", 1, 3, sidebar)
        ->setText("View Quests")
        ->setCommandChar(6)
        ->setCommandCharCallback([&](Label* l) {
            events()->raise(std::make_shared<RegisterWindowEvent>(
                std::make_shared<QuestWindow>()));
        })
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
        ->setGameState(getState())
        ->setHeightStretchMargin(0)
        ->setWidthStretchMargin(m_sidebarWidth);

    createWidget<Label>("lblTileSizeIncr", 0, 0)
        ->setText("]")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            unsigned int height = getEngine()->getGraphics()->getTileHeight();
            unsigned int width = getEngine()->getGraphics()->getTileWidth();
            getEngine()->getGraphics()->updateTileSize(width + 1, height + 1);
            getEngine()->getWindows()->resize();
        })
        ->setVisible(false);
    createWidget<Label>("lblTileSizeDecr", 0, 0)
        ->setText("[")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            unsigned int height = getEngine()->getGraphics()->getTileHeight();
            unsigned int width = getEngine()->getGraphics()->getTileWidth();
            getEngine()->getGraphics()->updateTileSize(width - 1, height - 1);
            getEngine()->getWindows()->resize();
        })
        ->setVisible(false);
    createWidget<Label>("lblDebugWindow", 0, 0)
        ->setText("`")
        ->setCommandChar(1)
        ->setCommandCharCallback([&](Label* l) {
            events()->raise(std::make_shared<RegisterWindowEvent>(
                std::make_shared<DebugWindow>()));
        })
        ->setVisible(false);

    getEngine()->swapTurn();
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
    EntityId playerId = getEngine()->state()->player();
    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        Location oldLocation = getEngine()->state()->location(playerId);
        Location newLocation = oldLocation;
        updateLocation(key, newLocation);

        if (m_action == 'm') {
            events()->raise(
                std::make_shared<MoveEntityEvent>(playerId, newLocation));

            getEngine()->swapTurn();
        } else if (m_action == 'k') {
            EntityHolder l_entities = map()->findEntitiesAt(newLocation);
            for (EntityId entity : l_entities) {
                events()->raise(
                    std::make_shared<AttackEntityEvent>(playerId, entity));
            }
            getEngine()->swapTurn();
        } else if (m_action == 'i') {
            EntityHolder l_entities = map()->findEntitiesAt(newLocation);
            if (l_entities.size() > 0) {
                events()->raise(std::make_shared<RegisterWindowEvent>(
                    std::make_shared<InteractionWindow>(l_entities)));
            }
        }
        m_action = 'm';
    } else if (key == KEY_ESC) {
        events()->raise(std::make_shared<RegisterWindowEvent>(
            std::make_shared<EscapeWindow>()));
    }
    // std::cout << "Key: " << key << std::endl;
}

void MapWindow::nextTurn() {
    EntityId player = getEngine()->state()->player();
    if (!player) {
        return;
    }
    HealthComponent* l_health = components()->get<HealthComponent>(player);
    if (!l_health) {
        throw std::string("Player must have a health component!");
    }
    getWidget<ProgressBar>("pgbHealth")->setValue(l_health->health);
    getWidget<ProgressBar>("pgbHunger")->setValue(l_health->hunger);
    getWidget<ProgressBar>("pgbThirst")->setValue(l_health->thirst);

    auto l_messages = components()->get<LogMessageComponent>(player);
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