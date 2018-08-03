#ifndef __WINDOW_MANAGER_H__
#define __WINDOW_MANAGER_H__

#include <memory>
#include <vector>

class GameEngine;
class Window;

class WindowManager {
public:
    enum class NextWindowAction { None, Replace, ReplaceAll };

public:
    WindowManager() = default;
    virtual ~WindowManager() = default;

    virtual void initialise(GameEngine* engine);
    virtual void pushWindow(Window* win);
    virtual void popWindow();
    // void replaceWindow(Window* win);
    virtual void replaceAllWindows(Window* win);
    virtual Window* getActive();
    virtual void resize();
    virtual void nextTick();
    virtual void nextTurn();

    virtual void registerWindow(Window* win);

    template <typename T> T* createWindow() {
        T* win = new T();
        win->initialise(m_engine);
        pushWindow(win);
        return win;
    }

    template <typename T, typename A>
    T* createWindow(std::shared_ptr<A>& arguments) {
        T* win = new T();
        win->setArguments(arguments);
        win->initialise(m_engine);
        pushWindow(win);
        return win;
    }

private:
    virtual void manageNextWindow();

private:
    GameEngine* m_engine = nullptr;
    std::vector<Window*> m_windows;
    Window* m_nextWindow = nullptr;
    NextWindowAction m_nextAction = NextWindowAction::None;
};

#endif
