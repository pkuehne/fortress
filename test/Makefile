CC=g++
CFLAGS=-c -g -Wall -I. -I/usr/include -I../src/
LDFLAGS= 
LIBRARIES=-lGL -lGLU -lglut -lc -lm -lSOIL -lgtest -lgmock -lpthread
SOURCES=$(wildcard *.cpp)
SOURCES+= \
../src/algorithm.cpp \
../src/component_manager.cpp \
../src/event.cpp \
../src/generator.cpp \
../src/map_window.cpp \
../src/sprite_system.cpp \
../src/base_system.cpp \
../src/entity.cpp \
../src/event_manager.cpp \
../src/graphics.cpp \
../src/movement_system.cpp \
../src/window.cpp \
../src/color.cpp \
../src/entity_manager.cpp \
../src/gameengine.cpp \
../src/splash_window.cpp \
../src/window_manager.cpp \

OBJECTS=$(SOURCES:.cpp=.o) 
EXECUTABLE=unit_test

all: $(SOURCES) $(EXECUTABLE)

clean: 
	@rm $(OBJECTS) $(EXECUTABLE) ||:

test:
	make all
	./unit_test
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
