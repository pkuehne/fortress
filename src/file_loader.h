#ifndef FILE_LOADER
#define FILE_LOADER

#include "game_engine_interface.h"
#include <vector>
#include <string>

class FileLoader {
public:
    void initialise (GameEngineInterface* engine) { m_engine = engine; }
    void loadState ();

    Location loadLocation (unsigned int pos);
private:
    std::vector<std::string>    m_lines;
    GameEngineInterface*        m_engine;
};

#endif
