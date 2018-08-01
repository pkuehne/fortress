#include "tab.h"

Page* Tab::addPage(const std::string& title) {
    Page* page = new Page(title);
    m_pages.push_back(page);
    return page;
}

Tab* Tab::setCurrentPage(unsigned int page) {
    unsigned int prevPage = m_currentPage;
    m_currentPage = page;
    if (m_currentPage >= m_pages.size()) {
        m_currentPage = 0;
    }
    if (m_currentPage != prevPage && m_pageSwitchCallback &&
        m_pages.size() > 1) {
        m_pageSwitchCallback(this);
    }

    return this;
}

void Tab::render() {
    unsigned int currOffset = 1; // To account for selector

    for (unsigned int ii = 0; ii < m_pages.size(); ii++) {
        Page* page = m_pages[ii];

        if (ii == m_currentPage) {
            drawString(currOffset - 1, 0, ">", Color(RED));
        }
        drawString(currOffset, 0, page->getTitle().c_str());

        currOffset +=
            page->getTitle().length() + 2; // Space and indicator symbol
    }

    m_pages[m_currentPage]->getFrame()->render();
}

void Tab::keyPress(unsigned char key) {
    if (key == KEY_TAB) {
        setCurrentPage(m_currentPage + 1);
        // return;
    }

    m_pages[m_currentPage]->getFrame()->keyPress(key);
}

void Tab::realign(unsigned int xOrigin, unsigned int yOrigin,
                  unsigned int parentWidth, unsigned int parentHeight) {
    Widget::realign(xOrigin, yOrigin, parentWidth, parentHeight);

    unsigned int offsetForPageLabels = 2;

    for (Page* page : m_pages) {
        page->getFrame()->setHeight(getHeight() - offsetForPageLabels);
        page->getFrame()->setWidth(getWidth());

        page->getFrame()->realign(getXPos(), getYPos() + offsetForPageLabels,
                                  getWidth(), getHeight());
    }
}