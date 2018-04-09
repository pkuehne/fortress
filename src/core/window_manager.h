#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include <vector>

class GameEngine;
class Window;

class WindowManager
{
  public:
    enum class NextWindowAction
    {
        Replace,
        ReplaceAll
    };

  public:
    WindowManager() {}
    void initialise(GameEngine *engine);
    void pushWindow(Window *win);
    void popWindow();
    void replaceWindow(Window *win);
    void replaceAllWindows(Window *win);
    Window *getActive();
    void redraw();
    void resize();
    void nextTick();
    void nextTurn();

    template <typename T>
    T *createWindow(void *args = nullptr, void *retval = nullptr)
    {
        T *win = new T();
        win->initialise(m_engine, args, retval);
        pushWindow(win);
        return win;
    }

  private:
    void manageNextWindow();

  private:
    GameEngine *m_engine = nullptr;
    std::vector<Window *> m_windows;
    Window *m_nextWindow;
    NextWindowAction m_nextAction;
};

#endif
