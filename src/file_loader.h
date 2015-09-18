#ifndef FILE_LOADER
#define FILE_LOADER

#include "game_engine_interface.h"
#include "tag.h"
#include <vector>
#include <string>

class FileLoader {
public:
    void initialise (GameEngineInterface* engine) { m_engine = engine; }
    void loadState ();

    Location loadLocation (unsigned int& pos);
    ComponentBase* loadComponent (unsigned int& pos, const std::string& component);

private:
    std::vector<Tag>        m_tags;
    GameEngineInterface*    m_engine;
};

#endif
