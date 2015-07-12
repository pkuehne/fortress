#include "window.h"
#include "map_window.h"
#include "gameengine.h"
#include "event.h"

void MapWindow::initialise(GameEngineInterface* a_engine) {
    Window::initialise (a_engine);

    std::string l_mapName ("");
    getEngine()->loadMap(l_mapName);
}

void MapWindow::redraw() {

    if (getKey(27)) exit (0);

    drawMap();
}

void MapWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    enum MoveEntityEvent::DIRECTION l_dir = MoveEntityEvent::NONE;
    switch (key) {
        case 'w': l_dir = MoveEntityEvent::UP; break;
        case 'a': l_dir = MoveEntityEvent::LEFT; break;
        case 's': l_dir = MoveEntityEvent::DOWN; break;
        case 'd': l_dir = MoveEntityEvent::RIGHT; break;
        case 27: getEngine()->quit(); break;
    }
    if (l_dir != MoveEntityEvent::NONE) {
        MoveEntityEvent* l_event = new MoveEntityEvent;
        l_event->entity = getEngine()->getEntities()->getEntity("Player");
        l_event->direction = l_dir;
        getEngine()->raiseEvent (l_event);
    }
}

void MapWindow::drawMap() {

    std::map<Entity*, SpriteComponent>& l_sprites = getEngine()->getEntities()->getSprites()->getAll();
    std::map<Entity*, SpriteComponent>::iterator it = l_sprites.begin();
    for (; it != l_sprites.end(); it++) {
        SpriteComponent& l_sprite = it->second;
        //std::cout << "Drawing Tile" << std::endl;
        getEngine()->getGraphics()->drawTile (l_sprite.yPos, l_sprite.xPos, l_sprite.sprite, l_sprite.fgColor, l_sprite.bgColor);
    }
}
