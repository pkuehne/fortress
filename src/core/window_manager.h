#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include <vector>

class GameEngine;
class Window;

class WindowManager 
{
public:
    WindowManager() { }
    void initialise (GameEngine* engine);
    void pushWindow (Window* win);
    void popWindow ();
    void replaceWindow (Window* win);
    void replaceAllWindows (Window* win);
    Window* getActive();
    void redraw ();
    void resize ();
    void update ();

    template<typename T>
        T* createWindow(void* args = nullptr, void* retval = nullptr)
        {
            T* win = new T();
            win->initialise(m_engine, args, retval);
            pushWindow(win);
            return win;
        }
private:
    GameEngine*            m_engine = nullptr;
    std::vector<Window*>   m_windows;
};

#endif
