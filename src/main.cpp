#include "gameengine.h"
#include <GL/glut.h>

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    std::string l_map("testmap.txt");
    if (argc > 1) {
        l_map = argv[1];
    }

    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->loadMap (l_map);
    l_engine->start();

    return 0;
}
