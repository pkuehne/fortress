.PHONY: all clean build run
CC=g++

MODULES = $(wildcard */)
OUT_DIR = ..
PROGRAM = $(OUT_DIR)/fortress
ART_DIR = $(OUT_DIR)/artifacts
OBJ_DIR = $(ART_DIR)/objects
DEP_DIR = $(ART_DIR)/depends
COV_DIR = $(ART_DIR)/coverage
ALL_DIR = $(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR)

INC_DIRS += -I. -I/usr/include/ $(addprefix -I, $(MODULES))
CFLAGS=-g -rdynamic -Wall -Werror -std=c++14 $(INC_DIRS)
LDFLAGS= -g -rdynamic
GLFW_LIBS=$(shell pkg-config glfw3 --libs --static)
LIBRARIES=$(GLFW_LIBS) -lGL -lc -lm -lSOIL -lpthread -lglog 

SOURCES = $(foreach sdir, $(MODULES), $(wildcard $(sdir)/*.cpp))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.o)))
DEPENDS = $(addprefix $(DEP_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.d)))

vpath %.cpp $(MODULES)

all: $(SOURCES) $(PROGRAM)

clean:
	@rm -fr $(ART_DIR)
	@rm -fr $(PROGRAM)
	@echo "Cleanup completed"

build: $(PROGRAM)

$(PROGRAM): $(ALL_DIR) $(OBJECTS)
	@$(CC) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@
	@echo "Building $(notdir $@)"

-include $(DEPENDS)

$(OBJ_DIR)/%.o: %.cpp
	@$(CC) -c  $(CFLAGS) $< -o $@
	@$(CC) -MM $(CFLAGS) $< > $(DEP_DIR)/$*.d
	@echo "Building $(notdir $<)"

$(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR):
	@mkdir -p $@
	@echo "Creating directory $@"
