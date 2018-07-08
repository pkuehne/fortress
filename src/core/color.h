#pragma once

typedef enum {
    RED,
    GREEN,
    BLUE,
    WHITE,
    BLACK,
    GREY,
    YELLOW,
    DARK_GREEN,
    BROWN
} COLOR;

class Color {
public:
    Color() : m_red(0), m_green(0), m_blue(0) {}
    Color(float red, float green, float blue);
    explicit Color(COLOR color);
    float& Red() { return m_red; }
    float Red() const { return m_red; }
    float& Green() { return m_green; }
    float Green() const { return m_green; }
    float& Blue() { return m_blue; }
    float Blue() const { return m_blue; }

    void operator*=(float lhs);
    bool operator==(const Color& lhs) const {
        return this->m_red == lhs.m_red && this->m_blue == lhs.m_blue &&
               this->m_green == lhs.m_green;
    }

private:
    float m_red;
    float m_green;
    float m_blue;
};
