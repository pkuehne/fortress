#include "window.h"
#include "../core/component_manager.h"
#include "../core/entity_manager.h"
#include "../core/event_manager.h"
#include "../core/graphics_interface.h"
#include "../core/map_manager.h"
#include "../widgets/frame.h"
#include <iostream>

void Window::initialise(std::shared_ptr<GraphicsInterface> graphics,
                        std::shared_ptr<EventManager> events,
                        std::shared_ptr<ComponentManager> components,
                        std::shared_ptr<EntityManager> entities,
                        std::shared_ptr<MapManager> map) {
    m_graphics = graphics;
    m_events = events;
    m_components = components;
    m_entities = entities;
    m_map = map;
    m_baseWidget = createWidget<Frame>("frmBase", 0, 0)->setBorder(true);
}

void Window::setDimensions(int x, int y, int width, int height) {
    m_xOffset = x;
    m_yOffset = y;
    m_width = width;
    m_height = height;

    m_baseWidget->setHeight(m_height)->setWidth(m_width)->realign(x, y, width,
                                                                  height);
}

void Window::beforeRedraw() {
    m_graphics->clearArea(m_yOffset, m_xOffset, m_height, m_width);
}

void Window::renderWidgets() { m_baseWidget->render(); }

void Window::afterRedraw() {}

void Window::destroy(void) {}

/// The "screen" dimensions have changed, reload them and re-apply depending on
/// whether this window is fullscreen or not
void Window::resize() {
    if (m_fullscreen) {
        setDimensions(0, 0, m_graphics->getScreenWidth(),
                      m_graphics->getScreenHeight());
    } else {
        int x = 0;
        int y = 0;

        m_graphics->calculateWindowOffsetsFromCentre(m_height, m_width, y, x);
        m_xOffset = x;
        m_yOffset = y;
        setDimensions(x, y, m_width, m_height);
    }
}

void Window::mouseDown(int x, int y, int button) {
    if (button < MAX_BUTTONS) {
        m_buttons[button] = true;
    }
}

void Window::mouseUp(int x, int y, int button) {
    if (button < MAX_BUTTONS) {
        m_buttons[button] = false;
    }
}

void Window::keyDown(unsigned char key) {
    if (m_onEscape != EscapeBehaviour::None && key == KEY_ESC) {
        if (m_onEscape == EscapeBehaviour::CloseWindow) {
            events()->raise(std::make_shared<CloseWindowEvent>());
        }
        if (m_onEscape == EscapeBehaviour::QuitGame) {
            events()->raise(std::make_shared<QuitEvent>());
        }
        return;
    }

    m_baseWidget->keyPress(key);
    this->keyPress(key);
}

void Window::setFullscreen(bool fullscreen) {
    m_fullscreen = fullscreen;
    setDimensions(0, 0, m_graphics->getScreenWidth(),
                  m_graphics->getScreenHeight());
}

void Window::setTitle(const std::string& title) {
    dynamic_cast<Frame*>(m_baseWidget)->setTitle(title);
}
