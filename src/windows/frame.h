#pragma once

#include "widget.h"

class Frame : public Widget
{
  public:
    Frame *setBorder(bool border = true)
    {
        m_border = border;
        return this;
    }
    Frame *setMargin(unsigned int margin = 1)
    {
        m_margin = margin;
        return this;
    }
    Frame *setTitle(const std::string &title)
    {
        m_title = title;
        return this;
    }
    Widget *setWindowOffsets(unsigned int x, unsigned int y);
    Widget *realignWidget(unsigned int width, unsigned int height);
    void render();
    void keyPress(unsigned char key);

  private:
    bool m_border = false;
    unsigned int m_margin = 0;
    std::string m_title;
};