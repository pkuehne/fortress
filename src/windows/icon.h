#pragma once

#include "widget.h"

class Icon : public Widget
{
  public:
    virtual void render();
    virtual Icon *setIcon(unsigned char i)
    {
        m_icon = i;
        return this;
    }

  private:
    unsigned char m_icon;
};