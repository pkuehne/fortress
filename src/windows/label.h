#pragma once

#include "widget.h"

class Label : public Widget {
    public:
        Label() {}

        Label* setText(const std::string& text) {
            m_text = text;
            return this;
        }
        Label* settext(const char* text) {
            m_text = std::string(text);
            return this;
        }
        std::string getText() const {
            return m_text;
        }
        Label* setCommandChar(unsigned char pos) 
        {
            m_commandChar = pos;
            return this;
        }
        unsigned char getCommandChar()
        {
            return m_commandChar;
        }

        virtual void keyPress(unsigned char key);
        virtual void render();

        void(*onCommandChar)(Label*) = nullptr;

    private:
        std::string m_text = "";
        unsigned char m_commandChar;
};
