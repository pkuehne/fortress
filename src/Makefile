.PHONY: all clean build run
CC=g++
CFLAGS=-g -rdynamic -Wall -Werror -I. -I/usr/include -std=c++11
LDFLAGS= -g -rdynamic
LIBRARIES=-lGL -lGLU -lglut -lglfw -lc -lm -lSOIL -lpthread 
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPENDENCIES=$(SOURCES:.cpp=.d)
GCNO=$(SOURCES:.cpp=.gcno)
GCDA=$(SOURCES:.cpp=.gcda)
EXECUTABLE=../fortress
BUILD=

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DEPENDENCIES) $(GCNO) $(GCDA) ||:

build: $(EXECUTABLE) $(BUILD)

$(BUILD):
	mkdir $(BUILD) ||:

-include $(DEPENDENCIES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $(BUILD)$@
	$(CC) -MM $(CFLAGS) $< -o $(BUILD)$*.d
