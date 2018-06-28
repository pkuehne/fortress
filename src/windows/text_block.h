#pragma once
#include "widget.h"
#include <vector>

class TextBlock : public Widget {
public:
    Widget* setWidth(unsigned int width) {
        Widget::setWidth(width);
        wrapText();
        setHeight(m_lines.size());
        return this;
    }
    TextBlock* setText(const std::string& text) {
        m_text = text;
        wrapText();
        setHeight(m_lines.size());
        return this;
    }
    void wrapText();
    std::vector<std::string>& getLines() { return m_lines; }

    void render();

private:
    std::string m_text = "";
    std::vector<std::string> m_lines;
    unsigned int m_maxRows = 99;
};