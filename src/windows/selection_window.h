#ifndef SELECTION_WINDOW_H
#define SELECTION_WINDOW_H

#include "window.h"
#include "../core/entity.h"

class SelectionWindow : public Window {
    public:
        virtual void setup();
        virtual void registerWidgets();

        void setEntities(EntityHolder* entities);
        std::vector<EntityId>& getEntities() { return m_entities; }

    private:
        std::vector<std::string>    m_lines;
        std::vector<EntityId>       m_entities;
        unsigned int                m_selection = 0;
};

#endif
