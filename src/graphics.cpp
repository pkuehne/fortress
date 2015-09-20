#include "graphics.h"
#include "utility.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <SOIL.h>

static Graphics* g_graphics = 0;

static void empty (void) {

}

void resizeWindowCallBack (GLFWwindow*, int width, int height)
{
    g_graphics->callResizeFunc (width, height);
}

void keyboardCallBack (GLFWwindow*, int key, int scancode, int action, int mods)
{
    g_graphics->callKeyboardFunc (key, scancode, action, mods);
}

void Graphics::callResizeFunc (int width, int height)
{
    m_width = width;
    m_height = height;
    if (m_resizeFunc) {
        m_resizeFunc (width, height);
    }
}

void Graphics::callKeyboardFunc (int key, int scancode, int action, int mods)
{
    if (key > 64 && key < 91 && !(mods & GLFW_MOD_SHIFT)) key += 32;
    if (key == GLFW_KEY_ESCAPE) key = ESC;
    if (key == GLFW_KEY_TAB) key = TAB;
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (m_keyDownFunc) m_keyDownFunc ((unsigned char) key, 0, 0);
    } else if (action == GLFW_RELEASE) {
        if (m_keyUpFunc) m_keyUpFunc ((unsigned char) key, 0, 0);
    }
}


unsigned int Graphics::drawString (int y, int x, const char* string, Color fg, Color bg)
{
    int offset = 0;
    while (*string != '\0') {
        drawTile (y, x+offset++, static_cast<unsigned int>(*string++), fg, bg);
    }
    return offset;
}

void Graphics::drawTile (int y, int x, unsigned int tile, Color fg, Color bg)
{
    long iconSize = m_config.getTag("IconSize").getNum();
    float tileWidth = 1.0/16;
    float tileHeight = 1.0/16;
    unsigned int tileCol = 0;
    unsigned int tileRow = 0;
    tileCol = tile % 16;
    tileRow = (tile - (tile % 16)) / 16;

    y = (m_height/iconSize) - (y+1);

    glColor3f (fg.Red(), fg.Green(), fg.Blue());
    glBegin(GL_QUADS);
       glTexCoord2f(tileWidth*(tileCol+1), tileHeight*(tileRow+1));
       glVertex2f(iconSize*(x+1), iconSize*(y+0));
       glTexCoord2f(tileWidth*(tileCol+1), tileHeight*(tileRow+0));
       glVertex2f(iconSize*(x+1), iconSize*(y+1));
       glTexCoord2f(tileWidth*(tileCol+0), tileHeight*(tileRow+0));
       glVertex2f(iconSize*(x+0), iconSize*(y+1));
       glTexCoord2f(tileWidth*(tileCol+0), tileHeight*(tileRow+1));
       glVertex2f(iconSize*(x+0), iconSize*(y+0));
    glEnd();
}

void Graphics::drawBorder (int y, int x, int height, int width)
{
    // Draw Corners
    drawTile (y, x, 201, WHITE, WHITE);
    drawTile (y+1+height, x, 200, WHITE, WHITE);
    drawTile (y, x+1+width, 187, WHITE, WHITE);
    drawTile (y+1+height, x+1+width, 188, WHITE, WHITE);

    // Draw Horizontals
    for (int xx = x+1; xx <= x+width; xx++) {
        drawTile (y, xx, 205, WHITE, WHITE);
        drawTile (y+height+1, xx, 205, WHITE, WHITE);
    }

    // Draw Verticals
    for (int yy = y+1; yy <= y+height; yy++) {
        drawTile (yy, x, 186, WHITE, WHITE);
        drawTile (yy, x+width+1, 186, WHITE, WHITE);
    }
}

void Graphics::clearArea (int y, int x, int height, int width)
{
    for (int xx = x; xx < x+width; xx++) {
        for (int yy = y; yy < y+height; yy++) {
            drawTile (yy, xx, 219, BLACK, BLACK);
        }
    }
}

int Graphics::getScreenHeight ()
{
    long iconSize = m_config.getTag("IconSize").getNum();
    return (m_height/iconSize);
}

int Graphics::getScreenWidth()
{
    long iconSize = m_config.getTag("IconSize").getNum();
    return (m_width/iconSize);
}

void Graphics::calculateWindowOffsetsFromCentre (int height, int width, int& y, int& x)
{
    int screenWidth = getScreenWidth();
    int screenHeight = getScreenHeight();

    x = (screenWidth/2) - (width / 2);
    y = (screenHeight/2) - (height / 2);
}

void Graphics::updateScreenSize (int width, int height)
{
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0, width, 0, height, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void Graphics::setKeyDownFunc (KeyboardFuncPtr func)
{
    m_keyDownFunc = func;
}

void Graphics::setKeyUpFunc (KeyboardFuncPtr func)
{
    m_keyUpFunc = func;
}

void Graphics::setDisplayFunc (DisplayFuncPtr func)
{
    m_displayFunc = func;
}

void Graphics::setMouseFunc (MouseFuncPtr func)
{

}


void Graphics::setResizeFunc (ResizeFuncPtr func)
{
    m_resizeFunc = func;
}

void Graphics::spin ()
{
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose (m_window))
    {
        double currTime = glfwGetTime();
        if (currTime > lastTime + 0.03) {
            m_displayFunc();
            glfwSwapBuffers (m_window);
            lastTime = currTime;
        }
        glfwPollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "Thank you for playing FORTRESS" << std::endl;
}

void Graphics::beginScreenUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::endScreenUpdate()
{
    glFlush();
}

void Graphics::initialise (int argc, char** argv)
{
    if (!glfwInit()) return;
    g_graphics = this;

    m_config.readFile ("config/graphics.cfg");
    m_width = 640;
    m_height = 480;

    if (m_config.getTag("Fullscreen").getNum() == 1) {
        m_window = glfwCreateWindow(m_width, m_height, "FORTRESS", NULL, NULL);
    } else {
    }

    if (!m_window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glfwSetWindowSizeCallback (m_window, resizeWindowCallBack);
    glfwSetKeyCallback (m_window, keyboardCallBack);

    updateScreenSize (m_width, m_height);

    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable (GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDisable (GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setDisplayFunc      (empty);

    std::string tileset ("graphics/");
    tileset.append (m_config.getTag("Tileset").getStr());
    GLuint tex = SOIL_load_OGL_texture (tileset.c_str(),
                                		SOIL_LOAD_AUTO,
                                		SOIL_CREATE_NEW_ID,
		                                SOIL_FLAG_MIPMAPS |
                                        SOIL_FLAG_NTSC_SAFE_RGB |
                                        SOIL_FLAG_COMPRESS_TO_DXT);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
