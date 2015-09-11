#include "window.h"
#include "map_window.h"
#include "inspection_window.h"
#include "equipment_window.h"
#include "gameengine.h"
#include "event.h"


void MapWindow::gainFocus ()
{
    getEngine()->loadMap(50, 50);

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
}

void MapWindow::redraw() {

    //clock_t l_clock = clock() - m_lastDraw;
    //double l_diff = static_cast<double> (l_clock/CLOCKS_PER_SEC);
    //if (l_diff < 0.01f) return;

    drawSeparators();
    drawMap();
    drawMessages();
    drawSidebar();
}

void MapWindow::resize() {
    setDimensions (0, 0, getEngine()->getGraphics()->getScreenWidth(), getEngine()->getGraphics()->getScreenHeight());
    m_sidebarXOffset = getWidth() - m_sidebarWidth - 1;
    m_mapWidth  = getWidth() - m_mapXOffset - m_sidebarWidth - 1;
    m_mapHeight = getHeight() - m_mapYOffset - 1;
}

void MapWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        DIRECTION l_dir = Direction::None;
        switch (key) {
            case 'w': l_dir = Direction::North; break;
            case 'a': l_dir = Direction::West;  break;
            case 's': l_dir = Direction::South; break;
            case 'd': l_dir = Direction::East;  break;
        }

        if (m_action == 'm') {
            MoveEntityEvent* l_event = new MoveEntityEvent;
            l_event->entity = getEngine()->getEntities()->getPlayer();
            l_event->direction = l_dir;
            getEngine()->raiseEvent (l_event);
        }
        if (m_action == 'k') {
            AttackEntityEvent* l_event = new AttackEntityEvent;
            l_event->entity = getEngine()->getEntities()->getPlayer();
            l_event->direction = l_dir;
            getEngine()->raiseEvent (l_event);
        }
        if (m_action == 'i') {
            EntityHolder l_entities = getEngine()->getEntities()->findEntitiesToThe(l_dir, getEngine()->getEntities()->getPlayer());
            if (l_entities.size() > 0) {
                EntityId* l_target = new EntityId(*l_entities.begin());

                InspectionWindow* l_win = new InspectionWindow();
                l_win->initialise(getEngine(), l_target);
                getEngine()->getWindows()->pushWindow (l_win);
            }
        }
        if (m_action != 'i') getEngine()->swapTurn();
        m_action = 'm';
    }
    if (key == 27) {
        getEngine()->quit();
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
        Location l_playerLoc = getEngine()->getEntities()->getLocation(getEngine()->getEntities()->getPlayer());
        EntityHolder l_entities = getEngine()->getEntities()->findEntitiesAt (l_playerLoc.x, l_playerLoc.y);
        bool foundSomethingAlready = false;
        for (EntityId l_entity : l_entities) {
            DroppableComponent* droppable = getEngine()->getEntities()->getDroppables()->get(l_entity);
            if (droppable) {
                if (!foundSomethingAlready) {
                    PickupEquipmentEvent* event = new PickupEquipmentEvent();
                    event->entity = getEngine()->getEntities()->getPlayer();
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
}

void MapWindow::drawSeparators() {
    getEngine()->getGraphics()->drawBorder (m_mapYOffset-1, m_mapXOffset-1, m_mapHeight, m_mapWidth);
    getEngine()->getGraphics()->drawBorder (0, m_sidebarXOffset, getHeight()-2, m_sidebarWidth-1);
}

void MapWindow::drawMap() {
    Location l_player = getEngine()->getEntities()->getLocation(getEngine()->getEntities()->getPlayer());
    m_mapStartX = l_player.x - (m_mapWidth/2);
    m_mapStartY = l_player.y - (m_mapHeight/2);

    int xWidth = m_mapStartX + m_mapWidth;
    int yWidth = m_mapStartY + m_mapHeight;

    for (int yy = m_mapStartY; yy < yWidth; yy++) {
        for (int xx = m_mapStartX; xx < xWidth; xx++) {
            if (!getEngine()->isValidTile (xx, yy, getEngine()->getLevel())) continue;
            Tile& l_tile = getEngine()->getTile (xx, yy, getEngine()->getLevel());
            for (EntityId entity : l_tile.entities) {
                SpriteComponent* l_sprite= getEngine()->getEntities()->getSprites()->get (entity);
                if (!l_sprite) continue;
                Color fgColor = l_sprite->fgColor;
                if (    xx < (int)l_player.x - 3 || xx > (int)l_player.x + 3
                    ||  yy < (int)l_player.y - 3 || yy > (int)l_player.y + 3) {
                    fgColor.Red()   *= 0.4;
                    fgColor.Green() *= 0.4;
                    fgColor.Blue()  *= 0.4;
                }
                drawTile (  yy + m_mapYOffset - m_mapStartY,
                            xx + m_mapXOffset - m_mapStartX,
                            l_sprite->sprite,
                            fgColor,
                            l_sprite->bgColor);

            }
        }
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
        drawString (hh, 1, l_messages[ii-1].message.c_str(), fg);
    }
}

void MapWindow::drawSidebar ()
{
    // Current health
    drawString (2, m_sidebarXOffset+2, "Health:");
    EntityId player = getEngine()->getEntities()->getPlayer();
    HealthComponent* l_health = getEngine()->getEntities()->getHealths()->get(player);
    if (l_health) {
        drawProgressBar (m_sidebarXOffset+10, 2, l_health->health);

    }

    // Actions to take
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
    float l_value = (float) value;
    Color l_color ((1.0f-(l_value/10.0f)), l_value/10.0f, 0);

    for (int xx = 0; xx < value; xx++) {
        drawTile (y, x+xx, 178, l_color, Color(BLACK));
    }
}
