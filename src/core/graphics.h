#pragma once

#include "color.h"
#include "config_manager.h"
#include "graphics_interface.h"
#include <GLFW/glfw3.h>

struct Texture {
    GLuint id = 0;
    std::string name;
    int textureWidth = 0;
    int textureHeight = 0;
    unsigned int numRows = 16;
    unsigned int numCols = 16;
    float tileWidth = 0;
    float tileHeight = 0;
};

class Graphics : public GraphicsInterface {
public:
    virtual ~Graphics() {}
    virtual void initialise(int argc, char** argv);
    virtual void spin();

    virtual Texture loadTexture(std::string, unsigned int cols,
                                unsigned int rows);

    virtual unsigned int drawString(int y, int x, const char* s,
                                    Color fg = Color(WHITE),
                                    Color bg = Color(BLACK));
    virtual void drawTile(int y, int x, unsigned int tile, Color fg, Color bg);

    virtual void drawBorder(int y, int x, int height, int width);
    virtual void clearArea(int y, int x, int height, int width);
    virtual void calculateWindowOffsetsFromCentre(int height, int width, int& y,
                                                  int& x);
    virtual void terminate() { glfwSetWindowShouldClose(m_window, 1); }

    virtual void beginScreenUpdate();
    virtual void endScreenUpdate();

    virtual int getScreenHeight();
    virtual int getScreenWidth();

    virtual void updateScreenSize(int width, int height);
    virtual void updateTileSize(unsigned int width, unsigned int height);
    virtual unsigned int getTileWidth() { return m_tileWidth; }
    virtual unsigned int getTileHeight() { return m_tileHeight; }

    virtual void setKeyDownFunc(KeyboardFuncPtr func);
    virtual void setKeyUpFunc(KeyboardFuncPtr func);
    virtual void setDisplayFunc(DisplayFuncPtr func);
    virtual void setMouseFunc(MouseFuncPtr func);
    virtual void setResizeFunc(ResizeFuncPtr func);

    virtual void callResizeFunc(int width, int height);
    virtual void callKeyboardFunc(int key, int scancode, int action, int mods);

private:
    virtual void drawRect(Texture& texture, int x, int y, unsigned int tile,
                          Color fg, Color bg);

private:
    ConfigManager m_config = ConfigManager("../config/config.yaml");
    int m_width = 0;
    int m_height = 0;
    GLFWwindow* m_window = 0;
    DisplayFuncPtr m_displayFunc = nullptr;
    ResizeFuncPtr m_resizeFunc = nullptr;
    KeyboardFuncPtr m_keyDownFunc = nullptr;
    KeyboardFuncPtr m_keyUpFunc = nullptr;
    Texture m_tileTexture;
    Texture m_fontTexture;
    unsigned int m_tileWidth = 0; // How big the tiles are on screen
    unsigned int m_tileHeight = 0;
};

void start_graphics();
