#pragma once

#include <memory>
#include <vector>

class GameEngine;
class Window;

class WindowManager {

public:
    WindowManager() = default;
    virtual ~WindowManager() = default;

    virtual void initialise(GameEngine* engine);
    virtual void pushWindow(std::shared_ptr<Window> win);

    virtual void popWindow();
    virtual void popAllWindows();
    virtual std::shared_ptr<Window> getActive();
    virtual void resize();
    virtual void nextTick();
    virtual void nextTurn();

private:
    virtual void removeWindow(std::shared_ptr<Window> win);

private:
    GameEngine* m_engine = nullptr;
    std::vector<std::shared_ptr<Window>> m_windows;
};
