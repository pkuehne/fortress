#pragma once

#include "color.h"
#include "config_manager.h"
#include "graphics_interface.h"
#include <GLFW/glfw3.h>

class Graphics : public GraphicsInterface {
public:
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

    virtual ~Graphics() {}
    void initialise(int argc, char** argv) override;
    void spin() override;

    virtual Texture loadTexture(std::string, unsigned int cols,
                                unsigned int rows);

    unsigned int drawString(int y, int x, const char* s,
                            Color fg = Color(WHITE),
                            Color bg = Color(BLACK)) override;
    void drawTile(int y, int x, unsigned int tile, Color fg, Color bg) override;

    void drawBorder(int y, int x, int height, int width) override;
    void clearArea(int y, int x, int height, int width) override;
    void calculateWindowOffsetsFromCentre(int height, int width, int& y,
                                          int& x) override;
    void terminate() override { glfwSetWindowShouldClose(m_window, 1); }

    void beginScreenUpdate() override;
    void endScreenUpdate() override;

    int getScreenHeight() override;
    int getScreenWidth() override;

    void updateScreenSize(int width, int height) override;
    void updateTileSize(unsigned int width, unsigned int height) override;
    unsigned int getTileWidth() override { return m_tileWidth; }
    unsigned int getTileHeight() override { return m_tileHeight; }

    void setKeyDownFunc(KeyboardFuncPtr func) override;
    void setKeyUpFunc(KeyboardFuncPtr func) override;
    void setDisplayFunc(DisplayFuncPtr func) override;
    void setMouseFunc(MouseFuncPtr func) override;
    void setResizeFunc(ResizeFuncPtr func) override;

    void callResizeFunc(int width, int height) override;
    void callKeyboardFunc(int key, int scancode, int action, int mods) override;

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
