#include "numeric_entry.h"

void NumericEntry::render()
{

    drawString(0,0, m_text.c_str());
}

void NumericEntry::keyPress(unsigned char key)
{
    if (key == '+')
    {
        setNumber(m_number+1);
    }
    if (key == '-')
    {
        setNumber(m_number-1);
    }
}