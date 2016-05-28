#ifndef __LUA_WRAPPER_H__
#define __LUA_WRAPPER_H__

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>
#include "game_state.h"

class LuaWrapper {
public:
    LuaWrapper ();
    ~LuaWrapper();
    void setGameState (GameState*);
    void loadFile (const std::string& filename);
    std::string executeCommand (const std::string& command);

private:
    void registerBindings();
private:
    GameState* m_state;
    lua_State* m_runtime;
};

#endif
