#include "window.h"
#include "map_window.h"
#include "inspection_window.h"
#include "gameengine.h"
#include "event.h"

void MapWindow::initialise(GameEngineInterface* a_engine) {
    Window::initialise (a_engine);

    std::string l_mapName ("");
    getEngine()->loadMap(l_mapName);
}

void MapWindow::redraw() {

    //if (getKey(27)) exit (0);

    drawMap();
}

void MapWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    static char action = 'm';

    if (key == 'w' || key == 'a' || key == 's' || key == 'd') {
        DIRECTION l_dir = Direction::None;
        switch (key) {
            case 'w': l_dir = Direction::North; break;
            case 'a': l_dir = Direction::West; break;
            case 's': l_dir = Direction::South; break;
            case 'd': l_dir = Direction::East; break;
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
        getEngine()->swapTurn();
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

void MapWindow::drawMap() {

    std::map<EntityId, SpriteComponent>& l_sprites = getEngine()->getEntities()->getSprites()->getAll();
    std::map<EntityId, SpriteComponent>::iterator it = l_sprites.begin();
    for (; it != l_sprites.end(); it++) {
        SpriteComponent& l_sprite = it->second;
        //std::cout << "Drawing Tile" << std::endl;
        getEngine()->getGraphics()->drawTile (l_sprite.yPos, l_sprite.xPos, l_sprite.sprite, l_sprite.fgColor, l_sprite.bgColor);
    }
}
