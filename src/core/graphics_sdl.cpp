#include "graphics_sdl.h"
#include "utility.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <spdlog/spdlog.h>

GraphicsSDL::Texture GraphicsSDL::loadTexture(const std::string& name,
                                              unsigned int cols,
                                              unsigned int rows) {
    // The final texture
    Texture texture;

    texture.rows = rows ? rows : 16;
    texture.cols = cols ? cols : 16;

    std::string filename = std::string("../graphics/");
    filename.append(name);

    // Load image at specified path
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (surface == nullptr) {
        spdlog::error("Unable to load image {} SDL_image Error: {}", filename,
                      IMG_GetError());
        throw std::runtime_error("Failed to load texture");
    }
    auto magenta = SDL_MapRGB(surface->format, 255, 0, 255);
    SDL_SetColorKey(surface, SDL_TRUE, magenta); // Make it transparent
    texture.width = surface->w;
    texture.height = surface->h;

    // Create texture from surface pixels
    texture.ptr = SDL_CreateTextureFromSurface(m_renderer, surface);
    if (texture.ptr == nullptr) {
        spdlog::error("Unable to create texture from surface. SDL Error: {}",
                      SDL_GetError());
        throw std::runtime_error("Failed to create texture from surface");
    }
    // SDL_SetTextureBlendMode(texture.ptr, SDL_BLENDMODE_BLEND);

    // Get rid of old loaded surface
    SDL_FreeSurface(surface);

    return texture;
}

void GraphicsSDL::initialise(int argc, char** argv) {
    spdlog::info("Initializing Graphics");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        spdlog::error("Failed to initialize SDL: {}", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL");
    }

    m_width = 0;
    m_height = 0;
    m_tileHeight = m_config.tileHeight;
    m_tileWidth = m_config.tileWidth;

    if (!m_config.fullscreen) {
        m_width = m_config.windowWidth;
        m_height = m_config.windowHeight;
    }

    Uint32 flags = 0;
    if (m_config.fullscreen) {
        spdlog::info("Setting to fullscreen");
        flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_ALLOW_HIGHDPI;
    }
    m_window = SDL_CreateWindow("SDL Tutorial", 0, 0, m_width, m_height, flags);
    if (m_window == nullptr) {
        spdlog::error("Failed to create SDL Window: {}", SDL_GetError());
        throw std::runtime_error("Failed to create SDL Window");
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == nullptr) {
        spdlog::error("Failed to create SDL Renderer: {}", SDL_GetError());
        throw std::runtime_error("Failed to create SDL Renderer");
    }
    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_GetRendererOutputSize(m_renderer, &m_width, &m_height);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    spdlog::info("Window ({}x{}) Tile ({}x{})", m_width, m_height, m_tileWidth,
                 m_tileHeight);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        spdlog::error("Failed to initialize IMG: {}", IMG_GetError());
        throw std::runtime_error("Failed to initialize IMG");
    }

    setDisplayFunc([]() {});

    m_tileTexture = loadTexture(m_config.tileset, m_config.tileset_rows,
                                m_config.tileset_cols);

    m_fontTexture = loadTexture(m_config.fontset, m_config.fontset_rows,
                                m_config.fontset_cols);
}

/// @brief Converts SDL key code to our enum
/// @param[in,out] key The key code to convert
int convert_key(SDL_Keysym code) {

    int key = code.sym;

    if (key == SDLK_ESCAPE) {
        return KEY_ESC;
    }
    if (key == SDLK_TAB) {
        return KEY_TAB;
    }
    if (key == SDLK_RETURN) {
        return KEY_ENTER;
    }
    if (key == SDLK_UP) {
        return KEY_UP;
    }
    if (key == SDLK_DOWN) {
        return KEY_DOWN;
    }
    if (key == SDLK_LEFT) {
        return KEY_LEFT;
    }
    if (key == SDLK_RIGHT) {
        return KEY_RIGHT;
    }
    if (key == SDLK_BACKSPACE) {
        return KEY_BACKSPACE;
    }
    if (code.mod & KMOD_SHIFT && key > 32) {
        key -= 32;
    }
    return key;
}

void GraphicsSDL::spin() {
    SDL_Event e;
    while (m_running) {
        while (SDL_PollEvent(&e) != 0) {
            // User requests quit
            if (e.type == SDL_QUIT) {
                m_running = false;
            }
            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    spdlog::info("Resize event received ({}x{})",
                                 e.window.data1, e.window.data2);
                    m_resizeFunc(e.window.data1, e.window.data2);
                }
            }
            if (e.type == SDL_KEYDOWN) {
                unsigned char key =
                    static_cast<unsigned char>(convert_key(e.key.keysym));
                m_keyDownFunc(key, 0, 0);
            }
            if (e.type == SDL_KEYUP) {
                unsigned char key =
                    static_cast<unsigned char>(convert_key(e.key.keysym));
                m_keyUpFunc(key, 0, 0);
            }
        }
        m_displayFunc();
    }
}

void GraphicsSDL::updateScreenSize(int width, int height) {
    spdlog::info("Resizing to {}x{}", width, height);
    m_width = width;
    m_height = height;
}

int GraphicsSDL::getScreenHeight() { return (m_height / m_tileHeight); }

int GraphicsSDL::getScreenWidth() { return (m_width / m_tileWidth); }

void GraphicsSDL::beginScreenUpdate() { SDL_RenderClear(m_renderer); }

void GraphicsSDL::endScreenUpdate() { SDL_RenderPresent(m_renderer); }

void GraphicsSDL::drawRect(const Texture& texture, int x, int y, int tile,
                           Color fg, Color bg) {
    int tileCol = tile % texture.cols;
    int tileRow = (tile - (tileCol)) / texture.cols;
    int tileWidth = texture.width / texture.cols;
    int tileHeight = texture.height / texture.cols;

    SDL_Rect source = {tileCol * tileWidth, tileRow * tileHeight, tileWidth,
                       tileHeight};
    SDL_Rect destination = {x * m_tileWidth, y * m_tileHeight, m_tileWidth,
                            m_tileHeight};

    SDL_SetTextureColorMod(texture.ptr, fg.Red(), fg.Green(), fg.Blue());
    SDL_RenderCopy(m_renderer, texture.ptr, &source, &destination);
}

unsigned int GraphicsSDL::drawString(int y, int x, const char* s, Color fg,
                                     Color bg) {
    int offset = 0;
    while (*s != '\0') {
        drawRect(m_fontTexture, x + offset++, y,
                 static_cast<unsigned int>(*s++), fg, bg);
    }
    return offset;
}

void GraphicsSDL::drawTile(int y, int x, unsigned int tile, Color fg,
                           Color bg) {
    drawRect(m_tileTexture, x, y, tile, fg, bg);
}

void GraphicsSDL::drawBorder(int y, int x, int height, int width) {
    // Draw Corners
    drawTile(y, x, 201, Color(WHITE), Color(WHITE));
    drawTile(y + 1 + height, x, 200, Color(WHITE), Color(WHITE));
    drawTile(y, x + 1 + width, 187, Color(WHITE), Color(WHITE));
    drawTile(y + 1 + height, x + 1 + width, 188, Color(WHITE), Color(WHITE));

    // Draw Horizontals
    for (int xx = x + 1; xx <= x + width; xx++) {
        drawTile(y, xx, 205, Color(WHITE), Color(WHITE));
        drawTile(y + height + 1, xx, 205, Color(WHITE), Color(WHITE));
    }

    // Draw Verticals
    for (int yy = y + 1; yy <= y + height; yy++) {
        drawTile(yy, x, 186, Color(WHITE), Color(WHITE));
        drawTile(yy, x + width + 1, 186, Color(WHITE), Color(WHITE));
    }
}

void GraphicsSDL::clearArea(int y, int x, int height, int width) {
    SDL_Rect rect = {x * m_tileWidth, y * m_tileHeight, width * m_tileWidth,
                     height * m_tileHeight};
    SDL_RenderFillRect(m_renderer, &rect);
}

void GraphicsSDL::calculateWindowOffsetsFromCentre(int height, int width,
                                                   int& y, int& x) {
    int screenWidth = getScreenWidth();
    int screenHeight = getScreenHeight();

    x = (screenWidth / 2) - (width / 2);
    y = (screenHeight / 2) - (height / 2);
}
