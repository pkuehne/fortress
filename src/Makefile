CC=g++
CFLAGS=-c -g -Wall -I. -I/usr/include 
LDFLAGS= 
LIBRARIES=-lpthread -lGL -lGLU -lglut -lc -lm
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=fortress

all: $(SOURCES) $(EXECUTABLE)

clean: 
	@rm $(OBJECTS) $(EXECUTABLE) ||:

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBRARIES) -o $@

%.o : %.cpp 
	$(CC) $(CFLAGS) $< -o $@
