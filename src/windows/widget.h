#ifndef __WIDGET_H__
#define __WIDGET_H__

#include "../core/graphics.h"

typedef void (*KeyFunc)(unsigned char);

class Window;

class Widget
{
  public:
    enum class HorizontalAlign
    {
        Left,
        Centre,
        Right,
    };
    enum class VerticalAlign
    {
        Top,
        Centre,
        Bottom,
    };

  public:
    Widget() {}
    virtual ~Widget() {}

    // Methods to set basic info on creation
    Widget *setWindowOffsets(unsigned int x, unsigned int y)
    {
        m_xOffset = x;
        m_yOffset = y;
        return this;
    }
    Widget *setGraphics(GraphicsInterface *graphics)
    {
        m_graphics = graphics;
        return this;
    }

    Widget *setName(std::string &name)
    {
        m_name = name;
        return this;
    }
    std::string getName() const
    {
        return m_name;
    }
    Widget *setX(unsigned int x)
    {
        this->m_x = x;
        return this;
    }
    unsigned int getX() const
    {
        return m_x;
    }
    Widget *setY(unsigned int y)
    {
        this->m_y = y;
        return this;
    }
    unsigned int getY() const
    {
        return m_y;
    }
    Widget *setWindow(Window *win)
    {
        this->m_window = win;
        return this;
    }
    Window *getWindow() const
    {
        return m_window;
    }
    Widget *setVisible(bool visible)
    {
        this->m_visible = visible;
        return this;
    }
    bool getVisible() const
    {
        return m_visible;
    }
    Widget* setSensitive(bool sensitive)
    {
        m_sensitive = sensitive;
        return this;
    }
    bool getSensitive() const
    {
        return m_sensitive;
    }
    Widget *setWidth(unsigned int width)
    {
        this->m_width = width;
        return this;
    }
    unsigned int getWidth()
    {
        return m_width;
    }
    Widget *setHeight(unsigned int height)
    {
        this->m_height = height;
        return this;
    }
    unsigned int getHeight()
    {
        return m_height;
    }
    Widget *setHorizontalAlign(HorizontalAlign align)
    {
        m_hAlign = align;
        return this;
    }
    HorizontalAlign getHorizontalAlign()
    {
        return m_hAlign;
    }
    Widget *setVerticalAlign(VerticalAlign align)
    {
        m_vAlign = align;
        return this;
    }
    VerticalAlign getVerticalAlign()
    {
        return m_vAlign;
    }
    Widget *setForegroundColor(Color color)
    {
        m_fgColor = color;
        return this;
    }
    Color getForegroundColor()
    {
        return m_fgColor;
    }
    Widget *setBackgroundColor(Color color)
    {
        m_bgColor = color;
        return this;
    }
    Color getBackgroundColor()
    {
        return m_bgColor;
    }

    // Subclass overrideable
    virtual void keyPress(unsigned char key);
    virtual void render() {}

    // Callbacks
    KeyFunc onKeyPress = nullptr;

    // Utility methods for widgets
    Widget *drawCommandString(unsigned int x,
                              unsigned int y,
                              const char *text,
                              unsigned int pos,
                              bool active);
    Widget *drawString(unsigned int x,
                       unsigned int y,
                       const char *text,
                       Color fg = Color(WHITE),
                       Color bg = Color(BLACK));

    // Internal Methods
    Widget *realignWidget(unsigned int screenWidth, unsigned int screenHeight);
    void keyDown(unsigned char key) { keyPress(key); }

  private:
    Window *m_window = nullptr;
    unsigned int m_x = 1; ///< The Window X offset
    unsigned int m_y = 1; ///< The Window Y offset

    unsigned int m_xOffset = 0; ///< X Offset within the Window
    unsigned int m_yOffset = 0; ///< Y Offset within the Window
    unsigned int m_xPos = 0;    ///< The actual X position on screen
    unsigned int m_yPos = 0;    ///< The actual Y position on screen
    unsigned int m_width = 1;
    unsigned int m_height = 1;

    GraphicsInterface *m_graphics = nullptr;
    std::string m_name = "";
    bool m_visible = true;
    bool m_sensitive = true;

    HorizontalAlign m_hAlign = HorizontalAlign::Left;
    VerticalAlign m_vAlign = VerticalAlign::Top;
    Color m_fgColor = Color(WHITE);
    Color m_bgColor = Color(BLACK);
};

#endif
