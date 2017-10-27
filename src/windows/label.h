#pragma once

#include "widget.h"

class Label : public Widget {
    public:
        Label() {}

        
        std::string text() { return m_text; }
        void text(std::string text) { m_text = text; width = m_text.size(); }
        bool sensitive = true;
        unsigned int commandChar = 0;

        virtual void render();

    private:
        std::string m_text = "";

};
