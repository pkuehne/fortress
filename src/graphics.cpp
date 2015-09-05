#include "graphics.h"
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <iostream>
#include <SOIL.h>

static void empty (void) {

}

unsigned int Graphics::drawString (int y, int x, const char* string, Color fg, Color bg)
{
    int offset = 0;
    while (*string != '\0') {
        drawTile (y, x+offset++, static_cast<unsigned int>(*string++), fg, bg);
        //drawTile (y, x+offset++, static_cast<unsigned int>(*string++), Color (WHITE), Color (BLACK));
    }
    return offset;
}

void Graphics::drawTile (int y, int x, unsigned int tile, Color fg, Color bg)
{
    long iconSize = m_config.getTag("IconSize").num;
    float tileWidth = 1.0/16;
    float tileHeight = 1.0/16;
    unsigned int tileCol = 0;
    unsigned int tileRow = 0;
    tileCol = tile % 16;
    tileRow = (tile - (tile % 16)) / 16;

    y = (glutGet (GLUT_WINDOW_HEIGHT)/iconSize) - (y+1);

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

    for (int yy = y+1; yy <= y+height; yy++) {
        drawTile (yy, x, 186, WHITE, WHITE);
        drawTile (yy, x+width+1, 186, WHITE, WHITE);
    }
    // Draw Verticals
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
    long iconSize = m_config.getTag("IconSize").num;
    return (glutGet (GLUT_WINDOW_HEIGHT)/iconSize);
}

int Graphics::getScreenWidth()
{
    long iconSize = m_config.getTag("IconSize").num;
    return (glutGet (GLUT_WINDOW_WIDTH)/iconSize);
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

void Graphics::setKeyboardFunc (KeyboardFuncPtr func)
{
    glutKeyboardFunc (func);
}

void Graphics::setKeyboardUpFunc (KeyboardFuncPtr func)
{
    glutKeyboardUpFunc (func);
}

void Graphics::setDisplayFunc (DisplayFuncPtr func)
{
    glutDisplayFunc (func);
    glutIdleFunc    (func);
}

void Graphics::setMouseFunc (MouseFuncPtr func)
{
    glutMouseFunc (func);
}

void Graphics::setResizeFunc (ResizeFuncPtr func)
{
    glutReshapeFunc (func);
}

void Graphics::spin ()
{
    glutMainLoop();
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
    glutInit (&argc, argv);

    m_config.readFile ("../config/graphics.cfg");
std::cout << "Width: " << m_config.getTag("WindowWidth").num << std::endl;
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (m_config.getTag("WindowWidth").num, m_config.getTag("WindowHeight").num);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("FORTRESS");

    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable (GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDisable (GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutReshapeFunc     (NULL);
    setKeyboardUpFunc   (NULL);
    setMouseFunc        (NULL);
    setDisplayFunc      (empty);

    GLuint tex = SOIL_load_OGL_texture (m_config.getTag("Tileset").str.c_str(),
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

    //delete pixels;
}
