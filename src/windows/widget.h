#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "../core/graphics.h"

class Widget {
    public:
        Widget() {}
        virtual ~Widget() {}

        void setWindowOffsets(unsigned int x, unsigned int y) {
            m_xOffset = x; m_yOffset = y;
        }
        void setGraphics(GraphicsInterface* graphics) { m_graphics = graphics; }

        virtual void render() {}

        void drawCommandString (unsigned int x,
                                unsigned int y,
                                const char* text,
                                unsigned int pos,
                                bool active);
        void drawString (   unsigned int x,
                            unsigned int y,
                            const char* text,
                            Color fg = Color(WHITE),
                            Color bg = Color(BLACK));
    public:
        unsigned int x = 0;
        unsigned int y = 0;
        Color fg = Color(WHITE);
        Color bg = Color(BLACK);
        
    private:
        unsigned int m_xOffset = 0;
        unsigned int m_yOffset = 0;
        GraphicsInterface*  m_graphics = nullptr;
};

#endif
