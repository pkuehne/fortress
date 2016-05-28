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

INC_DIRS += -I. -I/usr/include/ $(addprefix -I, $(MODULES))
CFLAGS=-g -rdynamic -Wall -Werror -std=c++14 $(INC_DIRS)
LDFLAGS= -g -rdynamic 
GLFW_LIBS=$(shell pkg-config glfw3 --libs --static)
YAML_LIBS=$(shell pkg-config yaml-cpp --libs --static)
LUA_LIBS=-L/usr/local/lib -llua
LIBRARIES=$(GLFW_LIBS) $(YAML_LIBS) -lGL -lc -lm -lSOIL -lpthread -lglog 
LIBRARIES+=-lgtest -lgmock -gcov

SOURCES = $(foreach sdir, $(MODULES), $(wildcard $(sdir)/*.cpp))
SOURCES+= $(wildcard *.cpp)
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.o)))
DEPENDS = $(addprefix $(DEP_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.d)))

vpath %.cpp $(MODULES)

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
