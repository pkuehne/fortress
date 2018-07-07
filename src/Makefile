.PHONY: all clean build run lint
CC=g++
MODULES = $(sort $(dir $(wildcard ../src/*/)))
OUT_DIR = ..
PROGRAM = $(OUT_DIR)/fortress
ART_DIR = $(OUT_DIR)/artifacts
OBJ_DIR = $(ART_DIR)/objects
DEP_DIR = $(ART_DIR)/depends
COV_DIR = $(ART_DIR)/coverage
ALL_DIR = $(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR)

INC_DIRS += -I. -I/usr/include/ $(addprefix -I, $(MODULES))
CFLAGS=-g -rdynamic -Wall -Werror -pedantic -std=c++14 $(INC_DIRS)
LDFLAGS= -g -rdynamic
GLFW_LIBS=$(shell pkg-config glfw3 --libs --static)
YAML_LIBS=$(shell pkg-config yaml-cpp --libs --static)
LUA_LIBS=$(shell pkg-config lua5.3 --libs --static)
SOIL_LIBS=-lSOIL
GLOG_LIBS=-lglog
EXPERIMENTAL=-lstdc++fs
OTHER=-lGL -lc -lm
LIBRARIES=$(GLFW_LIBS) $(YAML_LIBS) $(LUA_LIBS) $(SOIL_LIBS) $(GLOG_LIBS) $(EXPERIMENTAL) $(OTHER) 

SOURCES = $(foreach sdir, $(MODULES), $(wildcard $(sdir)/*.cpp))
#SOURCES+=main.cpp
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.o)))
DEPENDS = $(addprefix $(DEP_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.d)))

vpath %.cpp $(MODULES)

all: $(SOURCES) $(PROGRAM)

clean:
	@rm -fr $(ART_DIR)
	@rm -fr $(PROGRAM)
	@echo "Build Cleanup completed"

lint:
	cppcheck . --enable=all 2>lint-errors.txt

build: $(PROGRAM)

-include $(DEPENDS)

$(PROGRAM): $(ALL_DIR) $(OBJECTS)
	@echo "Linking $(notdir $@)"
	@$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

$(OBJ_DIR)/main.o: main.cpp
	@echo "Overriding main"
	@$(CC) -c  $(CFLAGS) main.cpp -o $@

$(OBJ_DIR)/%.o: %.cpp 
	@echo "Building $(notdir $<)"
	@$(CC) -c  $(CFLAGS) $< -o $@
	@$(CC) -MM $(CFLAGS) $< -MT $@ -MF $(DEP_DIR)/$*.d

$(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR):
	@mkdir -p $@
	@echo "Creating directory $@"
