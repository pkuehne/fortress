#pragma once

#include "window.h"

class InspectionWindow : public Window {
public:
    InspectionWindow(EntityId entity) : m_entity(entity) {}
    void setup();
    void registerWidgets();

private:
    EntityId m_entity;
};
