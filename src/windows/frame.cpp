#include "frame.h"

Widget *Frame::setWindowOffsets(unsigned int x, unsigned int y)
{
    Widget::setWindowOffsets(x, y);

    for (auto iter : getChildren())
    {
        Widget *w = iter.second;
        w->setWindowOffsets(x, y);
    }
    return this;
}

Widget *Frame::realignWidget(unsigned int width, unsigned int height)
{
    Widget::realignWidget(width, height);

    for (auto iter : getChildren())
    {
        Widget *w = iter.second;
        w->realignWidget(width - 2, height - 2);
    }
    return this;
}

void Frame::render()
{
    Widget::render();

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