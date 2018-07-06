#pragma once

#include "widget.h"

class NumericEntry : public Widget {
public:
    NumericEntry() {}
    ~NumericEntry() {}
    void render();
    NumericEntry* setNumber(int number) {
        m_number = number;
        m_text = std::to_string(number);
        setWidth(m_text.size() + 2); ///< To account for angle brackets
        return this;
    }
    int getNumber() { return m_number; }

    void keyPress(unsigned char key);

private:
    int m_number = 0;
    std::string m_text;
};