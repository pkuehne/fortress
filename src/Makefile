.PHONY: all clean build

MODULES = $(sort $(dir $(wildcard ../src/*/)))
OUT_DIR = ..
PROGRAM = $(OUT_DIR)/fortress
ART_DIR = $(OUT_DIR)/artifacts
OBJ_DIR = $(ART_DIR)/objects
DEP_DIR = $(ART_DIR)/depends
COV_DIR = $(ART_DIR)/coverage
ALL_DIR = $(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR)

MAJOR_VER?=0
MINOR_VER?=5
PATCH_VER?=0
BUILD_NUM?=\"dev-build\"

DEFINES=-DMAJOR=$(MAJOR_VER) -DMINOR=$(MINOR_VER) -DPATCH=$(PATCH_VER) -DBUILD=$(BUILD_NUM)
INC_DIRS += -I. -I/usr/include/ $(addprefix -I, $(MODULES))

CXX?=g++
WARNINGS=-Wall -Werror -pedantic
STANDARD=-std=c++14
DEBUG_INFO=-g
BACKTRACE=-rdynamic
CXXFLAGS= $(DEBUG_INFO) $(BACKTRACE) $(WARNINGS) $(STANDARD) $(INC_DIRS) $(DEFINES)

GLFW_LIBS=$(shell pkg-config glfw3 --libs --static)
YAML_LIBS=$(shell pkg-config yaml-cpp --libs --static)
LUA_LIBS=$(shell pkg-config lua5.3 --libs --static)
SOIL_LIBS=-lSOIL
GLOG_LIBS=-lglog
EXTERNAL_LIBS=$(GLFW_LIBS) $(YAML_LIBS) $(LUA_LIBS) $(SOIL_LIBS) $(GLOG_LIBS)
EXPERIMENTAL_LIBS=-lstdc++fs
OPENGL_LIBS=-lGL
CSTD_LIBS=-lc
MATH_LIBs=-lm
STANDARD_LIBS=$(EXPERIMENTAL_LIBS) $(OPENGL_LIBS) $(CSTD_LIBS) $(MATH_LIBS)

LIBRARIES= $(EXTERNAL_LIBS) $(STANDARD_LIBS) 
LDFLAGS= $(DEBUG) $(BACKTRACE)

SOURCES = $(foreach sdir, $(MODULES), $(wildcard $(sdir)/*.cpp))
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.o)))
DEPENDS = $(addprefix $(DEP_DIR)/, $(notdir $($(notdir SOURCES):.cpp=.d)))

vpath %.cpp $(MODULES)

all: $(SOURCES) $(PROGRAM)

clean:
	@rm -fr $(ART_DIR)
	@rm -fr $(PROGRAM)
	@echo "Build Cleanup completed"

build: $(PROGRAM)

-include $(DEPENDS)

$(PROGRAM): $(ALL_DIR) $(OBJECTS)
	@echo "Linking $(notdir $@)"
	@$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

$(OBJ_DIR)/main.o: main.cpp
	@echo "Overriding main"
	@$(CXX) -c  $(CXXFLAGS) main.cpp -o $@

$(OBJ_DIR)/%.o: %.cpp 
	@echo "Building $(notdir $<)"
	@$(CXX) -c  $(CXXFLAGS) $< -o $@
	@$(CXX) -MM $(CXXFLAGS) $< -MT $@ -MF $(DEP_DIR)/$*.d

$(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR):
	@mkdir -p $@
	@echo "Creating directory $@"
