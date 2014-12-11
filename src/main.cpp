#include "gameengine.h"
#include <GL/glut.h>

int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    std::string l_map("../maps/test1.map");
    if (argc > 1) {
        l_map = argv[1];
    }

    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->loadMap (l_map);
    l_engine->execute();

    return 0;
}
