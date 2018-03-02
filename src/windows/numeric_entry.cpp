#include "../core/utility.h"
#include "numeric_entry.h"

void NumericEntry::render()
{
    if (getSensitive())
    {
        drawCommandString(0, 0, "-", 0, true);
        drawCommandString(m_text.size()+1, 0, "+", 0, true);
    }
    drawString(1, 0, m_text.c_str());
}

void NumericEntry::keyPress(unsigned char key)
{
    if (key == '+' || key == KEY_RIGHT)
    {
        setNumber(m_number + 1);
    }
    if (key == '-' || key == KEY_LEFT)
    {
        setNumber(m_number - 1);
    }
}