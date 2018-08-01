#include "progress_bar.h"
#include <iostream>

void ProgressBar::render() {
    float percent = (float)m_value / m_max;

    for (unsigned int ii = 0; ii < getWidth() * percent && ii < getWidth();
         ii++) {
        // drawString(ii, 0, "=");
        drawTile(ii, 0, 178);
    }
}