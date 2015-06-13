CC=g++
CFLAGS=-c -g -Wall -I. -I/usr/include -I../src/
LDFLAGS= 
LIBRARIES=-lGL -lGLU -lglut -lc -lm -lSOIL -lgtest -lgmock -lpthread
SOURCES=$(wildcard *.cpp)
SOURCES+= \
../src/color.cpp \

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
