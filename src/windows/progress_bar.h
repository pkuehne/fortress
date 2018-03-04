#pragma once

#include "widget.h"

class ProgressBar : public Widget
{
  public:
    ProgressBar *setValue(unsigned int value)
    {
        m_value = value;
        return this;
    }
    ProgressBar *setMaxValue(unsigned int max)
    {
        m_max = max;
        return this;
    }
    unsigned int getValue()
    {
        return m_value;
    }

    void render();

  private:
    unsigned int m_value = 0;
    unsigned int m_max = 1;
};