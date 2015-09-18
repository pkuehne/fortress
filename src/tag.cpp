#include "tag.h"

Tag::Tag (std::string& text)
{
    size_t tagStart = text.find("[");
    size_t valStart = text.find(":");
    size_t tagEnd   = text.find("]");
    if (tagStart == std::string::npos ||
        valStart == std::string::npos ||
        tagEnd   == std::string::npos) {
            return; // Not a valid [tag:value] pair
    }
    m_name.assign (text.substr(tagStart+1, valStart-tagStart-1));
    m_string.assign (text.substr(valStart+1, tagEnd-valStart-1));

    try {
        m_number = std::stol (m_string);
    } catch (std::exception& e) {
        m_number = 0;
    }
    try {
        m_decimal = std::stod (m_string);
    } catch (std::exception& e) {
        m_decimal = 0.0;
    }

}
