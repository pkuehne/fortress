#include "window.h"
#include "map_window.h"
#include "inspection_window.h"
#include "equipment_window.h"
#include "selection_window.h"
#include "escape_window.h"
#include "game_engine.h"
#include "event.h"
#include "sprite_component.h"
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
                if (getEngine()->state()->components()->get<NpcComponent>(entity)) {
                    AttackEntityEvent* l_event = new AttackEntityEvent;
                    l_event->attacker = playerId;
                    l_event->defender = entity;
                    getEngine()->raiseEvent (l_event);
                }
            }
        }
        if (m_action == 'i') {
            EntityHolder l_entities = getEngine()->state()->map()->findEntitiesAt(newLocation);
            if (l_entities.size() > 0) {
                SelectionWindow* selWin = new SelectionWindow();
                selWin->initialise (getEngine(), &l_entities);
                getEngine()->getWindows()->pushWindow (selWin);
            }
        }
        if (m_action != 'i') getEngine()->swapTurn();
        m_action = 'm';
    }
    if (key == KEY_ESC) {
        EscapeWindow* menu = new EscapeWindow();
        menu->initialise (getEngine());
        getEngine()->getWindows()->pushWindow (menu);
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
                    getEngine()->addMessage(INFO, "There's something else here...");
                    break;
                }
            }
        }
        if (!foundSomethingAlready) {
            getEngine()->addMessage(INFO, "There's nothing here...");
        }
    }
    if (key == 'E') {
        EquipmentWindow* l_win = new EquipmentWindow();
        l_win->initialise(getEngine());
        getEngine()->getWindows()->pushWindow (l_win);
    }
    if (key == 'S') {
        FileSaver saver;
        saver.initialise (getEngine());
        saver.saveState();
        getEngine()->addMessage (INFO, "Game saved!");
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

    int xWidth = m_mapStartX + m_mapWidth;
    int yWidth = m_mapStartY + m_mapHeight;

    for (int yy = m_mapStartY; yy < yWidth; yy++) {
        for (int xx = m_mapStartX; xx < xWidth; xx++) {
            Location loc (xx, yy, l_player.z);
            if (!getEngine()->state()->isValidTile (loc)) continue;
            Tile& l_tile = getEngine()->state()->tile(loc);

            std::map<unsigned int, std::vector<SpriteComponent*> > l_sprites;
            for (EntityId entity : l_tile.entities()) {
                SpriteComponent* l_sprite = getEngine()->state()->components()->get<SpriteComponent> (entity);
                if (!l_sprite) continue;
                l_sprites[l_sprite->renderLayer].push_back (l_sprite);
            }
            l_sprites[0].push_back (&(l_tile.getFloor().getSprite()));

            for (auto& layer : l_sprites) {
                for (SpriteComponent* l_sprite : layer.second) {
                    Color fgColor = l_sprite->fgColor;
                    if (l_tile.lastVisited < getEngine()->getTurn()) {
                        fgColor *= 0.4;
                    }

                    if (l_tile.lastVisited > 0 && l_tile.lastVisited + 200 > getEngine()->getTurn()) {
                        drawTile (  yy + m_mapYOffset - m_mapStartY,
                                xx + m_mapXOffset - m_mapStartX,
                                l_sprite->sprite,
                                fgColor,
                                l_sprite->bgColor);
                    }
                }
            }
        }
    }
    if (m_debugMode) {
        // Show NPC paths
        for (EntityId entity : getEngine()->state()->entities()) {
            Location loc = getEngine()->state()->location(entity);
            int x = loc.x;
            int y = loc.y;
            if (x < m_mapStartX || x > xWidth || y < m_mapStartY || y > yWidth) continue;
            NpcComponent* npc = getEngine()->state()->components()->get<NpcComponent> (entity);
            if (npc) {
                for (Location stepLoc : npc->path) {
                    drawTile (  stepLoc.y + m_mapYOffset - m_mapStartY,
                            stepLoc.x + m_mapXOffset - m_mapStartX,
                            '+',
                            Color (RED),
                            Color (BLACK));
                }
            }
        }
    } else {
        //
    }

    return;
}

void MapWindow::drawMessages()
{
    std::vector<Message>& l_messages = getEngine()->getMessages();
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
    drawString (getHeight()-10, m_sidebarXOffset+2, "Save Game");
    drawString (getHeight()-10, m_sidebarXOffset+2, "S", Color (GREEN));

    drawString (getHeight()-8, m_sidebarXOffset+2, "pickup Items");
    drawString (getHeight()-8, m_sidebarXOffset+2, "p", Color (GREEN));

    drawString (getHeight()-7, m_sidebarXOffset+2, "move (wasd)");
    drawString (getHeight()-7, m_sidebarXOffset+2, "m", Color (GREEN));
    if (m_action == 'm') drawString (getHeight()-7, m_sidebarXOffset+1, ">", Color (RED));

    drawString (getHeight()-6, m_sidebarXOffset+2, "attack (wasd)");
    drawString (getHeight()-6, m_sidebarXOffset+7, "k", Color (GREEN));
    if (m_action == 'k') drawString (getHeight()-6, m_sidebarXOffset+1, ">", Color (RED));

    drawString (getHeight()-5, m_sidebarXOffset+2, "inspect (wasd)");
    drawString (getHeight()-5, m_sidebarXOffset+2, "i", Color (GREEN));
    if (m_action == 'i') drawString (getHeight()-5, m_sidebarXOffset+1, ">", Color (RED));

    drawString (getHeight()-4, m_sidebarXOffset+2, "skip turn (.)");
    drawString (getHeight()-4, m_sidebarXOffset+13, ".", Color (GREEN));

    drawString (getHeight()-2, m_sidebarXOffset+2, "View Equipment");
    drawString (getHeight()-2, m_sidebarXOffset+7, "E", Color (GREEN));
}

void MapWindow::drawProgressBar (int x, int y, int value)
{
    for (int xx = 0; xx < value; xx++) {
        drawTile (y, x+xx, 178, Color (GREEN), Color(BLACK));
    }
}
