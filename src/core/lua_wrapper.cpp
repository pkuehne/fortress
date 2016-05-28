#include "lua_wrapper.h"
#include "game_state.h"
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
}

void LuaWrapper::setGameState (GameState* state)
{
    m_state = state;
}

bool LuaWrapper::loadFile (const std::string& filename)
{
    return false;
}

std::string LuaWrapper::executeCommand (const std::string& command)
{
    int result = luaL_dostring (m_runtime, command.c_str());
    int num_retvals = lua_gettop(m_runtime);
    std::cout << "Retvals: " << num_retvals << std::endl;
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
