#include "widget.h"
#include <iostream>

Widget *Widget::realignWidget(unsigned int windowWidth, unsigned int windowHeight)
{
    switch (this->getVerticalAlign())
    {
    case VerticalAlign::Top:
    {
        this->m_yPos = this->m_y + m_yOffset;
        break;
    }
    case VerticalAlign::Centre:
    {
        this->m_yPos = m_yOffset + this->m_y + (windowHeight / 2 - this->getHeight() / 2);
        break;
    }
    case VerticalAlign::Bottom:
    {
        this->m_yPos = m_yOffset + windowHeight - this->getHeight() - this->m_y + 1;
        break;
    }
    }
    switch (this->getHorizontalAlign())
    {
    case HorizontalAlign::Left:
    {
        m_xPos = this->m_x + m_xOffset;
        break;
    }
    case HorizontalAlign::Centre:
    {
        this->m_xPos = m_xOffset + this->m_x + (windowWidth / 2 - this->getWidth() / 2);
        break;
    }
    case HorizontalAlign::Right:
    {
        this->m_xPos = m_xOffset + windowWidth - this->getWidth() - this->m_x + 1;
        break;
    }
    }
    // std::cout << "width: " << windowWidth << " height: " << windowHeight << std::endl;
    // std::cout << "offX: " << m_xOffset << " offY: " << m_yOffset << std::endl;
    // std::cout << "XPos: " << m_xPos << " YPos: " << m_yPos << std::endl;
    // std::cout << "X: " << x << " Y: " << y << std::endl;
    // std::cout << "W: " << this->getWidth() << std::endl;

    return this;
}

Widget *Widget::drawString(unsigned int x, unsigned int y,
                           const char *text, Color fg, Color bg)
{
    m_graphics->drawString(m_yPos + y, m_xPos + x, text, fg, bg);

    return this;
}

Widget *Widget::drawCommandString(unsigned int x, unsigned int y,
                                  const char *text, unsigned int pos,
                                  bool active)
{
    char command[2] = {0};
    command[0] = text[pos];

    Color fg = Color(WHITE);
    Color bg = Color(BLACK);
    Color cc = Color(GREEN);
    if (!active)
    {
        float factor = 0.5;
        fg *= factor;
        cc *= factor;
    }

    drawString(x, y, text, fg, bg);
    if (active)
    {
        drawString(x + pos, y, command, cc, bg);
    }

    return this;
}

Widget *Widget::drawTile(unsigned int x, unsigned int y, unsigned char text)
{
    m_graphics->drawTile(m_yPos + y, m_xPos + x, text, m_fgColor, m_bgColor);

    return this;
}

Widget *Widget::drawBorder()
{
    return this->drawBorder(0, 0, getWidth(), getHeight());
}

Widget *Widget::drawBorder(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    std::cout << "Border - x: " << (m_xPos) << " w: " << width << std::endl;
    m_graphics->drawBorder(m_yPos + y, m_xPos + x, height-2, width-2);
    return this;
}
