#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "widget.h"
#include "../core/game_engine.h"

#include <map>

class Window
{
  public:
    /// \brief Controls the behaviour on the Window when the Esc key is presed
    enum class EscapeBehaviour
    {
        None,
        CloseWindow,
        QuitGame ///!< Terminates the game immediately
    };

  public:
    static const int MAX_BUTTONS = 5;

    Window() {}
    virtual ~Window() {}
    virtual void destroy(void);
    virtual int getXOffset() { return m_xOffset; }
    virtual int getYOffset() { return m_yOffset; }
    virtual int getWidth() { return m_width; }
    virtual int getHeight() { return m_height; }
    virtual void resize();
    virtual void update() {}

    // All of these can be removed when MapWindow has been migrated
    virtual unsigned int drawString(int y, int x, const char *text, Color fg = Color(WHITE), Color bg = Color(BLACK));
    unsigned int drawCommandString(int y, int x, const char *text, int pos, bool active = true);
    virtual void drawTile(int y, int x, unsigned int tile, Color fg, Color bg);
    virtual void drawBorder(int y, int x, int height, int width);
    virtual void clearArea(int y, int x, int height, int width);
    virtual void drawProgress(unsigned int x, unsigned int y, unsigned int value, unsigned int max);
    virtual unsigned int wrapText(const std::string &text, std::vector<std::string> &lines, unsigned int maxWidth, unsigned int maxRows);

    virtual void keyDown(unsigned char key);
    virtual void keyUp(unsigned char key) { ascii_keys[key] = false; }
    virtual bool getKey(unsigned char key) { return ascii_keys[key]; }
    virtual void mouseDown(int x, int y, int button);
    virtual void mouseUp(int x, int y, int button);
    virtual bool getMouseButton(int button);

    virtual void beforeRedraw();
    virtual void redraw(){};
    virtual void renderWidgets();
    virtual void afterRedraw();

    virtual void gainFocus(){};
    virtual void loseFocus(){};

    template <class T>
    T *createWidget(
        std::string name,
        unsigned int x,
        unsigned int y,
        Widget *parent = 0)
    {
        T *widget = new T(); // TODO: Clean this up in the destructor!
        widget
            ->setWindowOffsets(m_xOffset, m_yOffset)
            ->setGraphics(m_graphics)
            ->setName(name)
            ->setX(x)
            ->setY(y)
            ->setWindow(this);
        if (!parent)
        {
            widget->setParent(m_baseWidget);
            if (m_baseWidget)
            {
                m_baseWidget->addChild(widget);
            }
        }
        else
        {
            widget->setParent(parent);
            parent->addChild(widget);
        }
        m_widgets[name] = widget;

        return widget;
    };

    // Non-overridable
    template <class T>
    T *getWidget(std::string name)
    {
        T *widget = dynamic_cast<T *>(m_widgets[name]);
        if (!widget)
        {
            throw("Widget '" + name + "' does not exist");
        }
        return widget;
    }
    void initialise(GameEngine *a_engine, void *Args = 0, void *Retval = 0);
    void *getArgs() { return m_args; }
    void *getRetval() { return m_retval; }

    void setFullscreen(bool fullscreen = true);
    void setTitle(const std::string &title);
    void setWidth(unsigned int width)
    {
        m_width = width;
        resize();
    }
    void setHeight(unsigned int height)
    {
        m_height = height;
        resize();
    }
    void setEscapeBehaviour(EscapeBehaviour b) { m_onEscape = b; }

    virtual GameEngine *getEngine() { return m_engine; }
    virtual GameState *getState() { return m_state; }
    virtual WindowManager *getManager() { return m_manager; }

    // Overrideable methods
    virtual void keyPress(unsigned char key) { /* Overrideable */}
    virtual void setup() { /* Overrideable */}
    virtual void registerWidgets() {}

  private:
    void setDimensions(int x, int y, int width, int height);

  private:
    bool ascii_keys[256] = {0};
    bool special_keys[256] = {0};
    int m_buttons[MAX_BUTTONS] = {0};
    GameEngine *m_engine = nullptr;
    GraphicsInterface *m_graphics = nullptr;
    GameState *m_state = nullptr;
    WindowManager *m_manager = nullptr;
    void *m_args = nullptr;
    void *m_retval = nullptr;
    int m_xOffset = 0;
    int m_yOffset = 0;
    int m_width = 0;
    int m_height = 0;
    bool m_fullscreen = 0;
    std::string m_title;
    EscapeBehaviour m_onEscape;
    std::map<std::string, Widget *> m_widgets;
    Widget *m_baseWidget;
};

#endif
