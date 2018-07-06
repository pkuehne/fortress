#include "map_window.h"
#include "../algos/fov_algorithm.h"
#include "../components/droppable_component.h"
#include "../components/graphics_effect_component.h"
#include "../components/health_component.h"
#include "../components/npc_component.h"
#include "../core/event.h"
#include "../core/game_engine.h"
#include "debug_window.h"
#include "equipment_window.h"
#include "escape_window.h"
#include "inspection_window.h"
#include "interaction_window.h"
#include "quest_window.h"
#include "window.h"

#include "camera.h"
#include "frame.h"
#include "label.h"
#include "listbox.h"
#include "progress_bar.h"

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
            [](Label* l) { l->getWindow()->getEngine()->swapTurn(); })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblEquipment", 1, 2, sidebar)
        ->setText("View Equipment")
        ->setCommandChar(6)
        ->setCommandCharCallback([](Label* l) {
            l->getWindow()
                ->getEngine()
                ->getWindows()
                ->createWindow<EquipmentWindow>();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblQuests", 1, 3, sidebar)
        ->setText("View Quests")
        ->setCommandChar(6)
        ->setCommandCharCallback([](Label* l) {
            l->getWindow()
                ->getEngine()
                ->getWindows()
                ->createWindow<QuestWindow>();
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

    getEngine()->swapTurn();
}

void MapWindow::setAction(char action, unsigned int yPos) {
    m_action = action;
    getWidget<Label>("lblAction")->setY(yPos);
    resize();
}

void MapWindow::keyPress(unsigned char key) {
    EntityId playerId = getEngine()->state()->player();
    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        Location oldLocation = getEngine()->state()->location(playerId);
        Location newLocation = oldLocation;
        switch (key) {
            case 'w':
                newLocation.y--;
                break;
            case 'a':
                newLocation.x--;
                break;
            case 's':
                newLocation.y++;
                break;
            case 'd':
                newLocation.x++;
                break;
        }

        if (m_action == 'm') {
            MoveEntityEvent* l_event = new MoveEntityEvent;
            l_event->entity = playerId;
            l_event->newLocation = newLocation;
            getEngine()->raiseEvent(l_event);
        }
        if (m_action == 'k') {
            EntityHolder l_entities =
                getEngine()->state()->map()->findEntitiesAt(newLocation);
            for (EntityId entity : l_entities) {
                AttackEntityEvent* l_event = new AttackEntityEvent;
                l_event->attacker = playerId;
                l_event->defender = entity;
                getEngine()->raiseEvent(l_event);
            }
        }
        if (m_action == 'i') {
            EntityHolder l_entities =
                getEngine()->state()->map()->findEntitiesAt(newLocation);
            if (l_entities.size() > 0) {

                auto interactArgs = std::make_shared<InteractionWindowArgs>();
                interactArgs->entities = l_entities;
                getEngine()->getWindows()->createWindow<InteractionWindow>(
                    interactArgs);
            }
        }
        if (m_action != 'i')
            getEngine()->swapTurn();
        m_action = 'm';
    }
    if (key == KEY_ESC) {
        getEngine()->getWindows()->createWindow<EscapeWindow>();
    }
    if (key == '[') {
        unsigned int height = getEngine()->getGraphics()->getTileHeight();
        unsigned int width = getEngine()->getGraphics()->getTileWidth();
        getEngine()->getGraphics()->updateTileSize(width - 1, height - 1);
        getEngine()->getWindows()->resize();
    }
    if (key == ']') {
        unsigned int height = getEngine()->getGraphics()->getTileHeight();
        unsigned int width = getEngine()->getGraphics()->getTileWidth();
        getEngine()->getGraphics()->updateTileSize(width + 1, height + 1);
        getEngine()->getWindows()->resize();
    }
    if (key == '`') {
        getEngine()->getWindows()->createWindow<DebugWindow>();
    }

    // std::cout << "Key: " << key << std::endl;
}

void MapWindow::nextTurn() {
    EntityId player = getEngine()->state()->player();
    HealthComponent* l_health =
        getEngine()->state()->components()->get<HealthComponent>(player);
    if (!l_health) {
        throw std::string("Player must have a health component!");
    }
    getWidget<ProgressBar>("pgbHealth")->setValue(l_health->health);
    getWidget<ProgressBar>("pgbHunger")->setValue(l_health->hunger);
    getWidget<ProgressBar>("pgbThirst")->setValue(l_health->thirst);

    std::vector<Message>& l_messages = getEngine()->state()->getMessages();
    ListBox* list = getWidget<ListBox>("lstMessages");

    list->clearItems();
    for (auto message : l_messages) {
        ListBoxItem item;
        item.setText(message.message);
        item.setColor(message.getColor());
        list->addItem(item);
    }
    list->scrollToBottom();
}