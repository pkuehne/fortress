#include "graphics.h"
#include "gameengine.h"
#include "window.h"
#include "event.h"
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <iostream>
//#include <lodepng/lodepng.h>
#include <SOIL.h>


void drawString (int y, int x, const char* string)
{
    int offset = 0;
    while (*string != '\0')
        drawTile (y, x+offset++, static_cast<unsigned int>(*string++), Color (WHITE), Color (BLACK));
}

void drawTile (int y, int x, unsigned int tile, Color fg, Color bg)
{
    int iconSize = 12;
    float tileWidth = 1.0/16;
    float tileHeight = 1.0/48;
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

void drawBorder (int y, int x, int height, int width)
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


static void display (void)
{
    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->tick();
    l_engine->getCurrentWindow()->beforeRedraw();
    l_engine->getCurrentWindow()->redraw();
    l_engine->getCurrentWindow()->afterRedraw();
}

static void resize (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

static void keyDown (unsigned char key, int x, int y)
{
    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->getCurrentWindow()->keyDown (key);

}

static void keyUp (unsigned char key, int x, int y)
{
    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->getCurrentWindow()->keyUp (key);
}

static void mouseClick (int button, int state, int x, int y)
{
    GameEngine* l_engine = GameEngine::getEngine();
    if (state) {
        l_engine->getCurrentWindow()->mouseUp (x, y, button);
    } else {
        l_engine->getCurrentWindow()->mouseDown (x, y, button);
    }
}

void setup_graphics ()
{
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("FORTRESS");

    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable (GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDisable (GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutReshapeFunc     (resize);
    glutKeyboardFunc    (keyDown);
    glutKeyboardUpFunc  (keyUp);
    glutMouseFunc       (mouseClick);
    glutDisplayFunc     (display);
    glutIdleFunc        (display);

    std::string l_textureName ("12x12.png");
    std::cout << "Loading texture: " << l_textureName << std::endl;
    GLuint tex = SOIL_load_OGL_texture (l_textureName.c_str(),
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

void start_graphics ()
{
    glutMainLoop();
}

void beginScreenUpdate()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void endScreenUpdate()
{
    glFlush();
}
