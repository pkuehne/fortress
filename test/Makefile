.PHONY: all clean build run 
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

MAJOR_VER?=0
MINOR_VER?=0
PATCH_VER?=0
BUILD_NUM?=\"unit-tests\"

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
GMOCK_LIBS=-lgmock -lgtest
EXTERNAL_LIBS=$(GLFW_LIBS) $(YAML_LIBS) $(LUA_LIBS) $(SOIL_LIBS) $(GLOG_LIBS) $(GMOCK_LIBS)
EXPERIMENTAL_LIBS=-lstdc++fs
OPENGL_LIBS=-lGL
CSTD_LIBS=-lc
MATH_LIBs=-lm
STANDARD_LIBS=$(EXPERIMENTAL_LIBS) $(OPENGL_LIBS) $(CSTD_LIBS) $(MATH_LIBS)

LIBRARIES= $(EXTERNAL_LIBS) $(STANDARD_LIBS) 
LDFLAGS= $(DEBUG) $(BACKTRACE)

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
	@$(CXX) $(LDFLAGS) $(OBJECTS) $(LIBRARIES) -o $@

$(OBJ_DIR)/%.o: %.cpp 
	@echo "Building $(notdir $<)"
	@$(CXX) -c  $(CXXFLAGS) $< -o $@
	@$(CXX) -MM $(CXXFLAGS) $< -MT $@ -MF $(DEP_DIR)/$*.d

$(ART_DIR) $(OBJ_DIR) $(DEP_DIR) $(COV_DIR):
	@mkdir -p $@
	@echo "Creating directory $@"
