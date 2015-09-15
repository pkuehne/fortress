#ifndef FILE_SAVER
#define FILE_SAVER

#include "game_engine_interface.h"

class FileSaver {
public:
    void initialise (GameEngineInterface* engine) { m_engine = engine; }
    void saveState ();
    
private:
    GameEngineInterface*    m_engine;
};

#endif
