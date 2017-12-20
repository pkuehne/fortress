#include "label.h"
#include <iostream>

void Label::render()
{
    if (this->commandChar > 0) {
        drawCommandString ( 0, 0,
                            this->m_text.c_str(),
                            this->commandChar-1,
                            this->sensitive);
    } else {
        Color fg = this->fg;
        fg *= (this->sensitive ? 1.0 : 0.5);
        drawString( 0, 0, this->m_text.c_str(), fg);
    }
}

void Label::keyPress(unsigned char key)
{
    if (commandChar && key == m_text[commandChar-1] && onCommandChar) {
        onCommandChar(this);
    }
}
