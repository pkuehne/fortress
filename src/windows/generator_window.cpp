#include "generator_window.h"
#include "../components/connector_component.h"
#include "../core/game_engine.h"
#include "../generators/dungeon_generator.h"
#include "../generators/rural_generator.h"
#include "../widgets/label.h"
#include "../widgets/numeric_entry.h"
#include "map_window.h"
#include <glog/logging.h>
#include <sstream>

void updateNumericEntrySensitivity(GeneratorWindow* win, std::string numName) {
    auto setSensitive = [](NumericEntry* l, std::string name) {
        l->setSensitive(l->getName() == name);
    };

    setSensitive(win->getWidget<NumericEntry>("numWidth"), numName);
    setSensitive(win->getWidget<NumericEntry>("numHeight"), numName);
    setSensitive(win->getWidget<NumericEntry>("numDepth"), numName);
    setSensitive(win->getWidget<NumericEntry>("numRooms"), numName);
}

void GeneratorWindow::setup() {
    m_worldSize = 129;
    m_selectedPosition = WIDTH;
    m_status = WAITING;

    setTitle(" Create New World ");
    setFullscreen();
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void GeneratorWindow::registerWidgets() {
    createWidget<Label>("lblParameters", 1, 11)
        ->setText("Level Parameters:")
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblWidth", 1, 10)
        ->setText("Width:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label* l) {
            updateNumericEntrySensitivity(
                dynamic_cast<GeneratorWindow*>(l->getWindow()), "numWidth");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblHeight", 1, 9)
        ->setText("Height:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label* l) {
            updateNumericEntrySensitivity(
                dynamic_cast<GeneratorWindow*>(l->getWindow()), "numHeight");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblRooms", 1, 8)
        ->setText("Rooms:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label* l) {
            updateNumericEntrySensitivity(
                dynamic_cast<GeneratorWindow*>(l->getWindow()), "numRooms");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblDepth", 1, 7)
        ->setText("Depth:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label* l) {
            updateNumericEntrySensitivity(
                dynamic_cast<GeneratorWindow*>(l->getWindow()), "numDepth");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblCreate", 1, 6)
        ->setText("Create:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label* l) {
            GeneratorWindow* win =
                dynamic_cast<GeneratorWindow*>(l->getWindow());
            win->startGenerating();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblPlay", 1, 5)
        ->setText("Play:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label* l) {
            GeneratorWindow* win =
                dynamic_cast<GeneratorWindow*>(l->getWindow());
            win->startPlaying();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setSensitive(false);

    createWidget<NumericEntry>("numWidth", 9, 10)
        ->setNumber(30)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<NumericEntry>("numHeight", 9, 9)
        ->setNumber(30)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setSensitive(false);
    createWidget<NumericEntry>("numRooms", 9, 8)
        ->setNumber(2)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setSensitive(false);
    createWidget<NumericEntry>("numDepth", 9, 7)
        ->setNumber(2)
        ->setVerticalAlign(Widget::VerticalAlign::Bottom)
        ->setSensitive(false);

    if (m_hideWindow) {
        this->startGenerating();
        events()->subscribe<MapGeneratedEvent>(
            [this](auto event) { this->startPlaying(); });
    } else {
        events()->subscribe<MapGeneratedEvent>([this](auto event) {
            this->m_status = COMPLETED;
            this->getWidget<Label>("lblPlay")->setSensitive(true);
        });
    }
}

void GeneratorWindow::startGenerating() {
    m_progress = 1;
    m_status = PROGRESS;

    events()->raise(std::make_shared<GenerateRuralMapEvent>(
        getWidget<NumericEntry>("numWidth")->getNumber(),
        getWidget<NumericEntry>("numHeight")->getNumber(),
        getWidget<NumericEntry>("numDepth")->getNumber(),
        getWidget<NumericEntry>("numRooms")->getNumber()));
}

void GeneratorWindow::startPlaying() {
    events()->raise(std::make_shared<RegisterWindowEvent>(
        std::make_shared<MapWindow>(),
        RegisterWindowEvent::WindowAction::Replace));
}
