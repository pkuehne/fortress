#ifndef __COLOR_H__
#define __COLOR_H__


typedef enum {
    RED,
    GREEN,
    BLUE,
    WHITE,
    BLACK,
    GREY,
    YELLOW
} COLOR;

class Color {
public:
    Color() : m_red (0), m_green (0), m_blue (0) { }
    Color (float red, float green, float blue);
    Color (COLOR color);
    float& Red () { return m_red; }
    float& Green() { return m_green; }
    float& Blue () { return m_blue; }

private:
    float m_red;
    float m_green;
    float m_blue;

};

#endif
