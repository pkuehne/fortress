#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "../core/graphics.h"

typedef void(*KeyFunc)(unsigned char);

class Window;

class Widget {
    public:
        Widget() {}
        virtual ~Widget() {}

        // Methods to set basic info on creation
        void setWindowOffsets(unsigned int x, unsigned int y) {
            m_xOffset = x; m_yOffset = y;
        }
        void setGraphics(GraphicsInterface* graphics) { m_graphics = graphics; }
        
        void setName(std::string& name) { m_name = name; }
        void realignWidget(unsigned int screenWidth, unsigned int screenHeight);

        void keyDown(unsigned char key) { keyPress(key); } // Not overridable
        virtual void keyPress (unsigned char key);  // Overridable

        // Utility methods for widgets
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

        // Overridable methods
        virtual void render() {}
        KeyFunc onKeyPress = nullptr;

        const std::string& name() { return m_name; }

    public:
        enum class HorizontalAlign { Left, Centre, Right, };
        enum class VerticalAlign { Top, Centre, Bottom, };
    public:
        unsigned int x = 1;
        unsigned int y = 1;
        unsigned int width = 1;
        unsigned int height = 1;
        HorizontalAlign hAlign = HorizontalAlign::Left;
        VerticalAlign vAlign = VerticalAlign::Top;

        Color fg = Color(WHITE);
        Color bg = Color(BLACK);
        
        Window* window = nullptr;

    private:
        unsigned int m_xOffset  = 0;
        unsigned int m_yOffset  = 0;
        unsigned int m_xPos     = 0;
        unsigned int m_yPos     = 0;
        GraphicsInterface*  m_graphics = nullptr;
        std::string  m_name     = "";
};

#endif
