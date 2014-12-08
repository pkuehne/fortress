#include "gameengine.h"

int main (int argc, char** argv)
{
    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->getMap();

    return 0;
}
