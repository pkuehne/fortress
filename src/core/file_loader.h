#pragma once

#include "game_engine.h"
#include <string>
#include <vector>

class FileLoader {
public:
    FileLoader() {}
    ~FileLoader() {}
    void initialise(GameEngine* engine) { m_engine = engine; }

private:
    GameEngine* m_engine = nullptr;
};
