CC=g++
CFLAGS=-c -g -Wall -I. -I/usr/include 
LDFLAGS= 
LIBRARIES=-lpthread -lGL -lGLU -lglut -lc -lm -lSOIL
SOURCES=$(wildcard *.cpp) lodepng/lodepng.cpp 
OBJECTS=$(SOURCES:.cpp=.o) cJSON/cJSON.o
EXECUTABLE=fortress

all: $(SOURCES) $(EXECUTABLE)

clean: 
	@rm $(OBJECTS) $(EXECUTABLE) ||:

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
