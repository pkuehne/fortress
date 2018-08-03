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
    virtual void pushWindow(std::shared_ptr<Window> win);
    virtual void removeWindow(std::shared_ptr<Window> win);

    virtual void popWindow();
    // void replaceWindow(Window* win);
    virtual void replaceAllWindows(std::shared_ptr<Window> win);
    virtual std::shared_ptr<Window> getActive();
    virtual void resize();
    virtual void nextTick();
    virtual void nextTurn();

    virtual void registerWindow(std::shared_ptr<Window> win);

    template <typename T> std::shared_ptr<T> createWindow() {
        auto win = std::make_shared<T>();
        win->initialise(m_engine);
        pushWindow(win);
        return win;
    }

    template <typename T, typename A>
    std::shared_ptr<T> createWindow(std::shared_ptr<A>& arguments) {
        auto win = std::make_shared<T>();
        win->setArguments(arguments);
        win->initialise(m_engine);
        pushWindow(win);
        return win;
    }

private:
    virtual void manageNextWindow();

private:
    GameEngine* m_engine = nullptr;
    std::vector<std::shared_ptr<Window>> m_windows;
    std::shared_ptr<Window> m_nextWindow = nullptr;
    NextWindowAction m_nextAction = NextWindowAction::None;
};

#endif
