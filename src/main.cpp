#include "gameengine.h"
#include <GL/glut.h>
#include <iostream>

int main (int argc, char** argv)
{
    try {
        glutInit (&argc, argv);
        std::string l_map("testmap.txt");
        if (argc > 1) {
            l_map = argv[1];
        }

        GameEngine* l_engine = GameEngine::getEngine();
        l_engine->initialise();
        l_engine->start();
    } catch (char const * err) {
        std::cout << err << std::endl;
    }
    return 0;
}
