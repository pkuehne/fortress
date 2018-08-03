#pragma once

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

private:
    virtual void manageNextWindow();

private:
    GameEngine* m_engine = nullptr;
    std::vector<std::shared_ptr<Window>> m_windows;
    std::shared_ptr<Window> m_nextWindow = nullptr;
    NextWindowAction m_nextAction = NextWindowAction::None;
};
