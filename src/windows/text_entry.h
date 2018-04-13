#pragma once

#include "widget.h"
#include <functional>

class TextEntry : public Widget
{
  public:
    TextEntry *setText(const std::string &text)
    {
        m_text = text;
        return this;
    }

    std::string getText()
    {
        return m_text;
    }

    TextEntry* setEnterCallback(const std::function<void(TextEntry*)>& cb) {
        m_enterCb = cb;
        return this;
    }
    void keyPress(unsigned char key);
    void render();
  private:
    std::string m_text = std::string("");
    bool m_blink = false;
    std::function<void(TextEntry*)> m_enterCb = [](TextEntry*){};
};