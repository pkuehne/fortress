#pragma once

#include "widget.h"
#include <functional>

class Label : public Widget {
public:
    typedef std::function<void(Label*)> CommandCharCB;
    Label() {}

    Label* setText(const std::string& text) {
        m_text = text;
        setWidth(text.size());
        return this;
    }
    Label* setText(const char* text) { return setText(std::string(text)); }
    std::string getText() const { return m_text; }
    Label* setCommandChar(unsigned char pos) {
        m_commandChar = pos;
        return this;
    }
    unsigned char getCommandChar() { return m_commandChar; }
    Label* setCommandCharCallback(CommandCharCB cb) {
        m_onCommandChar = cb;
        return this;
    }
    Label* setIgnoreCommandCharCase(bool ignore) {
        m_ignoreCase = ignore;
        return this;
    }
    bool getIgnoreCommandCharCase() { return m_ignoreCase; }

    void keyPress(unsigned char key) override;
    void render() override;

private:
    std::string m_text = "";
    unsigned char m_commandChar = 0;
    CommandCharCB m_onCommandChar = nullptr;
    bool m_ignoreCase = false;
};
