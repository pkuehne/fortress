#include "frame.h"
#include <iostream>

void Frame::realign(unsigned int xOrigin, unsigned int yOrigin, unsigned int parentWidth, unsigned int parentHeight)
{
    Widget::realign(xOrigin, yOrigin, parentWidth, parentHeight);

    unsigned int internalOffset = m_margin;
    if (m_border)
    {
        internalOffset += 1;
    }

    for (auto iter : getChildren())
    {
        Widget *w = iter.second;
        if (m_mergeBorders && dynamic_cast<Frame *>(w))
        {
            w->realign(getXPos(), getYPos(), getWidth(), getHeight());
        }
        else
        {
            w->realign(getXPos() + internalOffset,
                       getYPos() + internalOffset,
                       getWidth() - internalOffset * 2,
                       getHeight() - internalOffset * 2);
        }
    }
}

void Frame::render()
{
    Widget::render();

    if (m_border)
    {
        drawBorder();
        if (m_title.length())
        {
            int x = getWidth() / 2 - m_title.length() / 2;

            clearArea(x - 1, 0, m_title.length() + 2, 1);
            drawString(x, 0, m_title.c_str());
        }
    }
    for (auto iter : getChildren())
    {
        Widget *w = iter.second;
        if (!w->getVisible())
        {
            continue;
        }
        w->render();
    }
}

void Frame::keyPress(unsigned char key)
{
    Widget::keyPress(key);
    for (auto iter : getChildren())
    {
        Widget *w = iter.second;
        if (!w->getSensitive())
        {
            continue;
        }
        w->keyPress(key);
    }
}