#include "window.h"
#include "map_window.h"
#include "inspection_window.h"
#include "gameengine.h"
#include "event.h"

void MapWindow::gainFocus ()
{
    std::string l_mapName ("");
    getEngine()->loadMap(l_mapName);

    setTitle ("Map");

    m_mapXOffset = 1;
    m_mapYOffset = 9;
    m_mapStartX = 0;
    m_mapStartY = 0;
    m_mapWidth  = 20;
    m_mapHeight = 25;
    m_sidebarWidth = 20;
    m_sidebarXOffset = getWidth() - m_sidebarWidth;

    m_action = 'm';
}

void MapWindow::redraw() {
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
            std::vector<EntityId> l_entities = getEngine()->getEntities()->findEntitiesToThe(l_dir, getEngine()->getEntities()->getPlayer());
            if (l_entities.size() > 0) {
                EntityId* l_target = new EntityId(l_entities[0]);

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
}

void MapWindow::drawSeparators() {
    getEngine()->getGraphics()->drawBorder (m_mapYOffset-1, m_mapXOffset-1, m_mapHeight, m_mapWidth);
    getEngine()->getGraphics()->drawBorder (0, m_sidebarXOffset, getHeight()-2, m_sidebarWidth-1);
}

void MapWindow::drawMap() {

    std::map<EntityId, SpriteComponent>& l_sprites = getEngine()->getEntities()->getSprites()->getAll();
    std::map<EntityId, SpriteComponent>::iterator it = l_sprites.begin();
    LocationComponent* l_player = getEngine()->getEntities()->getLocations()->get (getEngine()->getEntities()->getPlayer());
    if (l_player) {
        m_mapStartX = l_player->x - (m_mapWidth/2);
        m_mapStartY = l_player->y - (m_mapHeight/2);
    }
    for (; it != l_sprites.end(); it++) {
        SpriteComponent& l_sprite = it->second;
        LocationComponent* l_location = getEngine()->getEntities()->getLocations()->get (it->first);
        int x = l_location->x;
        int y = l_location->y;
        int xWidth = m_mapStartX + m_mapWidth;
        int yWidth = m_mapStartY + m_mapHeight;
        if (x >= m_mapStartX && x < xWidth &&
            y >= m_mapStartY && y < yWidth &&
            l_location->z == getEngine()->getLevel()) {

            drawTile (  l_location->y + m_mapYOffset - m_mapStartY,
                        l_location->x + m_mapXOffset - m_mapStartX,
                        l_sprite.sprite,
                        l_sprite.fgColor,
                        l_sprite.bgColor);
        }
    }
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

    drawString (getHeight()-2, m_sidebarXOffset+2, "View Inventory");
    drawString (getHeight()-2, m_sidebarXOffset+2, "V", Color (GREEN));
}

void MapWindow::drawProgressBar (int x, int y, int value)
{
    float l_value = (float) value;
    Color l_color ((1.0f-(l_value/10.0f)), l_value/10.0f, 0);

    for (int xx = 0; xx < value; xx++) {
        drawTile (y, x+xx, 178, l_color, Color(BLACK));
    }
}
