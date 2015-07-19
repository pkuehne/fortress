.PHONY: all clean test shuffle
CC=g++
CFLAGS=-c -g -Wall -I. -I/usr/include -I../src/ -fprofile-arcs -ftest-coverage
LDFLAGS=
LIBRARIES=-lGL -lGLU -lglut -lc -lm -lSOIL -lgtest -lgmock -lpthread -lgcov
SOURCES=$(wildcard *.cpp)
SOURCES+= \
../src/algorithm.cpp \
../src/color.cpp \
../src/combat_system.cpp \
../src/component_manager.cpp \
../src/entity.cpp \
../src/entity_manager.cpp \
../src/event.cpp \
../src/event_manager.cpp \
../src/gameengine.cpp \
../src/game_system_base.cpp \
../src/generator.cpp \
../src/graphics.cpp \
../src/map_window.cpp \
../src/movement_system.cpp \
../src/npc_system.cpp \
../src/splash_window.cpp \
../src/sprite_system.cpp \
../src/window.cpp \
../src/window_manager.cpp \

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=unit_test

all: $(SOURCES) $(EXECUTABLE)

clean:
	@rm -f $(OBJECTS) $(EXECUTABLE) ||:

test:
	$(MAKE) all
	./unit_test --gtest_shuffle

shuffle:
	./unit_test --gtest_repeat=100 --gtest_shuffle

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
