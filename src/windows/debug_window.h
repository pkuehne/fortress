#ifndef __DEBUG_WINDOW_H__
#define __DEBUG_WINDOW_H__

#include "window.h"
#include "utility.h"

struct Output {
    std::string text;
    Color color;
};

const Color COMMAND_COLOR = Color (WHITE);
const Color ERROR_COLOR = Color (RED);
const Color OUTPUT_COLOR = Color (GREY);

const unsigned int COMMAND_MAX_LEN = 128;
class DebugWindow : public Window {
public:
    void gainFocus();
    void resize();
    void redraw();
    void keyDown (unsigned char key);
private:
    char command[COMMAND_MAX_LEN] = {0};
    int length;
    std::vector<Output> history;
};

#endif
