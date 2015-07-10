#include "gameengine.h"
#include <GL/glut.h>
#include <iostream>
#include <execinfo.h>
#include <signal.h>

void handler (int signal) {
    const unsigned int  numFrames   = 100;
    void* frames[numFrames]         = {0};
    size_t stackSize                = backtrace (frames, numFrames);
    char** symbols                  = 0;

    std::cerr << "!!!CRASH!!! Caught Segmentation Violation: " << signal << std::endl;
    symbols = backtrace_symbols (frames, stackSize);
    if (symbols == 0) {
        std::cerr << "Failed to load back trace symbols!" << std::endl;
        exit (1);
    }

    for (unsigned int ii = 0; ii < stackSize; ii++) {
        std::cerr << ii << ". " << symbols[ii] << std::endl;
    }

    exit(1);
}


int main (int argc, char** argv)
{
    // Install Segmentation Fault handler
    signal(SIGSEGV, handler);

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
