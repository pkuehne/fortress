#ifndef __DEBUG_WINDOW_H__
#define __DEBUG_WINDOW_H__

#include "window.h"
#include "../core/utility.h"
#include "../core/lua_wrapper.h"

struct Output {
    Output (const std::string& t, const Color& c)
        : text(t), color (c) {}
    Output () {}
    std::string text;
    Color color;
};

const Color COMMAND_COLOR = Color (WHITE);
const Color ERROR_COLOR = Color (RED);
const Color OUTPUT_COLOR = Color (GREY);

const unsigned int COMMAND_MAX_LEN = 128;
class DebugWindow : public Window {
public:
    void setup();
    void registerWidgets();
    void nextTurn();

private:
    void setupLua();
    void loadLuaScripts();

private:
    std::vector<Output> history;
    LuaWrapper  m_lua;
};

#endif
