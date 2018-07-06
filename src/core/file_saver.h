#ifndef FILE_SAVER
#define FILE_SAVER

#include "../components/component_base.h"
#include <fstream>
#include <iostream>

class GameEngine;
class FileSaver {
public:
    FileSaver() {}
    ~FileSaver() {}
    void initialise(GameEngine* engine) { m_engine = engine; }
    // void saveState();

private:
    GameEngine* m_engine = 0;
    std::ofstream m_file;
};

#endif
