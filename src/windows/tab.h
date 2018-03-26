#pragma once
#include "widget.h"
#include "frame.h"
#include "../core/utility.h"
#include <vector>

class Page
{
  public:
    explicit Page(const std::string &title)
        : m_title(title)
    {
    }

    Page *setTitle(const std::string &title)
    {
        m_title = title;
        return this;
    }
    const std::string &getTitle()
    {
        return m_title;
    }
    Frame *getFrame()
    {
        return &m_frame;
    }

  private:
    std::string m_title;
    Frame m_frame;
};

class Tab : public Widget
{
  public:
    typedef void (*PageSwitchCB)(Tab *);

    Page *addPage(const std::string &title);
    std::vector<Page *> &getPages() { return m_pages; }
    Tab *setCurrentPage(unsigned int page);    
    unsigned int getCurrentPage()
    {
        return m_currentPage;
    }
    Tab *setPageSwitchCallback(PageSwitchCB cb)
    {
        m_pageSwitchCallback = cb;
        return this;
    }
    void render();
    void keyPress(unsigned char key);
    Widget *setWindowOffsets(unsigned int x, unsigned int y);
    Widget *realignWidget(unsigned int width, unsigned int height);

  private:
    std::vector<Page *> m_pages;
    unsigned int m_currentPage = 0;
    PageSwitchCB m_pageSwitchCallback = 0;
};