#include "window.h"
#include "camera.h"
#include "map_window.h"
#include "inspection_window.h"
#include "equipment_window.h"
#include "selection_window.h"
#include "escape_window.h"
#include "debug_window.h"
#include "quest_window.h"
#include "game_engine.h"
#include "event.h"
#include "health_component.h"
#include "droppable_component.h"
#include "graphics_effect_component.h"
#include "npc_component.h"
#include "file_saver.h"
#include "file_loader.h"
#include "fov_algorithm.h"

void MapWindow::gainFocus ()
{
    setTitle ("Map");

    m_mapXOffset = 1;
    m_mapYOffset = 9;
    m_mapStartX = 0;
    m_mapStartY = 0;
    m_mapWidth  = 0;
    m_mapHeight = 0;
    m_sidebarWidth = 20;
    m_sidebarXOffset = getWidth() - m_sidebarWidth;

    m_action = 'm';
    m_lastDraw = clock();
    m_debugMode = false;

    FovAlgorithm l_algo;
    l_algo.initialise (getEngine());
    l_algo.calculateFov();

    m_camera = new Camera (getEngine()->getGraphics(), getEngine()->state());
    std::cout << "Map gain focus" << std::endl;
}

void MapWindow::redraw()
{
    drawSeparators();
    drawMap();
    drawMessages();
    drawSidebar();
}

void MapWindow::resize()
{
    setDimensions (0, 0, getEngine()->getGraphics()->getScreenWidth(), getEngine()->getGraphics()->getScreenHeight());
    m_sidebarXOffset = getWidth() - m_sidebarWidth - 1;
    m_mapWidth  = getWidth() - m_mapXOffset - m_sidebarWidth - 1;
    m_mapHeight = getHeight() - m_mapYOffset - 1;

    m_camera->viewport().width = m_mapWidth;
    m_camera->viewport().height = m_mapHeight;
    m_camera->viewport().x = m_mapXOffset;
    m_camera->viewport().y = m_mapYOffset;
}

void MapWindow::keyDown (unsigned char key)
{
    Window::keyDown (key);
    EntityId playerId = getEngine()->state()->player();
    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        Location oldLocation = getEngine()->state()->location(playerId);
        Location newLocation = oldLocation;
        switch (key) {
            case 'w': newLocation.y--; break;
            case 'a': newLocation.x--;  break;
            case 's': newLocation.y++; break;
            case 'd': newLocation.x++;  break;
        }

        if (m_action == 'm') {
            MoveEntityEvent* l_event = new MoveEntityEvent;
            l_event->entity = playerId;
            l_event->newLocation = newLocation;
            getEngine()->raiseEvent (l_event);
        }
        if (m_action == 'k') {
            EntityHolder l_entities = getEngine()->state()->map()->findEntitiesAt(newLocation);
            for (EntityId entity : l_entities) {
                //if (getEngine()->state()->components()->get<NpcComponent>(entity)) {
                AttackEntityEvent* l_event = new AttackEntityEvent;
                l_event->attacker = playerId;
                l_event->defender = entity;
                getEngine()->raiseEvent (l_event);
                //}
            }
        }
        if (m_action == 'i') {
            EntityHolder l_entities = getEngine()->state()->map()->findEntitiesAt(newLocation);
            if (l_entities.size() > 0) {
                getEngine()->getWindows()->pushWindow (
                        getEngine()->getWindows()->createWindow<SelectionWindow>(
                            &l_entities));
            }
        }
        if (m_action != 'i') getEngine()->swapTurn();
        m_action = 'm';
    }
    if (key == KEY_ESC) {
        getEngine()->getWindows()->pushWindow (
                getEngine()->getWindows()->createWindow<EscapeWindow>());
    }
    if (key == 'm' ||
            key == 'k' ||
            key == 'i') {
        m_action = key;
    }
    if (key == '.') {
        getEngine()->swapTurn();
    }
    if (key == 'p') {
        Location l_playerLoc = getEngine()->state()->location(playerId);
        EntityHolder l_entities = getEngine()->state()->map()->findEntitiesAt (l_playerLoc);
        bool foundSomethingAlready = false;
        for (EntityId l_entity : l_entities) {
            DroppableComponent* droppable = getEngine()->state()->components()->get<DroppableComponent>(l_entity);
            if (droppable) {
                if (!foundSomethingAlready) {
                    PickupEquipmentEvent* event = new PickupEquipmentEvent();
                    event->entity = playerId;
                    event->item = l_entity;
                    getEngine()->raiseEvent (event);
                    foundSomethingAlready = true;
                } else {
                    getEngine()->state()->addMessage(INFO, "There's something else here...");
                    break;
                }
            }
        }
        if (!foundSomethingAlready) {
            getEngine()->state()->addMessage(INFO, "There's nothing here...");
        }
    }
    if (key == 'E') {
        getEngine()->getWindows()->pushWindow (
                getEngine()->getWindows()->createWindow<EquipmentWindow>());
    }
    if (key == 'S') {
        FileSaver saver;
        saver.initialise (getEngine());
        saver.saveState();
        getEngine()->state()->addMessage (INFO, "Game saved!");
    }
    if (key == '=') {
        std::cout << "Switching debug mode" << std::endl;
        m_debugMode = !m_debugMode;
        EntityId player = getEngine()->state()->player();
        GraphicsEffectComponent* effect =
            getEngine()->state()->components()->make<GraphicsEffectComponent>(player);
        effect->type = EFFECT_BLINK_FAST;
        effect->duration = 20;

    }
    if (key == 'q') {
        getEngine()->getWindows()->pushWindow(
                getEngine()->getWindows()->createWindow<QuestWindow>());
    }
    if (key == '[') {
        unsigned int height = getEngine()->getGraphics()->getTileHeight();
        unsigned int width = getEngine()->getGraphics()->getTileWidth();
        getEngine()->getGraphics()->updateTileSize(width-1, height-1);
        getEngine()->getWindows()->resize();
    }
    if (key == ']') {
        unsigned int height = getEngine()->getGraphics()->getTileHeight();
        unsigned int width = getEngine()->getGraphics()->getTileWidth();
        getEngine()->getGraphics()->updateTileSize(width+1, height+1);
        getEngine()->getWindows()->resize();
    }
    if (key == '`') {
        getEngine()->getWindows()->pushWindow (
                getEngine()->getWindows()->createWindow<DebugWindow>());
    }

    //std::cout << "Key: " << key << std::endl;
}

void MapWindow::drawSeparators()
{
    getEngine()->getGraphics()->drawBorder (m_mapYOffset-1, m_mapXOffset-1, m_mapHeight, m_mapWidth);
    getEngine()->getGraphics()->drawBorder (0, m_sidebarXOffset, getHeight()-2, m_sidebarWidth-1);
}

void MapWindow::drawMap()
{
    Location l_player = getEngine()->state()->location (
            getEngine()->state()->player());

    m_mapStartX = l_player.x - (m_mapWidth/2);
    m_mapStartY = l_player.y - (m_mapHeight/2);

    m_camera->setMapOffset (m_mapStartX, m_mapStartY, l_player.z);
    m_camera->render();

    return;
}

void MapWindow::drawMessages()
{
    std::vector<Message>& l_messages = getEngine()->state()->getMessages();
    size_t ii = l_messages.size();
    size_t hh = m_mapYOffset-2;

    for (; ii > 0 && hh > 0; hh--, ii--) {
        Color fg;
        switch (l_messages[ii-1].severity) {
            case INFO: fg = Color (WHITE); break;
            case WARN: fg = Color (RED); break;
            case GOOD: fg = Color (GREEN); break;
            case CRIT: fg = Color (BLUE); break;
        }
        std::vector<std::string> lines;
        wrapText (l_messages[ii-1].message, lines, m_sidebarXOffset, 1);
        drawString (hh, 1, lines[0].c_str(), fg);
    }
}

void MapWindow::drawSidebar ()
{
    // Current health
    drawString (2, m_sidebarXOffset+2, "Health:");
    drawString (3, m_sidebarXOffset+2, "Hunger:");
    drawString (4, m_sidebarXOffset+2, "Thirst:");
    EntityId player = getEngine()->state()->player();
    HealthComponent* l_health = getEngine()->state()->components()->get<HealthComponent>(player);
    if (l_health) {
        drawProgressBar (m_sidebarXOffset+10, 2, l_health->health);
        drawProgressBar (m_sidebarXOffset+10, 3, l_health->hunger);
        drawProgressBar (m_sidebarXOffset+10, 4, l_health->thirst);
    }

    // Actions to take
    drawCommandString(getHeight()-10, m_sidebarXOffset+2, "Save Game", 0);

    drawCommandString(getHeight()-8, m_sidebarXOffset+2, "pickup Items", 0);

    drawCommandString(getHeight()-7, m_sidebarXOffset+2, "move (wasd)", 0);
    if (m_action == 'm') {
        drawString (getHeight()-7, m_sidebarXOffset+1, ">", Color (RED));
    }

    drawCommandString(getHeight()-6, m_sidebarXOffset+2, "attack (wasd)", 5);
    if (m_action == 'k') {
        drawString (getHeight()-6, m_sidebarXOffset+1, ">", Color (RED));
    }

    drawCommandString(getHeight()-5, m_sidebarXOffset+2, "inspect (wasd)", 0);
    if (m_action == 'i') {
        drawString (getHeight()-5, m_sidebarXOffset+1, ">", Color (RED));
    }

    drawCommandString(getHeight()-4, m_sidebarXOffset+2, "skip turn (.)", 11);

    drawCommandString(getHeight()-2, m_sidebarXOffset+2, "View Equipment", 5);
}

void MapWindow::drawProgressBar (int x, int y, int value)
{
    for (int xx = 0; xx < value; xx++) {
        drawTile (y, x+xx, 178, Color (GREEN), Color(BLACK));
    }
}
