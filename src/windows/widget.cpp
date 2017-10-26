#include "widget.h"

void Widget::drawString (unsigned int x, unsigned int y,
                        const char* text, Color fg, Color bg)
{
    m_graphics->drawString (m_yOffset+y, m_xOffset+x, text, fg, bg);
}

void Widget::drawCommandString( unsigned int x, unsigned int y,
                                const char* text, unsigned int pos,
                                bool active)
{
    char command[2] = {0};
    command[0] = text[pos];

    Color fg = Color(WHITE);
    Color bg = Color(BLACK);
    Color cc = Color(GREEN);
    if (!active) {
        float factor = 0.5;
        fg *= factor;
        cc *= factor;
    }

    drawString (y, x, text, fg, bg);
    drawString (y, x+pos, command, cc, bg);
}
