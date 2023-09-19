#pragma once

#include "config_manager.h"
#include "graphics_interface.h"
#include <SDL2/SDL.h>

class GraphicsSDL : public GraphicsInterface {
public:
    struct Texture {
        SDL_Texture* ptr = nullptr;
        std::string name;
        int width = 0;
        int height = 0;
        unsigned int rows = 16;
        unsigned int cols = 16;
    };

    virtual ~GraphicsSDL() {}
    void initialise(int argc, char** argv) override;
    void spin() override;
    void terminate() override { m_running = false; }

    void beginScreenUpdate();
    void endScreenUpdate();

    // Questionable override methods
    int getScreenHeight() override;
    int getScreenWidth() override;

    void updateScreenSize(int width, int height) override;
    void updateTileSize(unsigned int width, unsigned int height) override {}
    unsigned int getTileWidth() override { return m_tileWidth; }
    unsigned int getTileHeight() override { return m_tileHeight; }

    void setKeyDownFunc(KeyboardFuncPtr func) override { m_keyDownFunc = func; }
    void setKeyUpFunc(KeyboardFuncPtr func) override { m_keyUpFunc = func; }
    void setDisplayFunc(DisplayFuncPtr func) override { m_displayFunc = func; }
    void setMouseFunc(MouseFuncPtr func) override {}
    void setResizeFunc(ResizeFuncPtr func) override { m_resizeFunc = func; }

    void callResizeFunc(int width, int height) override {}
    void callKeyboardFunc(int key, int scancode, int action,
                          int mods) override {}

    unsigned int drawString(int y, int x, const char* s,
                            Color fg = Color(WHITE),
                            Color bg = Color(BLACK)) override;
    void drawTile(int y, int x, unsigned int tile, Color fg, Color bg) override;

    void drawBorder(int y, int x, int height, int width) override;
    void clearArea(int y, int x, int height, int width) override;
    void calculateWindowOffsetsFromCentre(int height, int width, int& y,
                                          int& x) override;

private:
    Texture loadTexture(const std::string& filename, unsigned int cols,
                        unsigned int rows);
    void drawRect(const Texture& texture, int x, int y, int tile, Color fg,
                  Color bg);

private:
    bool m_running = true;
    ConfigManager m_config = ConfigManager("../config/config.yaml");
    SDL_Renderer* m_renderer = nullptr;
    SDL_Window* m_window = nullptr;
    Texture m_tileTexture;
    Texture m_fontTexture;

    int m_tileWidth = 0; // How big the tiles are on screen
    int m_tileHeight = 0;
    int m_width = 0;
    int m_height = 0;

    DisplayFuncPtr m_displayFunc = nullptr;
    ResizeFuncPtr m_resizeFunc = nullptr;
    KeyboardFuncPtr m_keyDownFunc = nullptr;
    KeyboardFuncPtr m_keyUpFunc = nullptr;
};