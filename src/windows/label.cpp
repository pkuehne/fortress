#include "label.h"

void Label::render()
{
    if (this->commandChar > 0) {
        drawCommandString ( 0, 0,
                            this->m_text.c_str(),
                            this->commandChar-1,
                            this->sensitive);
    } else {
        Color fg = Color(WHITE);
        fg *= (this->sensitive ? 1.0 : 0.5);
        drawString( 0, 0, this->m_text.c_str(), fg);
    }
}
