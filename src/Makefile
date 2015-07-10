.PHONY: all clean build run
CC=g++
CFLAGS=-c -g -rdynamic -Wall -I. -I/usr/include
LDFLAGS= -g -rdynamic
LIBRARIES=-lpthread -lGL -lGLU -lglut -lc -lm -lSOIL
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=fortress

all: $(SOURCES) $(EXECUTABLE)

run:
	./fortress
clean:
	@rm -f $(OBJECTS) $(EXECUTABLE) ||:

build: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
