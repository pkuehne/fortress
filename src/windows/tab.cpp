#include "tab.h"

Page *Tab::addPage(const std::string &title)
{
    Page *page = new Page(title);
    m_pages.push_back(page);
    return page;
}

void Tab::render()
{
    unsigned int currOffset = 1; // To account for selector

    for (unsigned int ii = 0; ii < m_pages.size(); ii++)
    {
        Page *page = m_pages[ii];

        if (ii == m_selection)
        {
            drawString(currOffset - 1, 0, ">", Color(RED));
        }
        drawString(currOffset, 0, page->getTitle().c_str());

        currOffset += page->getTitle().length() + 2; // Space and indicator symbol
    }

    m_pages[m_selection]->getFrame()->render();
}

void Tab::keyPress(unsigned char key)
{
    if (key == KEY_TAB)
    {
        setSelection(m_selection + 1);
        //return;
    }

    m_pages[m_selection]->getFrame()->keyPress(key);
}

Widget *Tab::setWindowOffsets(unsigned int x, unsigned int y)
{
    Widget::setWindowOffsets(x, y);

    for (Page *page : m_pages)
    {
        // For some reason this is not passed to the widgets in the frame properly
        page->getFrame()->setWindowOffsets(x, y+2);
    }
    return this;
}

Widget *Tab::realignWidget(unsigned int width, unsigned int height)
{
    Widget::realignWidget(width, height);

    for (Page *page : m_pages)
    {
        page->getFrame()->realignWidget(width, height);
    }
    return this;
}