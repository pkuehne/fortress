#include "generator_window.h"
#include "../core/game_engine.h"
#include "../generators/dungeon_generator.h"
#include "../generators/rural_generator.h"
#include "map_window.h"
#include "../components/stair_component.h"
#include "label.h"
#include "numeric_entry.h"
#include <sstream>
#include <glog/logging.h>

void updateNumericEntrySensitivity(GeneratorWindow *win, std::string numName)
{
    auto setSensitive = [](NumericEntry* l, std::string name) {
        l->setSensitive(l->getName() == name);
    };

    setSensitive(win->getWidget<NumericEntry>("numWidth"), numName);
    setSensitive(win->getWidget<NumericEntry>("numHeight"), numName);
    setSensitive(win->getWidget<NumericEntry>("numDepth"), numName);
    setSensitive(win->getWidget<NumericEntry>("numRooms"), numName);
}

void GeneratorWindow::setup()
{
    m_worldSize = 129;
    m_selectedPosition = WIDTH;
    m_status = WAITING;

    setTitle(" Create New World ");
    setFullscreen(true);
    setEscapeBehaviour(Window::EscapeBehaviour::CloseWindow);
}

void GeneratorWindow::registerWidgets()
{
    createWidget<Label>("lblParameters", 1, 11)
        ->setText("Level Parameters:")
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblWidth", 1, 10)
        ->setText("Width:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label *l) {
            updateNumericEntrySensitivity(dynamic_cast<GeneratorWindow *>(l->getWindow()), "numWidth");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblHeight", 1, 9)
        ->setText("Height:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label *l) {
            updateNumericEntrySensitivity(dynamic_cast<GeneratorWindow *>(l->getWindow()), "numHeight");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblRooms", 1, 8)
        ->setText("Rooms:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label *l) {
            updateNumericEntrySensitivity(dynamic_cast<GeneratorWindow *>(l->getWindow()), "numRooms");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblDepth", 1, 7)
        ->setText("Depth:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label *l) {
            updateNumericEntrySensitivity(dynamic_cast<GeneratorWindow *>(l->getWindow()), "numDepth");
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblCreate", 1, 6)
        ->setText("Create:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label *l) {
            GeneratorWindow *win = dynamic_cast<GeneratorWindow *>(l->getWindow());
            win->startGenerating();
        })
        ->setVerticalAlign(Widget::VerticalAlign::Bottom);
    createWidget<Label>("lblPlay", 1, 5)
        ->setText("Play:")
        ->setCommandChar(1)
        ->setIgnoreCommandCharCase(true)
        ->setCommandCharCallback([](Label *l) {
            GeneratorWindow *win = dynamic_cast<GeneratorWindow *>(l->getWindow());
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
}

void GeneratorWindow::update()
{
    if (getArgs() && m_status == WAITING)
    {
        startGenerating();
        startPlaying();
        return;
    }
}

void GeneratorWindow::startGenerating()
{
    m_progress = 1;
    m_status = PROGRESS;
    unsigned int l_levelWidth = getWidget<NumericEntry>("numWidth")->getNumber();
    unsigned int l_levelHeight = getWidget<NumericEntry>("numHeight")->getNumber();
    unsigned int l_levelRooms = getWidget<NumericEntry>("numRooms")->getNumber();
    unsigned int l_levelDepth = getWidget<NumericEntry>("numDepth")->getNumber();

    unsigned int startArea = getEngine()->state()->map()->createArea(
        l_levelWidth,
        l_levelHeight,
        1);

    RuralGenerator rural;
    rural.initialise(getEngine());
    rural.mapHeight() = l_levelHeight;
    rural.mapWidth() = l_levelWidth;
    rural.area() = startArea;
    rural.generate();

    for (EntityId stair : rural.getAreaLinks())
    {
        int retries = 0;
        bool success = false;
        unsigned int area =
            getEngine()->state()->map()->createArea(l_levelWidth,
                                                    l_levelHeight,
                                                    l_levelDepth);

        LOG(INFO) << "Generating area: " << area << std::endl;
        DungeonGenerator l_generator;
        l_generator.initialise(getEngine());
        l_generator.maxDepth() = l_levelDepth;
        l_generator.mapHeight() = l_levelHeight;
        l_generator.mapWidth() = l_levelWidth;
        l_generator.area() = area;
        l_generator.numberOfRooms() = l_levelRooms;
        l_generator.downStairTarget() = 0;
        l_generator.upStairTarget() = stair;
        if (area == 2)
        {
            l_generator.createBoss() = true;
        }
        do
        {
            success = l_generator.generate();
        } while (!success && retries++ < 20);
        if (!success)
        {
            LOG(ERROR) << "Failed to generate a valid map" << std::endl;
        }
        getEngine()->state()->components()->get<StairComponent>(stair)->target =
            l_generator.upStairLink();
    }
    LOG(INFO) << "Placed "
              << getEngine()->state()->entityManager()->getMaxId()
              << " entities!"
              << std::endl;

    getEngine()->state()->map()->setArea(startArea);
    m_status = COMPLETED;
    getWidget<Label>("lblPlay")->setSensitive(true);
}

void GeneratorWindow::generateLevel()
{
}

void GeneratorWindow::startPlaying()
{
    MapWindow *l_win = new MapWindow();
    l_win->initialise(getEngine());
    getEngine()->getWindows()->replaceAllWindows(l_win);
}
