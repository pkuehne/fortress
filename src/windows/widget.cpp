#include "widget.h"
#include <iostream>

void Widget::realign(unsigned int xOrigin, unsigned int yOrigin, unsigned int parentWidth, unsigned int parentHeight)
{
    switch (this->getVerticalAlign())
    {
    case VerticalAlign::Top:
    {
        this->m_yPos = yOrigin + this->m_relativeYPos;
        break;
    }
    case VerticalAlign::Centre:
    {
        this->m_yPos = yOrigin + this->m_relativeYPos + (parentHeight / 2 - this->getHeight() / 2);
        break;
    }
    case VerticalAlign::Bottom:
    {
        this->m_yPos = yOrigin + parentHeight - this->getHeight() - this->m_relativeYPos;
        break;
    }
    }
    switch (this->getHorizontalAlign())
    {
    case HorizontalAlign::Left:
    {
        this->m_xPos = xOrigin + this->m_relativeXPos;
        break;
    }
    case HorizontalAlign::Centre:
    {
        this->m_xPos = xOrigin + this->m_relativeXPos + (parentWidth / 2 - this->getWidth() / 2);
        break;
    }
    case HorizontalAlign::Right:
    {
        this->m_xPos = xOrigin + parentWidth - this->getWidth() - this->m_relativeXPos;
        break;
    }
    }
    // std::cout << "width: " << parentWidth << " height: " << parentHeight << std::endl;
    // std::cout << "offX: " << xOrigin << " offY: " << yOrigin << std::endl;
    // std::cout << "XPos: " << m_xPos << " YPos: " << m_yPos << std::endl;
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

Widget *Widget::drawTile(unsigned int x,
                         unsigned int y,
                         unsigned char text,
                         Color fg,
                         Color bg)
{
    m_graphics->drawTile(m_yPos + y, m_xPos + x, text, fg, bg);

    return this;
}

Widget *Widget::drawBorder()
{
    return this->drawBorder(0, 0, getWidth(), getHeight());
}

Widget *Widget::drawBorder(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    m_graphics->drawBorder(m_yPos + y, m_xPos + x, height - 2, width - 2);
    return this;
}

Widget *Widget::clearArea(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    m_graphics->clearArea(m_yPos + y, m_xPos + x, height, width);
    return this;
}
