.PHONY: all clean build run 
CC=g++
MODULES = $(filter-out ../src/, $(sort $(dir $(wildcard ../src/*/))))
OUT_DIR = ..
PROGRAM = $(OUT_DIR)/unit_tests
ART_DIR = $(OUT_DIR)/artifacts
OBJ_DIR = $(ART_DIR)/objects
DEP_DIR = $(ART_DIR)/depends
COV_DIR = $(ART_DIR)/coverage
ALL_DIR = $(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR)
TEST_DIR = ./tests/
MOCK_DIR = ./mocks/

INC_DIRS += -I. -I/usr/include/ -I$(TEST_DIR) -I$(MOCK_DIR) $(addprefix -I, $(MODULES))
CFLAGS=-g -rdynamic -Wall -Werror -std=c++11 $(INC_DIRS)
LDFLAGS= -g -rdynamic 
GLFW_LIBS=$(shell pkg-config glfw3 --libs --static)
YAML_LIBS=$(shell pkg-config yaml-cpp --libs --static)
LUA_LIBS=$(shell pkg-config lua5.2 --libs --static)
GTEST_LIBS=$(shell pkg-config gtest --libs --static)
GMOCK_LIBS=$(shell pkg-config gmock --libs --static)
LIBRARIES=$(GLFW_LIBS) $(YAML_LIBS) $(LUA_LIBS) $(GMOCK_LIBS) $(GTEST_LIBS)
LIBRARIES+=-lGL -lc -lm -lSOIL -lpthread -lglog 

SOURCES = $(foreach sdir, $(MODULES), $(wildcard $(sdir)/*.cpp))
SOURCES+= $(wildcard *.cpp)
SOURCES+= $(wildcard $(TEST_DIR)/*.cpp)
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.o)))
DEPENDS = $(addprefix $(DEP_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.d)))

vpath %.cpp $(MODULES) $(TEST_DIR)

all: $(SOURCES) $(PROGRAM)

clean:
	@rm -fr $(ART_DIR)
	@rm -fr $(PROGRAM)
	@echo "Test Cleanup completed"


build: $(PROGRAM)

-include $(DEPENDS)

$(PROGRAM): $(ALL_DIR) $(OBJECTS)
	@echo "Linking $(notdir $@)"
	@$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

$(OBJ_DIR)/%.o: %.cpp 
	@echo "Building $(notdir $<)"
	@$(CC) -c  $(CFLAGS) $< -o $@
	@$(CC) -MM $(CFLAGS) $< -MT $@ -MF $(DEP_DIR)/$*.d

$(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR):
	@mkdir -p $@
	@echo "Creating directory $@"
