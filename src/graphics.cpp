#include "graphics.h"
#include "gameengine.h"
#include "window.h"
#include "event.h"
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include <iostream>
#include <lodepng/lodepng.h>

static GLuint tex;

unsigned char* loadImage (const char* filename, unsigned int& width, unsigned int& height)
{
    std::vector<unsigned char> pixels;
    unsigned char* image = 0;
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

static void display (void)
{
    GameEngine* l_engine = GameEngine::getEngine();
    l_engine->tick();
    l_engine->getCurrentWindow()->beforeRedraw();
    l_engine->getCurrentWindow()->redraw();
    l_engine->getCurrentWindow()->afterRedraw();

    //l_engine->getScreen().redraw();
}

static void resize (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho (0, w, 0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    //l_screen.resize (w, h);
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
        //l_screen.mouseUp (x, y, button);
    } else {
        l_engine->getCurrentWindow()->mouseDown (x, y, button);
        //l_screen.mouseDown (x, y, button);
    }
}

void setup_graphics ()
{
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA);
    //glutInitWindowSize (l_screen.getWidth(), l_screen.getHeight());
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("FORTRESS");

    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (0.0, 0.0, 0.0, 0.0);

    glEnable (GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutReshapeFunc     (resize);
    glutKeyboardFunc    (keyDown);
    glutKeyboardUpFunc  (keyUp);
    glutMouseFunc       (mouseClick);
    glutDisplayFunc     (display);
    glutIdleFunc        (display);

    unsigned int width = 0;
    unsigned int height = 0;
    unsigned char* pixels = loadImage ("12x12.png", width, height);
    //unsigned char* pixels = loadImage ("../images/rendered/un-warrior.png", width, height);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    std::cout << "width: " << width << " height: " << height << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    delete pixels;
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
