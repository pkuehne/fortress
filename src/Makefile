.PHONY: all clean build run
CC=g++
CFLAGS=-g -rdynamic -Wall -Werror -I. -I/usr/include -std=c++11
LDFLAGS= -g -rdynamic
LIBRARIES=-lpthread -lGL -lGLU -lglut -lc -lm -lSOIL
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
DEPENDENCIES=$(SOURCES:.cpp=.d)
GCNO=$(SOURCES:.cpp=.gcno)
GCDA=$(SOURCES:.cpp=.gcda)
EXECUTABLE=fortress

all: $(SOURCES) $(EXECUTABLE)

run:
	./fortress
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(DEPENDENCIES) $(GCNO) $(GCDA) ||:

build: $(EXECUTABLE)

-include $(DEPENDENCIES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@
	$(CC) -MM $(CFLAGS) $< -o $*.d
