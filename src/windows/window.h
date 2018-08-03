#pragma once

#include "../core/game_engine.h"
#include "../widgets/widget.h"

#include <map>

class Window {
public:
    /// \brief Controls the behaviour on the Window when the Esc key is presed
    enum class EscapeBehaviour {
        None,
        CloseWindow,
        QuitGame ///!< Terminates the game immediately
    };

public:
    static const int MAX_BUTTONS = 5;

    Window() {}
    virtual ~Window() {
        for (auto w : m_widgets) {
            delete w.second;
        }
    }
    virtual void destroy(void);
    virtual int getXOffset() { return m_xOffset; }
    virtual int getYOffset() { return m_yOffset; }
    virtual int getWidth() { return m_width; }
    virtual int getHeight() { return m_height; }
    virtual void resize();
    virtual void nextTurn() {}

    virtual void keyDown(unsigned char key);
    virtual void keyUp(unsigned char key) { ascii_keys[key] = false; }
    virtual bool getKey(unsigned char key) { return ascii_keys[key]; }
    virtual void mouseDown(int x, int y, int button);
    virtual void mouseUp(int x, int y, int button);

    virtual void beforeRedraw();
    virtual void redraw(){};
    virtual void renderWidgets();
    virtual void afterRedraw();

    template <class T>
    T* createWidget(std::string name, unsigned int x, unsigned int y,
                    Widget* parent = 0) {
        T* widget = new T();
        widget->setGraphics(m_graphics)
            ->setName(name)
            ->setX(x)
            ->setY(y)
            ->setWindow(this);
        if (!parent) {
            widget->setParent(m_baseWidget);
            if (m_baseWidget) {
                m_baseWidget->addChild(widget);
            }
        } else {
            widget->setParent(parent);
            parent->addChild(widget);
        }
        m_widgets[name] = widget;

        return widget;
    }

    // Non-overridable
    template <class T> T* getWidget(std::string name) {
        T* widget = dynamic_cast<T*>(m_widgets[name]);
        if (!widget) {
            throw("Widget '" + name + "' does not exist");
        }
        return widget;
    }
    void initialise(GameEngine* a_engine);

    void setFullscreen(bool fullscreen = true);
    void setTitle(const std::string& title);
    void setWidth(unsigned int width) {
        m_width = width;
        resize();
    }
    void setHeight(unsigned int height) {
        m_height = height;
        resize();
    }
    void setEscapeBehaviour(EscapeBehaviour b) { m_onEscape = b; }

    virtual GameEngine* getEngine() { return m_engine; }
    virtual GameState* getState() { return m_state; }
    virtual WindowManager* getManager() { return m_manager; }

    // Overrideable methods
    virtual void keyPress(unsigned char key) { /* Overrideable */
    }
    virtual void setup() { /* Overrideable */
    }
    virtual void registerWidgets() {}

private:
    void setDimensions(int x, int y, int width, int height);

private:
    bool ascii_keys[256] = {0};
    bool special_keys[256] = {0};
    int m_buttons[MAX_BUTTONS] = {0};
    GameEngine* m_engine = nullptr;
    GraphicsInterface* m_graphics = nullptr;
    GameState* m_state = nullptr;
    WindowManager* m_manager = nullptr;
    int m_xOffset = 0;
    int m_yOffset = 0;
    int m_width = 0;
    int m_height = 0;
    bool m_fullscreen = 0;
    std::string m_title;
    EscapeBehaviour m_onEscape = EscapeBehaviour::None;
    std::map<std::string, Widget*> m_widgets;
    Widget* m_baseWidget = nullptr;
};
