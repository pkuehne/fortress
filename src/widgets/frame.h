#pragma once

#include "widget.h"

class Frame : public Widget {
public:
    Frame* setBorder(bool border = true) {
        m_border = border;
        return this;
    }
    Frame* setMargin(unsigned int margin = 1) {
        m_margin = margin;
        return this;
    }
    Frame* setTitle(const std::string& title) {
        m_title = title;
        return this;
    }
    Frame* setMergeBorders(bool merge = true) {
        m_mergeBorders = merge;
        return this;
    }
    void realign(unsigned int xOrigin, unsigned int yOrigin,
                 unsigned int parentWidth, unsigned int parentHeight) override;
    void render() override;
    void keyPress(unsigned char key) override;

private:
    bool m_border = false;
    bool m_mergeBorders = false;
    unsigned int m_margin = 0;
    std::string m_title;
};