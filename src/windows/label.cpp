#include "label.h"
#include <iostream>

void Label::render()
{
    if (this->m_commandChar > 0)
    {
        drawCommandString(0, 0,
                          this->m_text.c_str(),
                          this->m_commandChar - 1,
                          this->getSensitive());
    }
    else
    {
        Color fg = this->getForegroundColor();
        fg *= (this->getSensitive() ? 1.0 : 0.5);
        drawString(0, 0, this->m_text.c_str(), fg);
    }
}

void Label::keyPress(unsigned char key)
{
    if (this->getSensitive() && m_commandChar && key == m_text[m_commandChar - 1] && m_onCommandChar)
    {
        m_onCommandChar(this);
    }
    Widget::keyPress(key);
}
