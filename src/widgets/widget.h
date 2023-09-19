#pragma once

#include "../core/graphics_sdl.h"
#include <functional>
#include <map>
#include <memory>

typedef std::function<void(unsigned char)> KeyFunc;

class Window;

class Widget {
public:
    enum class HorizontalAlign {
        Left,
        Centre,
        Right,
    };
    enum class VerticalAlign {
        Top,
        Centre,
        Bottom,
    };
    enum class HorizontalSizing {
        Fixed,
        Stretch,
    };
    enum class VerticalSizing {
        Fixed,
        Stretch,
    };

public:
    Widget() {}
    virtual ~Widget() {}

    virtual Widget* setGraphics(std::shared_ptr<GraphicsInterface> graphics) {
        m_graphics = graphics;
        return this;
    }

    virtual Widget* setName(std::string& name) {
        m_name = name;
        return this;
    }
    virtual std::string getName() const { return m_name; }
    virtual Widget* setX(unsigned int x) {
        this->m_relativeXPos = x;
        return this;
    }
    virtual unsigned int getX() const { return m_relativeXPos; }
    virtual Widget* setY(unsigned int y) {
        this->m_relativeYPos = y;
        return this;
    }
    virtual unsigned int getY() const { return m_relativeYPos; }
    virtual Widget* setWindow(Window* win) {
        this->m_window = win;
        return this;
    }
    virtual Window* getWindow() const { return m_window; }
    virtual Widget* setParent(Widget* parent) {
        m_parent = parent;
        return this;
    }
    virtual Widget* getParent() { return m_parent; }
    virtual Widget* addChild(Widget* child) {
        m_children[child->getName()] = child;
        return this;
    }
    virtual std::map<std::string, Widget*> getChildren() { return m_children; }

    virtual Widget* setVisible(bool visible) {
        this->m_visible = visible;
        return this;
    }
    virtual bool getVisible() const { return m_visible; }
    virtual Widget* setSensitive(bool sensitive) {
        m_sensitive = sensitive;
        return this;
    }
    virtual bool getSensitive() const { return m_sensitive; }
    virtual Widget* setWidth(unsigned int width) {
        this->m_width = width;
        this->m_hSizing = HorizontalSizing::Fixed;
        return this;
    }
    virtual unsigned int getWidth() { return m_width; }
    virtual Widget* setWidthStretchMargin(unsigned int margin) {
        this->m_widthStretchMargin = margin;
        this->m_hSizing = HorizontalSizing::Stretch;
        return this;
    }
    virtual unsigned int getWidthStretchMargin() {
        return this->m_widthStretchMargin;
    }
    virtual HorizontalSizing getHorizontalSizing() { return this->m_hSizing; }
    virtual Widget* setHorizontalAlign(HorizontalAlign align) {
        m_hAlign = align;
        return this;
    }
    virtual HorizontalAlign getHorizontalAlign() { return m_hAlign; }

    virtual Widget* setHeight(unsigned int height) {
        this->m_height = height;
        this->m_vSizing = VerticalSizing::Fixed;
        return this;
    }
    virtual unsigned int getHeight() { return m_height; }
    virtual Widget* setHeightStretchMargin(unsigned int margin) {
        this->m_heightStretchMargin = margin;
        this->m_vSizing = VerticalSizing::Stretch;
        return this;
    }
    virtual unsigned int getHeightStretchMargin() {
        return this->m_heightStretchMargin;
    }
    virtual VerticalSizing getVerticalSizing() { return this->m_vSizing; }
    virtual Widget* setVerticalAlign(VerticalAlign align) {
        m_vAlign = align;
        return this;
    }
    virtual VerticalAlign getVerticalAlign() { return m_vAlign; }
    virtual Widget* setForegroundColor(Color color) {
        m_fgColor = color;
        return this;
    }
    virtual Color getForegroundColor() { return m_fgColor; }
    virtual Widget* setBackgroundColor(Color color) {
        m_bgColor = color;
        return this;
    }
    virtual Color getBackgroundColor() { return m_bgColor; }
    virtual unsigned int getXPos() { return m_xPos; }
    virtual unsigned int getYPos() { return m_yPos; }

    // Subclass overrideable
    virtual void keyPress(unsigned char key) {}
    virtual void render() {}
    virtual void realign(unsigned int xOrigin, unsigned int yOrigin,
                         unsigned int parentWidth, unsigned int parentHeight);

    // Callbacks
    KeyFunc onKeyPress = nullptr;

    // Utility methods for widgets
    Widget* drawCommandString(unsigned int x, unsigned int y, const char* text,
                              unsigned int pos, bool active);
    Widget* drawString(unsigned int x, unsigned int y, const char* text,
                       Color fg = Color(WHITE), Color bg = Color(BLACK));
    Widget* drawTile(unsigned int x, unsigned int y, unsigned char text,
                     Color fg = Color(WHITE), Color bg = Color(BLACK));
    Widget* drawBorder();
    Widget* drawBorder(unsigned int x, unsigned int y, unsigned int width,
                       unsigned int height);
    Widget* clearArea(unsigned int x, unsigned int y, unsigned int width,
                      unsigned int height);

private:
    Window* m_window = nullptr;
    Widget* m_parent = nullptr;
    std::map<std::string, Widget*> m_children;

    unsigned int m_relativeXPos =
        0; ///< The relative left position within the parent widget
    unsigned int m_relativeYPos =
        0; ///< The relative top position within the parent widget

    unsigned int m_xPos =
        0; ///< The absolute left position of the widget on screen
    unsigned int m_yPos =
        0; ///< The absolute top position of the widget on screen
    unsigned int m_width = 1;
    unsigned int m_height = 1;
    unsigned int m_widthStretchMargin = 0;
    unsigned int m_heightStretchMargin = 0;

    std::shared_ptr<GraphicsInterface> m_graphics = nullptr;
    std::string m_name = "";
    bool m_visible = true;
    bool m_sensitive = true;

    HorizontalAlign m_hAlign = HorizontalAlign::Left;
    VerticalAlign m_vAlign = VerticalAlign::Top;
    HorizontalSizing m_hSizing = HorizontalSizing::Fixed;
    VerticalSizing m_vSizing = VerticalSizing::Fixed;
    Color m_fgColor = Color(WHITE);
    Color m_bgColor = Color(BLACK);
};
