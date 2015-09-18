#ifndef FILE_SAVER
#define FILE_SAVER

#include "game_engine_interface.h"
#include "component_base.h"
#include <fstream>
#include <iostream>

class FileSaver {
public:
    void initialise (GameEngineInterface* engine) { m_engine = engine; }
    void saveState ();
    void saveComponent(ComponentBase* component);

private:
    GameEngineInterface*    m_engine;
    std::ofstream           m_file;
};

#endif
