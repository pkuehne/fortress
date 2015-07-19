#include <gameengine.h>
#include <graphics_mock.h>
#include <gtest/gtest.h>
#include "entity_manager_mock.h"
#include "event_manager_mock.h"
#include "window_manager_mock.h"
#include "window_mock.h"
#include "base_system_mock.h"
#include "generator_mock.h"

using namespace ::testing;

TEST (GameEngine, SetGetGraphics)
{
    GraphicsMock    l_graphics;
    GameEngine      l_engine (&l_graphics);
    EXPECT_EQ (&l_graphics, l_engine.getGraphics());
}

TEST (GameEngine, tick)
{
    GraphicsMock    l_graphics;
    GameEngine      l_engine (&l_graphics);

    EntityManagerMock   l_entities;
    EventManagerMock    l_events;
    WindowManagerMock   l_windows;
    BaseSystemMock      l_moveSystem;
    BaseSystemMock      l_spriteSystem;
    BaseSystemMock      l_combatSystem;
    WindowMock          l_window;
    GeneratorMock       l_generator;

    l_engine.setEntityManager (&l_entities);
    l_engine.setEventManager (&l_events);
    l_engine.setWindowManager (&l_windows);
    l_engine.setMoveSystem (&l_moveSystem);
    l_engine.setSpriteSystem (&l_spriteSystem);
    l_engine.setCombatSystem (&l_combatSystem);
    l_engine.setGenerator (&l_generator);

    EXPECT_CALL (l_entities, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_events, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_windows, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_moveSystem, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_combatSystem, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_spriteSystem, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_generator, initialise(Eq(&l_engine))).Times(1);

    EXPECT_CALL (l_events, registerHandler(Eq(&l_moveSystem))).Times(1);
    EXPECT_CALL (l_events, registerHandler(Eq(&l_spriteSystem))).Times(1);
    EXPECT_CALL (l_events, registerHandler(Eq(&l_combatSystem))).Times(1);

    KeyboardFuncPtr keyboardFunc;
    KeyboardFuncPtr keyboardUpFunc;
    DisplayFuncPtr  displayFunc;
    MouseFuncPtr    mouseFunc;

    EXPECT_CALL (l_graphics, setKeyboardFunc(_)).Times(1).WillOnce (SaveArg<0>(&keyboardFunc));
    EXPECT_CALL (l_graphics, setKeyboardUpFunc(_)).Times(1).WillOnce (SaveArg<0>(&keyboardUpFunc));
    EXPECT_CALL (l_graphics, setDisplayFunc(_)).Times(1).WillOnce (SaveArg<0>(&displayFunc));
    EXPECT_CALL (l_graphics, setMouseFunc(_)).Times(1).WillOnce (SaveArg<0>(&mouseFunc));

    l_engine.initialise();

    EXPECT_CALL (l_events, processEvents()).Times(1);
    EXPECT_CALL (l_moveSystem, update()).Times(1);
    EXPECT_CALL (l_spriteSystem, update()).Times(1);
    EXPECT_CALL (l_combatSystem, update()).Times(1);

    EXPECT_CALL (l_windows, getActive()).WillRepeatedly (Return (&l_window));
    EXPECT_CALL (l_window, beforeRedraw()).Times(1);
    EXPECT_CALL (l_window, redraw()).Times(1);
    EXPECT_CALL (l_window, afterRedraw()).Times(1);

    EXPECT_EQ (0, l_engine.getTick());
    l_engine.tick();
    EXPECT_EQ (1, l_engine.getTick());
}

TEST (GameEngine, raiseEventCallsEventManager)
{
    GraphicsMock    l_graphics;
    GameEngine      l_engine (&l_graphics);

    EventManagerMock    l_events;
    l_engine.setEventManager (&l_events);

    Event l_event (EVENT_INVALID);
    EXPECT_CALL (l_events, raiseEvent(Eq(&l_event))).Times(1);

    l_engine.raiseEvent (&l_event);
}

TEST (GameEngine, getEntitiesReturnsEntityManager)
{
    GraphicsMock    l_graphics;
    GameEngine      l_engine (&l_graphics);

    EntityManagerMock    l_entities;
    l_engine.setEntityManager (&l_entities);

    EXPECT_EQ (&l_entities, l_engine.getEntities());
}

TEST (GameEngine, graphicsFuncPointersCallWindow)
{
    GraphicsMock    l_graphics;
    GameEngine      l_engine (&l_graphics);

    EntityManagerMock   l_entities;
    EventManagerMock    l_events;
    WindowManagerMock   l_windows;
    BaseSystemMock      l_moveSystem;
    BaseSystemMock      l_spriteSystem;
    BaseSystemMock      l_combatSystem;
    WindowMock          l_window;

    l_engine.setEntityManager (&l_entities);
    l_engine.setEventManager (&l_events);
    l_engine.setWindowManager (&l_windows);
    l_engine.setMoveSystem (&l_moveSystem);
    l_engine.setSpriteSystem (&l_spriteSystem);
    l_engine.setCombatSystem (&l_combatSystem);

    EXPECT_CALL (l_entities, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_events, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_windows, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_moveSystem, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_combatSystem, initialise(Eq(&l_engine))).Times(1);
    EXPECT_CALL (l_spriteSystem, initialise(Eq(&l_engine))).Times(1);

    EXPECT_CALL (l_events, registerHandler(Eq(&l_moveSystem))).Times(1);
    EXPECT_CALL (l_events, registerHandler(Eq(&l_spriteSystem))).Times(1);
    EXPECT_CALL (l_events, registerHandler(Eq(&l_combatSystem))).Times(1);

    KeyboardFuncPtr keyboardFunc;
    KeyboardFuncPtr keyboardUpFunc;
    DisplayFuncPtr  displayFunc;
    MouseFuncPtr    mouseFunc;

    EXPECT_CALL (l_graphics, setKeyboardFunc(_)).Times(1).WillOnce (SaveArg<0>(&keyboardFunc));
    EXPECT_CALL (l_graphics, setKeyboardUpFunc(_)).Times(1).WillOnce (SaveArg<0>(&keyboardUpFunc));
    EXPECT_CALL (l_graphics, setDisplayFunc(_)).Times(1).WillOnce (SaveArg<0>(&displayFunc));
    EXPECT_CALL (l_graphics, setMouseFunc(_)).Times(1).WillOnce (SaveArg<0>(&mouseFunc));

    l_engine.initialise();

    EXPECT_CALL (l_windows, getActive()).WillRepeatedly (Return (&l_window));

    EXPECT_CALL (l_window, keyDown (Eq('a'))).Times(1);
    keyboardFunc ('a', 1, 1);

    EXPECT_CALL (l_window, keyUp (Eq('a'))).Times(1);
    keyboardUpFunc ('a', 1, 1);

    EXPECT_CALL (l_window, mouseDown (Eq (1), Eq(1), Eq(1))).Times(1);
    mouseFunc (1, 0, 1, 1);

    EXPECT_CALL (l_window, mouseUp (Eq (1), Eq(1), Eq(1))).Times(1);
    mouseFunc (1, 1, 1, 1);

}

TEST (GameEngine, generator)
{
    GraphicsMock    l_graphics;
    GameEngine      l_engine (&l_graphics);

    GeneratorMock   l_generator;
    l_engine.setGenerator (&l_generator);

    unsigned int l_height;
    unsigned int l_width;
    unsigned int l_rooms;

    EXPECT_CALL (l_generator, mapHeight()).WillOnce (ReturnRef (l_height));
    EXPECT_CALL (l_generator, mapWidth()).WillOnce (ReturnRef (l_width));
    EXPECT_CALL (l_generator, numberOfRooms()).WillOnce (ReturnRef (l_rooms));

    EXPECT_CALL (l_generator, generate()).Times(1);
    l_engine.loadMap ("");

}
