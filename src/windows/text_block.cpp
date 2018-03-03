#include "text_block.h"
#include <iostream>

void TextBlock::wrapText()
{
    size_t wordStart = 0;
    size_t wordEnd = 0;
    unsigned int lineNum = 0;
    m_lines.clear();
    m_lines.push_back("");

    while (wordEnd != std::string::npos)
    {
        wordEnd = m_text.find(' ', wordStart);
        std::string word(m_text.substr(wordStart, wordEnd - wordStart));
        if (m_lines[lineNum].length() + word.length() + 3 /*...*/ + 2 /*spaces*/ > getWidth() && lineNum + 1 >= m_maxRows)
        {
            m_lines[lineNum].append("...");
        }
        if (m_lines[lineNum].length() + word.length() + 1 > getWidth())
        {
            if (lineNum + 1 >= m_maxRows)
            {
                m_lines[lineNum].append("...");
            }
            // Start the next line
            m_lines.push_back("");
            lineNum++;
        }
        m_lines[lineNum].append(word);
        m_lines[lineNum].append(" ");
        wordStart = wordEnd + 1;
    }
}

void TextBlock::render()
{
    for (unsigned int ii = 0; ii < m_lines.size(); ii++)
    {
        drawString(0, ii, m_lines[ii].c_str());
    }
}