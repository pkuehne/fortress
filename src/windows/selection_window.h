#ifndef SELECTION_WINDOW_H
#define SELECTION_WINDOW_H

#include "../core/entity.h"
#include "window.h"
#include <memory>

class GameEngine;

typedef struct {
    EntityHolder entities;
    std::function<void(GameEngine*, EntityId)> selectionCallback;
} SelectionWindowArgs;

class SelectionWindow : public Window {
public:
    virtual void setup();
    virtual void registerWidgets();

    void setArguments(std::shared_ptr<SelectionWindowArgs> args) {
        m_arguments = args;
    }

    void setEntities(EntityHolder& entities);
    std::vector<EntityId>& getEntities() { return m_entities; }

private:
    std::vector<std::string> m_lines;
    std::vector<EntityId> m_entities;
    std::shared_ptr<SelectionWindowArgs> m_arguments;
    unsigned int m_selection = 0;
};

#endif
