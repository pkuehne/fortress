#include "lua_wrapper.h"
#include "game_state.h"
#include "prefab_builder.h"
#include <glog/logging.h>
#include <iostream>
#include <sstream>

LuaWrapper::LuaWrapper ()
: m_state (0)
, m_runtime (luaL_newstate())
{
    if (m_runtime == nullptr) {
        LOG(ERROR) << "Failed to open Lua runtime environment" << std::endl;
        throw std::runtime_error ("Failed to initialize LUA environment");
    }

    luaL_openlibs (m_runtime);

    registerBindings();
}

LuaWrapper::~LuaWrapper()
{
    lua_close(m_runtime);
}

void LuaWrapper::setGameState (GameState* state)
{
    m_state = state;
    lua_pushlightuserdata (m_runtime, state);
    lua_setglobal (m_runtime, "game_state");
}

void LuaWrapper::loadFile (const std::string& filename)
{
    int result = luaL_dofile (m_runtime, filename.c_str());
    if (result != 0) {
        LOG(ERROR) << "Failed to parse Lua file: " << filename << std::endl;
        throw std::runtime_error (std::string ("Parse error: ")
                                    .append (lua_tostring(m_runtime, -1)));
    }
}

std::string LuaWrapper::executeCommand (const std::string& command)
{
    int result = luaL_dostring (m_runtime, command.c_str());
    int num_retvals = lua_gettop(m_runtime);
    if (result == 0 && num_retvals > 0) {
        std::stringstream output;
        for (int ii = 1; ii <= num_retvals; ii++) {
            if (lua_isnumber (m_runtime, ii)) {
                output << lua_tonumber (m_runtime, ii);
            } else if (lua_isboolean (m_runtime, ii)) {
                output << lua_toboolean (m_runtime, ii);
            } else if (lua_isstring (m_runtime, ii)) {
                output << lua_tostring (m_runtime, ii);
            } else if (lua_isnil (m_runtime, ii)) {
                output <<  "(Nil)";
            } else {
                output <<  "(unknown)";
            }
            output << "\t";
        }
        lua_pop (m_runtime, num_retvals);
        return output.str();
    } else if (result != 0) {
        throw std::runtime_error (std::string ("Parse error: ")
                                    .append (lua_tostring(m_runtime, -1)));
    }
    return "Command success";
}

GameState* getState (lua_State* runtime)
{
    lua_getglobal (runtime, "game_state");
    if (lua_isnil (runtime, -1)) {
        lua_pushstring (runtime, "GameState not defined!");
        lua_error (runtime);
    }
    GameState* state = (GameState*) lua_touserdata (runtime, -1);
    return state;
}

int createOrc (lua_State* runtime)
{
    unsigned int x = 0;
    unsigned int y = 0;
    if (lua_gettop (runtime) != 2) {
        lua_pushstring (runtime, "Incorrect number of arguments");
        lua_error (runtime);
    }
    if (!lua_isnumber (runtime, 1)) {
        lua_pushstring (runtime, "First argument must be a number!");
        lua_error (runtime);
    }
    x = lua_tonumber (runtime, 1);

    if (!lua_isnumber (runtime, 2)) {
        lua_pushstring (runtime, "Second argument must be a number!");
        lua_error (runtime);
    }
    y = lua_tonumber (runtime, 2);

    GameState* state = getState (runtime);

    Location location = state->location(state->player());
    location.x += x;
    location.y += y;
    PrefabBuilder prefabs (state);
    prefabs.createEnemyPrefab (location);

    return 0;
}

int playerLocation (lua_State* runtime)
{
    GameState* state = getState (runtime);
    Location location = state->location(state->player());

    std::stringstream output;
    output << location;

    lua_pushstring (runtime, output.str().c_str());
    return 1;
}

int revealMap (lua_State* runtime)
{
    GameState* state = getState (runtime);

    for (unsigned x = 0; x < state->map()->getMapWidth(); x++) {
        for (unsigned y = 0; y < state->map()->getMapHeight(); y++) {
            for (unsigned z = 0; z < state->map()->getMapDepth(); z++) {
                Location location(x, y, z);
                Tile& tile = state->tile (location);
                if (tile.lastVisited < state->turn()) {
                    tile.lastVisited = state->turn();
                }
            }
        }
    }
    return 0;
}

void LuaWrapper::registerBindings()
{
    lua_pushcfunction (m_runtime, createOrc);
    lua_setglobal (m_runtime, "createOrc");

    lua_pushcfunction (m_runtime, playerLocation);
    lua_setglobal (m_runtime, "playerLocation");


    lua_pushcfunction (m_runtime, revealMap);
    lua_setglobal (m_runtime, "revealMap");
}

