#pragma once

#include "widget.h"

class NumericEntry : public Widget
{
  public:
    void render();
    NumericEntry *setNumber(int number)
    {
        m_number = number;
        m_text = std::to_string(number);
        return this;
    }
    int getNumber()
    {
        return m_number;
    }

    void keyPress(unsigned char key);

  private:
    int m_number;
    std::string m_text;
};