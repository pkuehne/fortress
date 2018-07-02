#pragma once

#include "window.h"

typedef struct {
    EntityId entity;
} InspectionWindowArgs;

class InspectionWindow : public Window {
public:
    void setArguments(std::shared_ptr<InspectionWindowArgs> args) {
        m_arguments = args;
    }
    void setup();
    void registerWidgets();

private:
    std::shared_ptr<InspectionWindowArgs> m_arguments;
};
