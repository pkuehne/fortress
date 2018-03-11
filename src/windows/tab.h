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
    Page *addPage(const std::string &title);
    std::vector<Page *> &getPages() { return m_pages; }
    Tab *setSelection(unsigned int selection) { 
        m_selection = selection;
        if (m_selection >= m_pages.size()) {
            m_selection = 0;
        }
        return this;
    }
    unsigned int getSelection() {
        return m_selection;
    }
    void render();
    void keyPress(unsigned char key);
    Widget* setWindowOffsets(unsigned int x, unsigned int y);
    Widget *realignWidget(unsigned int width, unsigned int height);

  private:
    std::vector<Page *> m_pages;
    unsigned int m_selection = 0;
};