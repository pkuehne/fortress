#pragma once
#include "../core/utility.h"
#include "frame.h"
#include "widget.h"
#include <functional>
#include <vector>

class Page {
public:
    explicit Page(const std::string& title) : m_title(title) {}

    Page* setTitle(const std::string& title) {
        m_title = title;
        return this;
    }
    const std::string& getTitle() { return m_title; }
    Frame* getFrame() { return &m_frame; }

private:
    std::string m_title;
    Frame m_frame;
};

class Tab : public Widget {
public:
    typedef std::function<void(Tab*)> PageSwitchCB;

    Page* addPage(const std::string& title);
    std::vector<Page*>& getPages() { return m_pages; }
    Tab* setCurrentPage(unsigned int page);
    unsigned int getCurrentPage() { return m_currentPage; }
    Tab* setPageSwitchCallback(PageSwitchCB cb) {
        m_pageSwitchCallback = cb;
        return this;
    }
    void render();
    void keyPress(unsigned char key);
    void realign(unsigned int xOrigin, unsigned int yOrigin,
                 unsigned int parentWidth, unsigned int parentHeight);

private:
    std::vector<Page*> m_pages;
    unsigned int m_currentPage = 0;
    PageSwitchCB m_pageSwitchCallback = 0;
};