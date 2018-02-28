#pragma once

#include "widget.h"

class Label : public Widget
{
  public:
    typedef void (*CommandCharCB)(Label *);

    Label() {}

    Label *setText(const std::string &text)
    {
        m_text = text;
        return this;
    }
    Label *settext(const char *text)
    {
        m_text = std::string(text);
        return this;
    }
    std::string getText() const
    {
        return m_text;
    }
    Label *setCommandChar(unsigned char pos)
    {
        m_commandChar = pos;
        return this;
    }
    unsigned char getCommandChar()
    {
        return m_commandChar;
    }
    Label *setCommandCharCallback(CommandCharCB cb)
    {
        m_onCommandChar = cb;
        return this;
    }
    Label *setIgnoreCommandCharCase(bool ignore) 
    {
        m_ignoreCase = ignore;
        return this;
    }
    bool getIgnoreCommandCharCase()
    {
        return m_ignoreCase;
    }

    virtual void keyPress(unsigned char key);
    virtual void render();

  private:
    std::string m_text = "";
    unsigned char m_commandChar = 0;
    CommandCharCB m_onCommandChar = nullptr;
    bool m_ignoreCase = false;
};
