#include "window.h"
#include "map_window.h"
#include "gameengine.h"
#include "event.h"
#include <cstdlib>

void MapWindow::initialise() {
    std::string l_mapName ("");

    GameEngine* l_engine = GameEngine::getEngine();
    std::cout << "Loading map: " << l_mapName << std::endl;
    l_engine->loadMap(l_mapName);
}

void MapWindow::redraw() {

    if (getKey(27)) exit (0);

    drawMap();
    drawLog();
}

void MapWindow::keyDown (unsigned char key) {
    Window::keyDown (key);

    GameEngine* l_engine = GameEngine::getEngine();
    enum MoveEntityEvent::DIRECTION l_dir = MoveEntityEvent::NONE;
    switch (key) {
        case 'w': l_dir = MoveEntityEvent::UP; break;
        case 'a': l_dir = MoveEntityEvent::LEFT; break;
        case 's': l_dir = MoveEntityEvent::DOWN; break;
        case 'd': l_dir = MoveEntityEvent::RIGHT; break;
        case 27: exit(0); break;
    }
    if (l_dir != MoveEntityEvent::NONE) {
        MoveEntityEvent* l_event = new MoveEntityEvent;
        l_event->entity = l_engine->getEntities().getEntity("Player");
        l_event->direction = l_dir;
        l_engine->raiseEvent (l_event);
    }
}

void MapWindow::drawMap() {
    GameEngine* l_engine = GameEngine::getEngine();
    //std::cout << "Updating Graphics System" << std::endl;
    std::map<Entity*, SpriteComponent>& l_sprites = l_engine->getEntities().getSprites().getAll();
    std::map<Entity*, SpriteComponent>::iterator it = l_sprites.begin();
    for (; it != l_sprites.end(); it++) {
        SpriteComponent& l_sprite = it->second;
        //std::cout << "Drawing Tile" << std::endl;
        drawTile (l_sprite.yPos, l_sprite.xPos, l_sprite.sprite, l_sprite.fgColor, l_sprite.bgColor);
    }
}

void MapWindow::drawLog() {
    drawBorder (1, 1, 10, 20);
}
