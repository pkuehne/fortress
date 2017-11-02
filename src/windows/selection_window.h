#ifndef SELECTION_WINDOW_H
#define SELECTION_WINDOW_H

#include "window.h"
#include "entity.h"

class SelectionWindow : public Window {
    public:
        virtual void gainFocus ();
        virtual void resize();
        virtual void redraw();
        virtual void keyDown (unsigned char key);

    private:
        std::vector<std::string>    m_lines;
        std::vector<EntityId>       m_entities;
        unsigned int                m_selection = 0;
};

#endif
