#include "text_entry.h"
#include "../core/utility.h"
#include <cctype>

void TextEntry::keyPress(unsigned char key) {
    if (isprint(key)) {
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
}