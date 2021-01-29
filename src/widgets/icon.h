#pragma once

#include "widget.h"

class Icon : public Widget {
public:
    Icon() {}
    ~Icon() {}
    void render() override;
    virtual Icon* setIcon(unsigned char i) {
        m_icon = i;
        return this;
    }

private:
    unsigned char m_icon = 0;
};