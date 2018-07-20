#include "text_entry.h"
#include "../core/utility.h"
#include <cctype>

void TextEntry::keyPress(unsigned char key) {
    unsigned int fullRenderLength = m_text.size() + 1 + m_suffix.size();
    if (isprint(key) && fullRenderLength < getWidth()) {
        m_text.append(1, key);
    } else if (key == KEY_BACKSPACE && !m_text.empty()) {
        m_text.pop_back();
    } else if (key == KEY_ENTER) {
        m_enterCb(this);
    }
}

void TextEntry::render() {
    m_blink = !m_blink;

    if (!m_text.empty()) {
        drawString(0, 0, m_text.c_str());
    }

    if (m_blink && getSensitive()) {
        drawString(m_text.size(), 0, "_", Color(GREEN));
    }
    if (!m_suffix.empty()) {
        unsigned int cursor = getSensitive() ? 1 : 0;
        drawString(m_text.size() + cursor, 0, m_suffix.c_str());
    }
}