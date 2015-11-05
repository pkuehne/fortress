#include "color.h"

Color::Color (float red, float green, float blue)
: m_red (red)
, m_green (green)
, m_blue (blue)
{

}

Color::Color (COLOR color)
{
    switch (color) {
        case RED:
            m_red = 1; m_green = 0; m_blue = 0; break;
        case GREEN:
            m_red = 0; m_green = 1; m_blue = 0; break;
        case BLUE:
            m_red = 0; m_green = 0; m_blue = 1; break;
        case WHITE:
            m_red = 1; m_green = 1; m_blue = 1; break;
        case BLACK:
            m_red = 0; m_green = 0; m_blue = 0; break;
        case GREY:
            m_red = 128.0/256.0; m_green = 128.0/256.0; m_blue = 128.0/256.0; break;
        case YELLOW:
            m_red = 0; m_green = 1; m_blue = 1; break;
        case DARK_GREEN:
            m_red = 34.0/256.0; m_green = 139.0/256.0; m_blue = 34.0/256.0; break;
        case BROWN:
            m_red = 102.0/256.0; m_green = 51.0/256.0; m_blue =0.0/256.0; break;
        default:
            break;
    }
}
