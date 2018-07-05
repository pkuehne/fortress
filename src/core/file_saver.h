#ifndef FILE_SAVER
#define FILE_SAVER

#include "../components/component_base.h"
#include <fstream>
#include <iostream>

class GameEngine;
class FileSaver {
public:
    void initialise(GameEngine* engine) { m_engine = engine; }
    void saveState();
    void saveComponent(ComponentBase* component);

private:
    GameEngine* m_engine;
    std::ofstream m_file;
};

#endif
