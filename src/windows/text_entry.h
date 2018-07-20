#pragma once

#include "widget.h"
#include <functional>

class TextEntry : public Widget {
public:
    typedef std::function<void(TextEntry*)> EnterCB;

    TextEntry* setText(const std::string& text) {
        m_text = text;
        return this;
    }
    std::string getText() { return m_text; }

    TextEntry* setSuffix(const std::string& suffix) {
        m_suffix = suffix;
        return this;
    }
    std::string getSuffix() { return m_suffix; }

    TextEntry* setEnterCallback(const EnterCB& cb) {
        m_enterCb = cb;
        return this;
    }
    void keyPress(unsigned char key);
    void render();

private:
    std::string m_text = std::string("");
    std::string m_suffix;
    bool m_blink = false;
    EnterCB m_enterCb = [](TextEntry*) {};
};