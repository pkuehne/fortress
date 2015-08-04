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
}

void MapWindow::redraw() {
    drawSeparators();
    drawMap();
}

void MapWindow::resize() {
    setDimensions (0, 0, getEngine()->getGraphics()->getScreenWidth(), getEngine()->getGraphics()->getScreenHeight());
    m_mapWidth  = getWidth() - m_mapXOffset - 1;
    m_mapHeight = getHeight() - m_mapYOffset - 1;
}

void MapWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    static char action = 'm';

    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        DIRECTION l_dir = Direction::None;
        switch (key) {
            case 'w': l_dir = Direction::North; break;
            case 'a': l_dir = Direction::West;  break;
            case 's': l_dir = Direction::South; break;
            case 'd': l_dir = Direction::East;  break;
        }

        if (action == 'm') {
            MoveEntityEvent* l_event = new MoveEntityEvent;
            l_event->entity = getEngine()->getEntities()->getPlayer()->getId();
            l_event->direction = l_dir;
            getEngine()->raiseEvent (l_event);
        }
        if (action == 'k') {
            AttackEntityEvent* l_event = new AttackEntityEvent;
            l_event->entity = getEngine()->getEntities()->getPlayer()->getId();
            l_event->direction = l_dir;
            getEngine()->raiseEvent (l_event);
        }
        if (action == 'i') {

            std::vector<EntityId> l_entities = getEngine()->getEntities()->findEntitiesToThe(l_dir, getEngine()->getEntities()->getPlayer());
            if (l_entities.size() > 0) {
                EntityId* l_target = new EntityId(l_entities[0]);

                InspectionWindow* l_win = new InspectionWindow();
                l_win->initialise(getEngine(), l_target);
                getEngine()->getWindows()->pushWindow (l_win);
            }
        }
        if (action != 'i') getEngine()->swapTurn();
        action = 'm';
    }
    if (key == 27) {
        getEngine()->quit();
    }
    if (key == 'm') {
        action = 'm';
    }
    if (key == 'k') {
        action = 'k';
    }
    if (key == 'i') {
        action = 'i';
    }
    if (key == '.') {
        getEngine()->swapTurn();
    }
}

void MapWindow::drawSeparators() {
    getEngine()->getGraphics()->drawBorder (m_mapYOffset-1, m_mapXOffset-1, m_mapHeight, m_mapWidth);
}

void MapWindow::drawMap() {

    std::map<EntityId, SpriteComponent>& l_sprites = getEngine()->getEntities()->getSprites()->getAll();
    std::map<EntityId, SpriteComponent>::iterator it = l_sprites.begin();
    SpriteComponent* l_player = getEngine()->getEntities()->getSprites()->get (getEngine()->getEntities()->getPlayer()->getId());
    if (l_player) {
        m_mapStartX = l_player->xPos - (m_mapWidth/2);
        m_mapStartY = l_player->yPos - (m_mapHeight/2);
    }
    for (; it != l_sprites.end(); it++) {
        SpriteComponent& l_sprite = it->second;
        int x = l_sprite.xPos;
        int y = l_sprite.yPos;
        int xWidth = m_mapStartX + m_mapWidth;
        int yWidth = m_mapStartY + m_mapHeight;
        if (x >= m_mapStartX && x < xWidth &&
            y >= m_mapStartY && y < yWidth) {

            drawTile (  l_sprite.yPos + m_mapYOffset - m_mapStartY,
                        l_sprite.xPos + m_mapXOffset - m_mapStartX,
                        l_sprite.sprite,
                        l_sprite.fgColor,
                        l_sprite.bgColor);
        }
    }
}
