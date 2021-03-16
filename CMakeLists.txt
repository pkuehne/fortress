cmake_minimum_required (VERSION 3.13)
project (Fortress)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)
add_executable(fortress src/main.cpp)
add_library(fortresslib "")
target_link_libraries(fortress fortresslib)

# Add external projects from git submodules
# add_subdirectory(third-party/soil)

include(FetchContent)

# SOIL
FetchContent_Declare(
  soil
  GIT_REPOSITORY https://github.com/paralin/soil.git
  GIT_TAG        master
)
FetchContent_MakeAvailable(soil)
target_include_directories(fortresslib PRIVATE ${soil_SOURCE_DIR}/inc)
if(MINGW)
  target_link_libraries(soil opengl32)
else()
  target_link_libraries(soil GL)
endif(MINGW)
target_link_libraries(fortresslib soil)

# Yaml-CPP
FetchContent_Declare(
	yaml-cpp
	GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
	GIT_TAG        master
	)
FetchContent_MakeAvailable(yaml-cpp)
target_link_libraries(
  fortresslib yaml-cpp)

# glfw
FetchContent_Declare(
	glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG        master
	)
FetchContent_MakeAvailable(glfw)
target_link_libraries(fortresslib glfw)

# lua
FetchContent_Declare(
	lua
	GIT_REPOSITORY https://github.com/walterschell/lua.git
	GIT_TAG        master
	)
FetchContent_MakeAvailable(lua)
target_link_libraries(fortresslib lua_static)

# glog
FetchContent_Declare(
	glog
	GIT_REPOSITORY https://github.com/google/glog.git
	GIT_TAG        master
	)
FetchContent_MakeAvailable(glog)
target_link_libraries(fortresslib glog::glog)

# Add Compiler definitions
add_compile_definitions(FORTRESS_VERSION_MAJOR=0)
add_compile_definitions(FORTRESS_VERSION_MINOR=5)
add_compile_definitions(FORTRESS_VERSION_PATCH=0)
add_compile_definitions(FORTRESS_VERSION_BUILD="dev-build")

# Include source files
add_subdirectory(src/core)
add_subdirectory(src/algos)
add_subdirectory(src/components)
add_subdirectory(src/generators)
add_subdirectory(src/windows)
add_subdirectory(src/widgets)
add_subdirectory(src/systems)
add_subdirectory(src/world)

# Compiler options
target_compile_options(fortress PRIVATE -Wall -Wpedantic -Werror)

# Additional libraries
target_link_libraries(fortress dl)
target_link_libraries(fortress stdc++fs)
target_link_libraries(fortress m)
target_link_libraries(fortress pthread)
if(MINGW)
  target_link_libraries(fortress opengl32)
  target_link_options(fortress PRIVATE -static)
else()
  target_link_libraries(fortress GL)
endif(MINGW)

# Add Testing target
enable_testing()
add_subdirectory(test/unit_tests)

# Add 'run' command
add_custom_target(run
    COMMAND ./fortress
    DEPENDS fortress
)