#pragma once

#include "../components/description_component.h"
#include "../components/openable_component.h"
#include "window.h"

typedef struct {
    EntityId entity;
} InteractionWindowArgs;

class InteractionWindow : public Window {
public:
    void setArguments(std::shared_ptr<InteractionWindowArgs> args) {
        m_arguments = args;
    }
    void setup();
    void registerWidgets();
    void nextTurn();

private:
    std::shared_ptr<InteractionWindowArgs> m_arguments;
    DescriptionComponent* m_desc;
    OpenableComponent* m_open;
};
