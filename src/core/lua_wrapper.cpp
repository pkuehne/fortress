#include "lua_wrapper.h"
#include "../core/location.h"
#include <iostream>
#include <spdlog/spdlog.h>
#include <sstream>

LuaWrapper::LuaWrapper() : m_runtime(luaL_newstate()) {
    if (m_runtime == nullptr) {
        spdlog::error("Failed to open Lua runtime environment");
        throw std::runtime_error("Failed to initialize LUA environment");
    }

    luaL_openlibs(m_runtime);

    registerBindings();
}

LuaWrapper::~LuaWrapper() { lua_close(m_runtime); }

void LuaWrapper::loadFile(const std::string& filename) {
    int result = luaL_dofile(m_runtime, filename.c_str());
    if (result != 0) {
        spdlog::error("Failed to parse Lua file: {}", filename);
        throw std::runtime_error(
            std::string("Parse error: ").append(lua_tostring(m_runtime, -1)));
    }
}

std::string LuaWrapper::executeCommand(const std::string& command) {
    int result = luaL_dostring(m_runtime, command.c_str());
    int num_retvals = lua_gettop(m_runtime);
    if (result == 0 && num_retvals > 0) {
        std::stringstream output;
        for (int ii = 1; ii <= num_retvals; ii++) {
            if (lua_isnumber(m_runtime, ii)) {
                output << lua_tonumber(m_runtime, ii);
            } else if (lua_isboolean(m_runtime, ii)) {
                output << lua_toboolean(m_runtime, ii);
            } else if (lua_isstring(m_runtime, ii)) {
                output << lua_tostring(m_runtime, ii);
            } else if (lua_isnil(m_runtime, ii)) {
                output << "(Nil)";
            } else {
                output << "(unknown)";
            }
            output << "    ";
        }
        lua_pop(m_runtime, num_retvals);
        return output.str();
    } else if (result != 0) {
        throw std::runtime_error(
            std::string("Parse error: ").append(lua_tostring(m_runtime, -1)));
    }
    return "Command success";
}

int createOrc(lua_State* runtime) {
    // unsigned int x = 0;
    // unsigned int y = 0;
    // if (lua_gettop(runtime) != 2) {
    //     lua_pushstring(runtime, "Incorrect number of arguments");
    //     lua_error(runtime);
    // }
    // if (!lua_isnumber(runtime, 1)) {
    //     lua_pushstring(runtime, "First argument must be a number!");
    //     lua_error(runtime);
    // }
    // x = lua_tonumber(runtime, 1);

    // if (!lua_isnumber(runtime, 2)) {
    //     lua_pushstring(runtime, "Second argument must be a number!");
    //     lua_error(runtime);
    // }
    // y = lua_tonumber(runtime, 2);

    // GameState* state = getState(runtime);

    // Location location; // = state->location(state->player());
    // location.x += x;
    // location.y += y;
    // state->prefabs().create("orc", location);

    return 0;
}

int playerLocation(lua_State* runtime) {
    // GameState* state = getState(runtime);
    Location location; // = state->location(state->player());

    std::stringstream output;
    output << location;

    lua_pushstring(runtime, output.str().c_str());
    return 1;
}

int revealMap(lua_State* runtime) {
    // GameState* state = getState(runtime);
    // state->debug().revealAllTiles = true;

    return 0;
}

int togglePaths(lua_State* runtime) {
    // GameState* state = getState(runtime);

    // state->debug().showNpcPaths = !state->debug().showNpcPaths;
    return 0;
}

void LuaWrapper::registerBindings() {
    lua_pushcfunction(m_runtime, createOrc);
    lua_setglobal(m_runtime, "createOrc");

    lua_pushcfunction(m_runtime, playerLocation);
    lua_setglobal(m_runtime, "playerLocation");

    lua_pushcfunction(m_runtime, revealMap);
    lua_setglobal(m_runtime, "revealMap");

    lua_pushcfunction(m_runtime, togglePaths);
    lua_setglobal(m_runtime, "togglePaths");
}
