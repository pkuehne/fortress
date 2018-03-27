#include "window.h"
#include "frame.h"
#include "../core/game_engine.h"
#include <iostream>

void Window::initialise(GameEngine *a_engine, void *args, void *retval)
{
    m_engine = a_engine;
    m_graphics = m_engine->getGraphics();
    m_state = m_engine->state();
    m_manager = m_engine->getWindows();
    m_args = args;
    m_retval = retval;
    m_baseWidget = createWidget<Frame>("frmBase", 0, 0)->setBorder(true);
}

void Window::setDimensions(int x, int y, int width, int height)
{
    m_xOffset = x;
    m_yOffset = y;
    m_width = width;
    m_height = height;

    m_baseWidget
        ->setWindowOffsets(m_xOffset, m_yOffset) // TODO: Remove
        ->setHeight(m_height)
        ->setWidth(m_width)
        ->realign(x, y, width, height);
}

unsigned int Window::drawString(int y, int x, const char *text, Color fg, Color bg)
{
    if (x < 0)
        x = (m_width / 2) - (strlen(text) / 2);
    return m_graphics->drawString(m_yOffset + y, m_xOffset + x, text, fg, bg);
}

unsigned int Window::drawCommandString(int y, int x, const char *text, int pos, bool active)
{
    char command[2] = {0};
    if (x < 0)
        x = (m_width / 2) - (strlen(text) / 2);
    Color fg = Color(WHITE);
    Color bg = Color(BLACK);
    Color cc = Color(GREEN);
    if (!active)
    {
        float factor = 0.5;
        fg *= factor;
        cc *= factor;
    }

    unsigned int retval = drawString(y, x, text, fg, bg);
    command[0] = text[pos];
    if (active)
    {
        retval += drawString(y, x + pos, command, cc, bg);
    }
    return retval;
}

void Window::drawTile(int y, int x, unsigned int tile, Color fg, Color bg)
{
    m_graphics->drawTile(m_yOffset + y, m_xOffset + x, tile, fg, bg);
}

void Window::drawBorder(int y, int x, int height, int width)
{
    m_graphics->drawBorder(m_yOffset + y, m_xOffset + x, height, width);
}

void Window::clearArea(int y, int x, int height, int width)
{
    m_graphics->clearArea(m_yOffset + y, m_xOffset + x, height, width);
}

void Window::beforeRedraw()
{
    m_graphics->clearArea(m_yOffset, m_xOffset, m_height, m_width);
}

void Window::renderWidgets()
{
    m_baseWidget->render();
}

void Window::afterRedraw()
{
}

void Window::destroy(void)
{
}

/// The "screen" dimensions have changed, reload them and re-apply depending on whether this window is fullscreen or not
void Window::resize()
{
    if (m_fullscreen)
    {
        setDimensions(0, 0, m_graphics->getScreenWidth(), m_graphics->getScreenHeight());
    }
    else
    {
        int x = 0;
        int y = 0;

        m_graphics->calculateWindowOffsetsFromCentre(m_height, m_width, y, x);
        m_xOffset = x;
        m_yOffset = y;
        setDimensions(x, y, m_width, m_height);
    }
}

void Window::mouseDown(int x, int y, int button)
{
    if (button < MAX_BUTTONS)
    {
        m_buttons[button] = true;
    }
}

void Window::mouseUp(int x, int y, int button)
{
    if (button < MAX_BUTTONS)
    {
        m_buttons[button] = false;
    }
}

bool Window::getMouseButton(int button)
{
    if (button < MAX_BUTTONS)
    {
        return m_buttons[button];
    }
    return false;
}

void Window::drawProgress(unsigned int x, unsigned int y, unsigned int value, unsigned int max)
{
    float l_value = (float)value;
    float l_max = (float)max;
    Color l_color((1.0f - (l_value / l_max)), l_value / l_max, 0);

    for (unsigned int xx = 0; xx < value; xx++)
    {
        drawTile(y, x + xx, 178, l_color, Color(BLACK));
    }
}

unsigned int Window::wrapText(const std::string &text, std::vector<std::string> &lines, unsigned int maxWidth, unsigned int maxRows)
{
    size_t wordStart = 0;
    size_t wordEnd = 0;
    unsigned int lineNum = 0;
    lines.resize(maxRows);

    while (wordEnd != std::string::npos)
    {
        wordEnd = text.find(' ', wordStart);
        std::string word(text.substr(wordStart, wordEnd - wordStart));
        if (lines[lineNum].length() + word.length() + 3 /*...*/ + 2 /*spaces*/ > maxWidth && lineNum + 1 >= maxRows)
        {
            lines[lineNum].append("...");
            return lineNum;
        }
        if (lines[lineNum].length() + word.length() + 1 > maxWidth)
        {
            if (lineNum + 1 >= maxRows)
            {
                lines[lineNum].append("...");
                return lineNum;
            }
            // Start the next line
            lineNum++;
        }
        lines[lineNum].append(word);
        lines[lineNum].append(" ");
        wordStart = wordEnd + 1;
    }

    return lineNum;
}

void Window::keyDown(unsigned char key)
{
    ascii_keys[key] = true;

    if (m_onEscape != EscapeBehaviour::None && key == KEY_ESC)
    {
        if (m_onEscape == EscapeBehaviour::CloseWindow)
        {
            getEngine()->getWindows()->popWindow();
        }
        if (m_onEscape == EscapeBehaviour::QuitGame)
        {
            std::cout << "Quitting" << std::endl;
            getEngine()->quit();
        }
        return;
    }

    m_baseWidget->keyPress(key);
    this->keyPress(key);
}

void Window::setFullscreen(bool fullscreen)
{
    m_fullscreen = fullscreen;
    setDimensions(0, 0, m_graphics->getScreenWidth(), m_graphics->getScreenHeight());
}

void Window::setTitle(const std::string &title)
{
    dynamic_cast<Frame*>(m_baseWidget)->setTitle(title);
}
