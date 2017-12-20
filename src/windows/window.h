#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "widget.h"
#include "label.h"
#include "../core/game_engine.h"

#include <map>

class Window
{
    public:
        static const int MAX_BUTTONS = 5;

        Window() {}
        virtual ~Window() { }
        virtual void destroy (void);
        virtual int getXOffset() { return m_xOffset; }
        virtual int getYOffset() { return m_yOffset; }
        virtual int getWidth() { return m_width; }
        virtual int getHeight() { return m_height; }
        virtual void resize() { setDimensions (m_xOffset, m_yOffset, m_width, m_height); }
        virtual void update() { }

        virtual unsigned int drawString (int y, int x, const char* text, Color fg = Color(WHITE), Color bg = Color(BLACK));
        unsigned int drawCommandString (int y, int x, const char* text, int pos, bool active = true);
        virtual void drawTile (int y, int x, unsigned int tile, Color fg, Color bg);
        virtual void drawBorder (int y, int x, int height, int width);
        virtual void clearArea (int y, int x, int height, int width);

        virtual void keyDown (unsigned char key);
        virtual void keyUp (unsigned char key) { ascii_keys[key] = false; }
        virtual bool getKey (unsigned char key) { return ascii_keys[key]; }
        virtual void mouseDown (int x, int y, int button);
        virtual void mouseUp (int x, int y, int button);
        virtual bool getMouseButton (int button);
        virtual void beforeRedraw();
        virtual void redraw () { };
        virtual void renderWidgets();
        virtual void afterRedraw();
        virtual void resize (int width, int height);

        virtual void gainFocus() { };
        virtual void loseFocus() { };

        virtual void drawProgress (unsigned int x, unsigned int y, unsigned int value, unsigned int max);
        virtual unsigned int wrapText (const std::string& text, std::vector<std::string>& lines, unsigned int maxWidth, unsigned int maxRows);

        template<class T> T* createWidget(
                std::string name,
                unsigned int x,
                unsigned int y)
        {
            T* w = new T();
            w->setWindowOffsets(m_xOffset, m_yOffset);
            w->setGraphics(m_graphics);
            w->setName(name);
            w->x = x;
            w->y = y;
            w->window = this;
            m_widgets[name] = w;

            return w;
        };

        // Non-overridable
        template<class T>
            T* getWidget(std::string name) { return dynamic_cast<T*>(m_widgets[name]); }
        void initialise (GameEngine* a_engine, void* Args = 0, void* Retval = 0);
        void* getArgs() { return m_args; }
        void* getRetval() { return m_retval; }

        void setTitle (const std::string& title) { m_title = title; }
        void setFullscreen(bool fullscreen) { m_fullscreen = true; }
        void setDimensions (int x, int y, int width, int height);

        virtual GameEngine* getEngine() { return m_engine; }
        virtual GameState* getState() { return m_state; }
        virtual WindowManager* getManager() { return m_manager; }

        // Overrideable methods
        virtual void keyPress (unsigned char key) { /* Overrideable */ }
        virtual void setup() { /* Overrideable */ }
        virtual void registerWidgets() { }

    private:
        bool                    ascii_keys[256]     = {0};
        bool                    special_keys[256]   = {0};
        int                     m_buttons[MAX_BUTTONS] = {0};
        GameEngine*             m_engine    = nullptr;
        GraphicsInterface*      m_graphics  = nullptr;
        GameState*              m_state     = nullptr;
        WindowManager*          m_manager   = nullptr;
        void*                   m_args      = nullptr;
        void*                   m_retval    = nullptr;
        int                     m_xOffset   = 0;
        int                     m_yOffset   = 0;
        int                     m_width     = 0;
        int                     m_height    = 0;
        std::string             m_title;
        bool                    m_fullscreen= false;
        // std::vector<Widget*>    m_widgets;
        std::map<std::string, Widget*>  m_widgets;
};

#endif
