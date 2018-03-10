#include "tab.h"

Page *Tab::addPage(const std::string &title)
{
    Page *page = new Page(title);
    page->getFrame().setWindowOffsets(0, 1);
    m_pages.push_back(page);
    return page;
}

void Tab::render()
{
    unsigned int currOffset = 1; // To account for selector

    for (unsigned int ii = 0; ii < m_pages.size(); ii++)
    {
        Page *page = m_pages[ii];

        if (ii == m_selection) {
            drawTile(currOffset - 1, 0, '>', Color(RED));
        }
        drawString(currOffset, 0, page->getTitle().c_str());

        currOffset += page->getTitle().length() + 2; // Space and indicator symbol
    }

    m_pages[m_selection]->getFrame().render();
}

void Tab::keyPress(unsigned char key)
{
    if (key == KEY_TAB)
    {
        setSelection(m_selection + 1);
        //return;
    }

    m_pages[m_selection]->getFrame().keyPress(key);
}