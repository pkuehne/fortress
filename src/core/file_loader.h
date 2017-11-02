#ifndef FILE_LOADER
#define FILE_LOADER

#include "game_engine.h"
#include "tag.h"
#include <vector>
#include <string>

class FileLoader {
public:
    void initialise (GameEngine* engine) { m_engine = engine; }
    void loadState ();

    Location loadLocation (unsigned int& pos);
    ComponentBase* loadComponent (unsigned int& pos, const std::string& component);
    void loadMap (unsigned int& pos);

private:
    std::vector<Tag>        m_tags;
    GameEngine*    m_engine;
};

#endif
