#pragma once

#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.hpp>
#include <lua5.3/lualib.h>
#include <string>

class LuaWrapper {
public:
    LuaWrapper();
    ~LuaWrapper();
    void loadFile(const std::string& filename);
    std::string executeCommand(const std::string& command);

private:
    void registerBindings();

private:
    lua_State* m_runtime;
};
