#pragma once

#include "../core/entity.h"
#include "window.h"

class InspectionWindow : public Window {
public:
    explicit InspectionWindow(EntityId entity) : m_entity(entity) {}
    void setup() override;
    void registerWidgets() override;

private:
    EntityId m_entity;
};
