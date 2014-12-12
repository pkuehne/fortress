#include "screen.h"
#include "gameengine.h"
#include "window.h"
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <iostream>
#include <lodepng/lodepng.h>

unsigned char* loadImage (const char* filename)
{
    std::vector<unsigned char> pixels;
    unsigned char* image;

    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int error = 0;

    std::cout << "Loading image: " << filename << std::endl;
    error = lodepng::decode (pixels, width, height, filename);
    if (error) {
        std::cout   
            << "Error: " << error 
            << " - " << lodepng_error_text (error) 
            << std::endl;
        return 0;
    }

    image = new unsigned char[height*width*4];
    for (unsigned int ii = 0; ii < height * width * 4; ii++) {
        image[ii] = pixels[ii];
    }
    return image;
}

void printString (int x, int y, const char* s)
{
    const int charWidth = 8;
    const int charHeight = 13;

    int xPos = x * (charWidth  + 2);
    int yPos = glutGet (GLUT_WINDOW_HEIGHT) - (y * (charHeight + 2));
    int len = strlen (s);

    glRasterPos2i (xPos, yPos);
    for (int ii = 0; ii < len; ii++) {
        glutBitmapCharacter (GLUT_BITMAP_8_BY_13, s[ii]);
    }
}

void drawImage (int x, int y, const unsigned char* image)
{
    int xPos = x;
    int yPos = glutGet (GLUT_WINDOW_HEIGHT) - y;
    glRasterPos2i (xPos, yPos);

    glDrawPixels (20, 20,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        image);
}

static void display (void)
{
    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->tick();
    l_engine->getScreen().redraw();
}

static void resize (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    Screen& l_screen = GameEngine::getEngine()->getScreen();
    l_screen.resize (w, h);
}

static void keyDown (unsigned char key, int x, int y)
{
    Screen& l_screen = GameEngine::getEngine()->getScreen();
    l_screen.keyDown (key);
}

static void keyUp (unsigned char key, int x, int y)
{
    Screen& l_screen = GameEngine::getEngine()->getScreen();
    l_screen.keyUp (key);
}

void setup_graphics ()
{
    Screen& l_screen = GameEngine::getEngine()->getScreen();

    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (l_screen.getWidth(), l_screen.getHeight());
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("FORTRESS");

    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glutReshapeFunc     (resize);
    glutKeyboardFunc    (keyDown);
    glutKeyboardUpFunc  (keyUp);
    glutDisplayFunc     (display);
    glutIdleFunc        (display);
}

void start_graphics ()
{
    glutMainLoop();
}
