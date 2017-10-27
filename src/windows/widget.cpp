#include "widget.h"
#include <iostream>

void Widget::realignWidget(unsigned int windowWidth, unsigned int windowHeight)
{
    switch (this->vAlign) {
        case VerticalAlign::Top:
            { this->m_yPos = this->y + m_yOffset; break; }
        case VerticalAlign::Centre:
            { this->m_yPos = (windowHeight/2 - this->height/2); break; }
        case VerticalAlign::Bottom:
            { this->m_yPos = windowHeight - this->y - this->height + m_yOffset; break; }
    }
    switch (this->hAlign) {
        case HorizontalAlign::Left:
            { m_xPos = this->x + m_xOffset; break; }
        case HorizontalAlign::Centre:
            { this->m_xPos = (windowWidth/2 - this->width/2); break; }
        case HorizontalAlign::Right:
            { this->m_xPos = windowWidth - this->x - this->width + m_yOffset; break; }
    }
    std::cout << "width: " << windowWidth << " height: " << windowHeight << std::endl;
    std::cout << "offX: " << m_xOffset << " offY: " << m_yOffset << std::endl;
    std::cout << "XPos: " << m_xPos << " YPos: " << m_yPos << std::endl;
    std::cout << "X: " << x << " Y: " << y << std::endl;
}

void Widget::drawString (unsigned int x, unsigned int y,
        const char* text, Color fg, Color bg)
{
    m_graphics->drawString (m_yPos+y, m_xPos+x, text, fg, bg);
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
