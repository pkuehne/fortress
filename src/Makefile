.PHONY: all clean build run
CC=g++
CFLAGS=-c -g -rdynamic -Wall -Werror -I. -I/usr/include -std=c++11
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
