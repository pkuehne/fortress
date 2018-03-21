#include "frame.h"
#include <iostream>

Widget *Frame::setWindowOffsets(unsigned int x, unsigned int y)
{
    Widget::setWindowOffsets(x, y);
    unsigned int internalOffset = m_margin;
    if (m_border)
    {
        internalOffset++;
    }
    for (auto iter : getChildren())
    {
        Widget *w = iter.second;
        if (m_mergeBorders && dynamic_cast<Frame *>(w))
        {
            w->setWindowOffsets(x, y);
        }
        else
        {
            w->setWindowOffsets(x + internalOffset, y + internalOffset);
        }
    }
    return this;
}

Widget *Frame::realignWidget(unsigned int width, unsigned int height)
{
    Widget::realignWidget(width, height);

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
            w->setWindowOffsets(getXPos(), getYPos());
            w->realignWidget(width, height);
        }
        else
        {
            w->setWindowOffsets(getXPos() + internalOffset, getYPos() + internalOffset);
            w->realignWidget(width - internalOffset * 2, height - internalOffset * 2);
        }
    }
    return this;
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