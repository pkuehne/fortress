#pragma once

#include "../core/entity.h"
#include "window.h"

class InspectionWindow : public Window {
public:
    explicit InspectionWindow(EntityId entity) : m_entity(entity) {}
    void setup();
    void registerWidgets();

private:
    EntityId m_entity;
};
