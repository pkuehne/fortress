#pragma once

#include "../core/lua_wrapper.h"
#include "../core/utility.h"
#include "window.h"

struct Output {
    Output(const std::string& t, const Color& c) : text(t), color(c) {}
    Output() {}
    std::string text;
    Color color;
};

const Color COMMAND_COLOR = Color(WHITE);
const Color ERROR_COLOR = Color(RED);
const Color OUTPUT_COLOR = Color(GREY);

class DebugWindow : public Window {
public:
    void setup();
    void registerWidgets();
    void nextTurn();

private:
    void setupLua();
    void loadLuaScripts();

private:
    std::vector<Output> m_history;
    LuaWrapper m_lua;
};

