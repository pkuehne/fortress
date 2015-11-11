#ifndef TAG_H
#define TAG_H

#include <string>

class Tag {
public:
    Tag() { }
    Tag (std::string& text);
    std::string getName() { return m_name; }
    std::string getStr() { return m_string; }
    long getNum() { return m_number; }
    double getDec() { return m_decimal; }

private:
    std::string m_name;
    std::string m_string;
    long        m_number 	= 0;
    double      m_decimal	= 0.0;
};

#endif
